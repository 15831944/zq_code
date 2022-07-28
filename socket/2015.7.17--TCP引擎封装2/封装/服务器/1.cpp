#include <iostream>
#include "TcpServer.h"

void main()
{
	CTcpServer ts;

	ts.Init(12345, 256, 10, 5);

	//std::vector<SOCEKT> v;

	while (ts.Continue())
	{
		ts.Run();

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
					//v.push_back(ne.s);
					break;
				}
			case _SNE_DATA:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"���ӵ�������"<<std::endl;
					break;
				}
			case _SNE_DISCONNECTED_C:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"�Ͽ����ͻ���������"<<std::endl;
					break;
				}
			case _SNE_DISCONNECTED_S:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"�Ͽ�������������)"<<std::endl;
					break;
				}
			case _SNE_DISCONNECTED_E:
				{
					std::cout<<CTcpServer::ulong_str(ne.ip, ip)<<"�Ͽ�������"<<std::endl;
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