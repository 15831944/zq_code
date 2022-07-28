#include "UseBmp.h"


HDC GetBmpDC(HWND hwnd,const char* bmpfile)
{
	HBITMAP hbmp = (HBITMAP)LoadImage(0,bmpfile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	if(!hbmp)
		return 0;
	//��������ʾ�豸
	//HDC maindc = GetDC(HWND_DESKTOP);
	//�õ����豸
	HDC maindc = GetDC(hwnd);

	//����������ʾ�豸
	HDC bmpdc = CreateCompatibleDC(maindc);

	//����λͼѡ������豸��
	HBITMAP oldbmp = (HBITMAP)SelectObject(bmpdc,hbmp);

	//ɾ����λͼ����λͼѡ�뵽�����豸�󣬼����豸�ڲ���������
	//������һ����λͼ������
	DeleteObject(hbmp);

	//ɾ����λͼ
	DeleteObject(oldbmp);

	//�ͷ����豸
	ReleaseDC(hwnd,maindc);

	return bmpdc;
}

void DeleteBmpDC(HDC hdc)
{
	DeleteDC(hdc);
}