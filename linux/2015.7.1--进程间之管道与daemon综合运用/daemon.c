#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

//�źŻص�����
int signal1(int signo, void(*func)(int))
{
	//��������sigaction �ṹָ��
	struct sigaction act, oact;
	//ָ���˻ص�����
	act.sa_handler = func;
	//����������Ѹ�ֵ���
	sigemptyset(&act.sa_mask);
	//��ʼ������ṹ
	act.sa_flags = 0;
	//����֮ǰ��״̬
	return sigaction(signo, &act, &oact);
}

//�ػ�����
void setdaemon()
{
	pid_t pid,sid;
	pid = fork();
	if (pid == -1)
	{
		printf("fork error!%s\n",strerror(errno) );
		exit(EXIT_FAILURE);
	}
	if ((sid = setsid()) < 0)
	{
		printf("fork error!%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
		exit(EXIT_SUCCESS);
}

//�����ܵ�
void listenfifo()
{
	const char* sfifoname = "fifo1";
	int len = 0;
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int fd = open(sfifoname, O_RDONLY);
	if (fd == -1)
	{
		printf("file open error!%s\n", strerror(errno));
		return;
	}
	len = read(fd, buf, sizeof(buf));
	if (len > 0)
	{
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;
		close(STDOUT_FILENO);
		open(buf, O_WRONLY);
	}
	close(fd);
}

//��׽�ź�
void catch_Signal(int sign)
{
	switch (sign)
	{
	case SIGINT:
		listenfifo();
		break;
	}
}

int main(int arg, char* args[])
{
	//�ѽ�����Ϊdaemon״̬
	setdaemon();
	//��׽SIGINT�ź�
	signal1(SIGINT, catch_Signal);
	while (1)
	{
		puts("hello world!");
		sleep(1);
	}
	return 0;
}