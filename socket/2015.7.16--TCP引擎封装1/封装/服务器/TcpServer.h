#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <Winsock2.h>
#include "MemoryPool.h"
#include "SqQueue.h"
#include "Map.h"

//端口号最小值
#define _MIN_PORT 1025

//网络事件（Net Event）
#define _NE_CONNECTED 0 //有客户端连接成功
#define _NE_DATA 1 //有客户端发送过来数据
#define _NE_DISCONNECTED_C 2 //客户端主动断开
#define _NE_DISCONNECTED_S 3 //服务器主动断开
#define _NE_DISCONNECTED_E 4 //因为错误断开
struct _NET_EVENT
{
	int type; //类型（0~4）
	SOCKET s; //发生网络事件的套接字
	unsigned long ip; //发生网络事件的ip地址
	char* data; //数据
	int len; //数据长度
};

class CTcpServer
{
	//发送结构体
	struct _SEND_DATA
	{
		char* data; //数据
		int all_size; //数据总长
		int send_size; //已发送数据长度
	};

	//接收结构体
	struct _RECV_DATA
	{
		char* data; //数据
		int size_byte; //数据总长有效字节数
		int all_size; //数据总长
		int recv_size; //已接收数据长度
	};

	//客户端
	struct _CLIENT
	{
		int state; //客户端状态
		unsigned long ip; //ip地址
		CSqQueue<_SEND_DATA> sd_queue; //发送数据队列
		_RECV_DATA rd; //接收数据
	};

	//网络事件队列
	CSqQueue<_NET_EVENT> m_NetEvent;

	//客户表
	CMap<SOCKET, _CLIENT> m_Client;

	//内存池
	CMemoryPool m_MP;

	//监听套接字
	SOCKET m_Listen;

	//最大连接数
	int m_MaxClient;

	//心跳包启动时间和间隔时间
	int m_BeginKA;
	int m_IntervalKA;

	//持续标志
	bool m_Continue;

	//接收连接请求
	void _Accept();

	//发送数据
	void _Send();

	//接收数据
	void _Recv();

public:

	//构造析构
	CTcpServer();
	~CTcpServer();

	//初始化
	bool Init(
		unsigned short port, //端口号
		int maxclient, //最大连接数
		int beginka, //心跳包启动时间
		int intervalka); //心跳包间隔时间

	//运行
	void Run();

	//停止
	void Stop();

	//持续
	bool Continue();

	//结束
	void End();

	//得到网络事件
	bool GetNetEvent(_NET_EVENT* ne);

	//释放网络事件
	void ReleaseNetEvent(_NET_EVENT* ne);

	//发送数据
	bool SendData(SOCKET s, const void* data, int len);

	//断开连接
	bool Disconnect(SOCKET s);
};

#endif