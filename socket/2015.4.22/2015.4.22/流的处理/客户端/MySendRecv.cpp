#include "MySendRecv.h"

#pragma comment(lib, "Ws2_32.lib")

#define _RECV_BUF (64 * 1024)

void CMySendRecv::_Send()
{
	//����
	while (sdlist.size() > 0)
	{
		//�õ���ǰҪ���͵����ݰ�
		_SEND_DATA sd = sdlist[0];

		//�������ݰ����͵Ľ��,0��1��2�ֱ��ʾ������ϡ��ݲ��ܷ�������
		int result = 0;

		//ѭ������
		while (sd.sendsize < sd.allsize)
		{
			int r = send(m_Socket, sd.data + sd.sendsize, sd.allsize - sd.sendsize, 0);

			if (SOCKET_ERROR == r)
			{
				if (WSAEWOULDBLOCK == WSAGetLastError())
					result = 1;
				else
					result = 2;
				break;
			}
			else
				sd.sendsize += r;
		}

		switch (result)
		{
		case 0:
			{
				//������ϵ�ǰ���ݰ��Ͱ����ӷ��ͱ���ɾ��
				free(sd.data);
				sdlist.erase(sdlist.begin());
				break;
			}
				//��ʱ���ܷ��͵Ļ���ʲô������
		case 1: break;

		case 2:
			{
				//���ô����¼�
				_NET_EVENT ne = {0};
				nelist.push_back(ne);
				break;
			}
		}
	}
}

void CMySendRecv::_Recv()
{
	char buf[_RECV_BUF];
	int r = recv(m_Socket, buf, _RECV_BUF, 0);

	//����
	if (r == SOCKET_ERROR)
	{
		//��ĳ�����
		if (WSAEWOULDBLOCK != WSAGetLastError())
		{
			//���ô����¼�
			_NET_EVENT ne = {0};
			nelist.push_back(ne);
		}
	}
	//���ŶϿ�
	else if (r == 0)
	{
		//���ô����¼�
		_NET_EVENT ne = {0};
		nelist.push_back(ne);
	}
	else
	{
		//��ǰ�����±�
		int cur_i = 0;
		while (cur_i < r)
		{
			//��ǰ���ճ��Ȳ���
			if (recv_data.allsize_bytes < 4)
			{
				//��ǰ�������곤�Ȳ���
				if (4 - recv_data.allsize_bytes > r - cur_i)
				{
					//���ֽڿ����������ܳ���
					memcpy(&recv_data.allsize, buf + cur_i, r - cur_i);

					//�����ܳ�����Ч�ֽ�������
					recv_data.allsize_bytes += r - cur_i;

					//��ǰ�����±����
					cur_i += r - cur_i;
				}
				//��ǰ�������곤�Ȳ���
				else
				{
					//���ֽڿ����������ܳ���
					memcpy(&recv_data.allsize, buf + cur_i, 4 - recv_data.allsize_bytes);

					//��ǰ�����±����
					cur_i += 4 - recv_data.allsize_bytes;

					//�����ܳ�����Ч�ֽ�������Ϊ4
					recv_data.allsize_bytes = 4;

					//���ٶ��ڴ�
					recv_data.data = (char*)malloc(recv_data.allsize);
				}
			}
			//��ǰ�������ݲ���
			else
			{
				//��ǰ���ܽ���������
				if (recv_data.allsize - recv_data.recv_size > r - cur_i)
				{
					//����ʣ�µ������ֽڵ�������
					memcpy(recv_data.data + recv_data.recv_size, buf + cur_i, r - cur_i);

					//��ǰ�Ѿ����յ����ݳ��ȵ���
					recv_data.recv_size += r - cur_i;

					//��ǰ�����±����
					cur_i += r - cur_i;
				}
				else
				{
					//������ǰ��������Ҫ���ֽڵ�������
					memcpy(recv_data.data + recv_data.recv_size, buf + cur_i, recv_data.allsize - recv_data.recv_size);
					
					//��ǰ�����±����
					cur_i += recv_data.allsize - recv_data.recv_size;

					//�����������¼�
					_NET_EVENT ne = {1, recv_data.data, recv_data.allsize};
					nelist.push_back(ne);

					//��ս���
					recv_data.allsize = 0;
					recv_data.allsize_bytes = 0;
					recv_data.data = 0;
					recv_data.recv_size = 0;
				}
			}
		}
	}
}

CMySendRecv::CMySendRecv(SOCKET Socket)
{
	m_Socket = Socket;

	//��ս���
	recv_data.allsize = 0;
	recv_data.allsize_bytes = 0;
	recv_data.data = 0;
	recv_data.recv_size = 0;
}

void CMySendRecv::SendData(const void* Data, int Size)
{
	//���һ���������ݽṹ��
	_SEND_DATA sd;
	sd.allsize = sizeof(int) + Size;
	sd.data = (char*)malloc(sd.allsize);
	*((int*)sd.data) = Size;
	memcpy(sd.data + 4, Data, Size);
	sd.sendsize = 0;

	//���������ݽṹ�����뷢�ͱ���
	sdlist.push_back(sd);
}

bool CMySendRecv::GetNetEvent(_NET_EVENT* pNetEvent)
{
	if (nelist.size() > 0)
	{
		*pNetEvent = nelist[0];
		nelist.erase(nelist.begin());
		return true;
	}
	else
		return false;
}

void CMySendRecv::Run()
{
	_Send();
	_Recv();
}

void CMySendRecv::Close()
{
	for (int i = 0; i < (int)sdlist.size(); ++i)
		free(sdlist[i].data);

	if (recv_data.data)
		free(recv_data.data);

	for (int i = 0; i < (int)nelist.size(); ++i)
	{
		if (nelist[i].type == 1)
			free(nelist[i].data);
	}
}