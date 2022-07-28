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

//�������ܵ�
void readfifo()
{
	int len = 0;
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	int fd = open("/home/zhangqi/helloworld/fifo1", O_RDONLY);
	if (fd == -1)
	{
		printf("file open error!%s\n",strerror(errno));
		return;
	}
	while ((len = read(fd, buf, sizeof(buf))) > 0)
	{
		printf("%s\n", buf);
		memset(buf, 0, sizeof(buf));
	}
	close(fd);
}

//�ػ�����
void setdaemon()
{
	pid_t pid = fork();
	if (pid == -1)
	{
		printf("fork error!\n");
		exit(0);
	}
	if (pid == 0)
	{
		//�ϵ����ն˵���ϵ
		setsid();
		/*
		//���ø�Ŀ¼
		chdir("/");
		//�����ļ�Ȩ��
		umask(0);
		//�رձ�׼�������
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		*/
	}
	if (pid > 0)
		exit(0);
}

int main(int arg, char* args[])
{
	setdaemon();
	readfifo();
	return 0;
}
