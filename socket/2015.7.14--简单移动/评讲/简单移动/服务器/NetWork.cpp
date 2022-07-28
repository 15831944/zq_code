#include "NetWork.h"
#pragma comment(lib, "Ws2_32.lib")

#define _BUF_MAX 65536

bool CNetWork::_SendData()
{
	//��������ݾͷ��͵�ǰ����
	while (sd_list.size() > 0)
	{
		//�õ�Ҫ���͵����ݰ�
		SD sd = sd_list.front();

		while (sd.send_len < sd.all_len)
		{
			int r = send(m_socket, sd.data + sd.send_len, sd.all_len - sd.send_len, 0);
			if (r == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
					return false;
				else
					return true;
			}
			else
				sd.send_len += r;
		}

		//��ǰ��������ϣ���ô�ͷŴ洢������
		free(sd.data);

		//����ӷ��ͱ���ɾ��
		sd_list.erase(sd_list.begin());
	}

	return true;
}

bool CNetWork::_RecvData()
{
	char buf[_BUF_MAX];
	int r = recv(m_socket, buf, _BUF_MAX, 0);
	if (r == SOCKET_ERROR)
		//������������Ĵ���ͷ��ؼ�
		//�����ǰû�����ݿɶ��ͷ�����
		return WSAGetLastError() == WSAEWOULDBLOCK;
		//��������ŶϿ��ͷ��ؼ�
	else if (r == 0)
		return false;
	else
	{
		//��ʼ��������λ��
		int cur = 0;

		//ѭ��������������
		while (cur < r)
		{
			//��ǰû�����곤��
			if (rd.len_valid_bytes < 4)
			{
				//��ǰ�������곤��
				if (4 - rd.len_valid_bytes > r - cur)
				{
					//���������յĳ����ֽڵ��ܳ�����
					memcpy(
						(char*)&rd.all_len + rd.len_valid_bytes,
						buf + cur,
						r - cur);

					//���ȵ���Ч�ֽ�������
					rd.len_valid_bytes += r - cur;

					//������λ�õ������������˳�ѭ�������������ݣ�
					cur += r - cur;
				}
				//��ǰ�������곤��
				else
				{
					//���������յĳ����ֽڵ��ܳ�����
					memcpy(
						(char*)&rd.all_len + rd.len_valid_bytes,
						buf + cur,
						4 - rd.len_valid_bytes);

					//������λ�õ���
					cur += 4 - rd.len_valid_bytes;

					//���ȵ���Ч�ֽ�������
					rd.len_valid_bytes = 4;

					//���ٽ������ݵ��ڴ�
					rd.data = (char*)malloc(rd.all_len);
				}
			}
			//��ǰ�����˳���Ӧ��������
			else
			{
				//��ǰ������������
				if (rd.all_len - rd.recv_len > r - cur)
				{
					//���������յ����ݵ���������
					memcpy(
						rd.data + rd.recv_len,
						buf + cur,
						r - cur);

					//�Ѿ����յ����ݸ���
					rd.recv_len += r - cur;

					//������λ�õ������������˳�ѭ�������������ݣ�
					cur += r - cur;
				}
				//��ǰ������������
				else
				{
					//���������յ����ݵ���������
					memcpy(
						rd.data + rd.recv_len,
						buf + cur,
						rd.all_len - rd.recv_len);

					//������λ�õ���
					cur += rd.all_len - rd.recv_len;

					//�����һ�����ķ���
					_RECV_DATA recv_data = {rd.data, rd.all_len};
					rd_list.push_back(recv_data);

					//���
					rd.len_valid_bytes = 0;
					rd.all_len = 0;
					rd.data = 0;
					rd.recv_len = 0;
				}
			}
		}
	}

	return true;
}

CNetWork::CNetWork()
:
m_socket(INVALID_SOCKET)
{
	rd.len_valid_bytes = 0;
	rd.all_len = 0;
	rd.data = 0;
	rd.recv_len = 0;
}

CNetWork::CNetWork(SOCKET s)
:
m_socket(s)
{
	rd.len_valid_bytes = 0;
	rd.all_len = 0;
	rd.data = 0;
	rd.recv_len = 0;
}

void CNetWork::SetSocket(SOCKET s)
{
	m_socket = s;
}

void CNetWork::SendData(const void* data, int len)
{
	//׼���������ݰ�
	SD sd;
	sd.all_len = sizeof(int) + len;
	sd.data = (char*)malloc(sd.all_len);
	sd.send_len = 0;
	
	//��䳤�Ⱥ�����
	*((int*)sd.data) = len;
	memcpy(sd.data + sizeof(int), data, len);

	//װ�뷢�ͱ���
	sd_list.push_back(sd);
}

bool CNetWork::GetRecvDate(_RECV_DATA* recv_data)
{
	if (rd_list.size() > 0)
	{
		*recv_data = rd_list.front();
		rd_list.erase(rd_list.begin());
		return true;
	}
	else
		return false;
}

void CNetWork::ReleaseRecvData(_RECV_DATA* recv_data)
{
	if (recv_data->data)
		free(recv_data->data);
}

bool CNetWork::Run()
{
	bool r1 = _RecvData();
	bool r2 = _SendData();
	return r1 && r2;
}

void CNetWork::End()
{
	for (int i = 0; i < rd_list.size(); ++i)
		free(rd_list[i].data);
	if (rd.data)
		free(rd.data);
	for (int i = 0; i < sd_list.size(); ++i)
		free(sd_list[i].data);
}