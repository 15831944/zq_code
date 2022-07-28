#include <iostream>
#include <string>
#include <map>
#include "TcpServer.h"
#include "..\\XY.h"

#define _CLIENT_INFO_FILE "�����Ϣ"

void GetIDPasswordFromFile(const char* fn,
						   std::map<std::string, std::string>* m);
void SaveFile(const char* fn, std::map<std::string, std::string>* m);

void main()
{
	//���ļ��ж�ȡ�˺ź�����
	std::map<std::string, std::string> m_ID_Password;
	GetIDPasswordFromFile(_CLIENT_INFO_FILE, &m_ID_Password);

	//��ǰ��ұ�<�׽��֡��˺�>
	std::map<SOCKET, std::string> m_Clients;

	//����������
	CTcpServer ts;
	ts.Init(12345, 256, 10, 5);

	//ҵ��ѭ��
	while (ts.Continue())
	{
		//����������
		ts.Run();

		//�����¼�����
		_SNET_EVENT ne;
		while (ts.GetNetEvent(&ne))
		{
			//���������¼�
			char ip[16];

			switch (ne.type)
			{
			case _SNE_CONNECTED:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"���ӵ�������"<<std::endl;

					//װ���׽��ֺͿ��˺�
					m_Clients.insert(std::pair<SOCKET, std::string>(ne.s, ""));

					break;
				}
			case _SNE_DATA:
				{
					_XY* xy = (_XY*)ne.data;
					switch (xy->type)
					{
					case 0:
						{
							CS_DL* dl = (CS_DL*)ne.data;

							//�޴����
							std::map<std::string, std::string>::iterator it = m_ID_Password.find(dl->id);
							if (it == m_ID_Password.end())
							{
								SC_NO_ID no_id;
								ts.SendData(ne.s, &no_id, sizeof(no_id));
								ts.Disconnect(ne.s);
							}
							else
							{
								//�����Ƿ���ȷ
								if (strcmp(it->second.c_str(), dl->pw) != 0)
								{
									SC_PW_ERROR pw_error;
									ts.SendData(ne.s, &pw_error, sizeof(pw_error));
									ts.Disconnect(ne.s);
								}
								else
								{
									//���˺�װ�뵱ǰ��ұ�����ĵ�ǰ��ұ���˺��ǿ�
									std::map<SOCKET, std::string>::iterator it = m_Clients.find(ne.s);
									it->second = dl->id;

									//ע��3����Ϣ�ĳ����Ǹ��ݵ�ǰ��ҵĸ�����ͬ����ͬ��

									//1������3����Ϣ�ĳ���
									int _3_len = sizeof(SC_DL_OK);
									for (it = m_Clients.begin(); it != m_Clients.end(); ++it)
									{
										if (it->first != ne.s && it->second.length() > 0)
											_3_len += it->second.length() + 1;
									}

									//2������3����Ϣ
									SC_DL_OK* dl_ok = (SC_DL_OK*)malloc(_3_len);
									dl_ok->type = 3;
									dl_ok->num = 0; //������Ҹ���
									char* p = (char*)(dl_ok + 1);
									for (it = m_Clients.begin(); it != m_Clients.end(); ++it)
									{
										if (it->first != ne.s && it->second.length() > 0)
										{
											memcpy(p, it->second.c_str(), it->second.length() + 1);
											p += strlen(p) + 1;
											dl_ok->num += 1;
										}
									}

									//3������3����Ϣ
									ts.SendData(ne.s, dl_ok, _3_len);
									free(dl_ok);

									//4������4����Ϣ
									SC_NEW_CLIENT new_client;
									strcpy_s(new_client.id, 32, dl->id);
									for (it = m_Clients.begin(); it != m_Clients.end(); ++it)
									{
										if (it->first != ne.s && it->second.length() > 0)
										{
											ts.SendData(it->first, &new_client, sizeof(new_client));
										}
									}
								}
							}

							break;
						}
					case 5:
						{
							CS_ZC* zc = (CS_ZC*)ne.data;
							
							//�ж��Ƿ��Ѿ����˸��˺�
							if (m_ID_Password.find(zc->id) != m_ID_Password.end())
							{
								//����ע��ʧ��
								SC_ZC_FAIL zc_fail;
								ts.SendData(ne.s, &zc_fail, sizeof(zc_fail));
							}
							else
							{
								m_ID_Password.insert(std::pair<std::string, std::string>(zc->id, zc->pw));
								SaveFile(_CLIENT_INFO_FILE, &m_ID_Password);

								//����ע��ɹ�
								SC_ZC_OK zc_ok;
								ts.SendData(ne.s, &zc_ok, sizeof(zc_ok));
							}

							ts.Disconnect(ne.s);

							break;
						}
					}
					break;
				}
			case _SNE_DISCONNECTED_C:
			case _SNE_DISCONNECTED_S:
			case _SNE_DISCONNECTED_E:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"�Ͽ�"<<std::endl;
					break;
				}
			}

			ts.ReleaseNetEvent(&ne);
		}

		if (GetAsyncKeyState(VK_ESCAPE))
			ts.Stop();
	}

	ts.End();

	system("pause");
}

void GetIDPasswordFromFile(const char* fn, std::map<std::string, std::string>* m)
{
	//�˺�����(4)
	//�˺�0������0
	//�˺�1������1
	//...
	//�˺�n������n

	FILE* pf = 0;
	fopen_s(&pf, fn, "rb");

	//���û���ļ����½��ļ�
	if (!pf)
	{
		fopen_s(&pf, fn, "wb");
		fclose(pf);
		m->clear();
		return;
	}
	
	//��ȡ�ļ�����
	fseek(pf, 0, SEEK_END);
	int fs = ftell(pf);
	rewind(pf);
	char* fd = (char*)malloc(fs);
	fread(fd, 1, fs, pf);
	fclose(pf);

	//�õ�����
	int num = *((int*)fd);

	//�õ����������Ϣ
	char* p = fd + 4;
	for (int i = 0; i < num; ++i)
	{
		std::string id = p;
		p += strlen(p) + 1;
		std::string pw = p;
		p += strlen(p) + 1;
		m->insert(std::pair<std::string, std::string>(id, pw));
	}

	//�ͷ�
	free(fd);
}

void SaveFile(const char* fn, std::map<std::string, std::string>* m)
{
	FILE* pf = 0;
	fopen_s(&pf, fn, "wb");

	int num = (int)m->size();
	fwrite(&num, 1, 4, pf);

	std::map<std::string, std::string>::iterator it;
	for (it = m->begin(); it !=  m->end(); ++it)
	{
		fwrite(it->first.c_str(), 1, it->first.length() + 1, pf);
		fwrite(it->second.c_str(), 1, it->second.length() + 1, pf);
	}

	fclose(pf);
}