#ifndef _GAME_H_
#define _GAME_H_

void Init();
void Run();
void End();

#endif

void capture_screen(const char* fn);

//DirectX��΢���Ƴ���ר����Զ�ý�塢������Ϸ�Ƚ��п�����
//��̹��ߣ�h��lib��dll������νDirect���������Ӣ�ĺ�����
//��ֱ�ӡ�����·��������˼���˴�����˼���ǡ�ֱ�ӡ���Ӳ����
//����������н���������߳��������Ч�ʣ���DirectX������
//Ҫ������Ǻ���Ƶ�йص����DirectGraphics���������ַ�Ϊ
//DirectDraw��Direct3D������DirectDraw�ǽ��ж�ά���Ƶ����
//����Direct3D�ǽ�����ά���Ƶ����������ͼʾʹ��GDI��Direct
//Graphics������
//����Aʹ��GDI <---> Windows <---> Ӳ������ <---> ������
//����Aʹ��DirectGraphics <---> Ӳ������ <---> ������
//���ż����Ӳ���ķ�չ��GDI��DirectDraw��Ч����������û����
//������ô���ˣ����ڵ�DirectDraw��Ч���ձ��GDI���ϼ�������
//��ʱ��98~05����ά��Ϸ�Ŀ���99%�������DirectDraw��������
//����������˵���ܶ໭��򵥵Ķ�ά��Ϸ�������ŭ��С��ȣ���
//��GDI�������Ϸ�Ļ�����ƶ�û��ʹ��DirectDraw��ֻҪ��װ��
//VS2005����ô����ͨ������Depends���鿴һ��exe��dll����ʱ��
//����Ҫ��dll��Depends��C:\Program Files\Microsoft Visual Studio 8\Common7\Tools\Bin\Depends
//ʹ��DirectDraw�����л���Ļ��Ʒǳ�����ֱ�Ӷ�д�Դ棬ʹ��
//DirectDraw��Ļ����ͷǳ��ʺϽ�����άͼ��ѧ��ѧϰ
//DirectX�ܹ�������һЩ���
//1��Direct Graphics
//  {
//		DirectDraw����ά����
//		Direct3D����ά����
//  }
//2��Direct Audio
//	{
//		DirectMusic���߽���Ƶ����Ҫ���ڽ������֡���Ч�Ĳ���
//		DirectSound���ͽ���Ƶ����Ҫ���ڲɼ���Ƶ��������ά��Чʵ��
//	}
//3��Direct Input�������빦�ܵ�֧�֣�����֧�ֳ������ꡢ���̣���֧�������������豸���ֱ���ҡ�ˡ�����̺��
//4��Direct Play���������ӵ�֧�֣����ֻ֧��64���ͻ��˵����ӣ�����������������Ϸһ�㶼ʹ��socket
//5��Direct Show����ý��Ĵ���