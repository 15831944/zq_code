#include <windows.h>
#include "resource.h"
#include <iostream>

bool begin = false;
int num = 0;
int opr = -1; //0123����+-*/
bool selectNum = true;//ѡ������


void activeNum(HWND hwndDlg,bool b)
{
	for(int i = IDC_BUTTON1 ; i <= IDC_BUTTON10;++i)
	{
		HWND h = GetDlgItem(hwndDlg ,i);
		EnableWindow(h,b);
	}
	for(int i = IDC_BUTTON12 ; i <= IDC_BUTTON15;++i)
	{
		HWND h = GetDlgItem(hwndDlg ,i);
		EnableWindow(h,!b);
	}
}

INT_PTR CALLBACK DiglogProc(HWND hwnddlg,
							UINT uMsg,
							WPARAM wParam,
							LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
			activeNum(hwnddlg,true);
			return 1;
		}
	case WM_COMMAND:
		{
			if(HIWORD(wParam) == BN_CLICKED)
			{
				if(LOWORD(wParam) == IDCANCEL
				||LOWORD(wParam) == IDOK)
					EndDialog(hwnddlg,1);
				else if(LOWORD(wParam) == IDC_BUTTON11)
				{
					begin = false;
					num = 0;
					opr = -1;
					selectNum = true;
					activeNum(hwnddlg,selectNum);
					SetWindowTextA(GetDlgItem(hwnddlg,IDC_EDIT1),"");
				}
				else
				{
					if(selectNum)
					{
						if(!begin)
						{
							num = LOWORD(wParam) - IDC_BUTTON1 + 1;
							begin = true;
						}
						else
						{
							switch(opr)
							{
							case 0:num += ( LOWORD(wParam) - IDC_BUTTON1 + 1);break;
							case 1:num -= ( LOWORD(wParam) - IDC_BUTTON1 + 1);break;
							case 2:num *= ( LOWORD(wParam) - IDC_BUTTON1 + 1);break;
							case 3:num /= ( LOWORD(wParam) - IDC_BUTTON1 + 1);break;
							}
						}
						char buf[32];
						sprintf_s(buf,32,"%d",num);
						SetWindowTextA(GetDlgItem(hwnddlg,IDC_EDIT1),buf);
						activeNum(hwnddlg,selectNum = !selectNum);
					}
					else
					{
						opr = LOWORD(wParam) - IDC_BUTTON12;
						activeNum(hwnddlg,selectNum = !selectNum);
					}
				}
			}
			return 0;
		}
	}
	return 0;
}


//������Ϣ��������������������ϵͳ����
__w64 long __stdcall WindowProc(HWND hwnd,//������Ϣ�Ĵ���
								unsigned int uMsg,//��Ϣ����
								__w64 unsigned int wParam,//��Ϣ���Ӳ���1
								__w64 long lParam)//��Ϣ���Ӳ���2
{
	switch(uMsg)
	{
	//������Ϣ������ʽ
	//1)���ϵͳ�˵��Ĺرղ˵��Alt + F4��
	//2)���Ͻǵ�X��ť
	case WM_DESTROY:
		{
			//Ͷ��һ��WM_QUIT��Ϣ�����̵߳���Ϣ������
			PostQuitMessage(0);
			//һ�����Ǵ�����ĳ����Ϣ��Ҫֱ�ӷ���0.
			return 0;
		}
	}
	//���ǲ����ĵ���Ϣ�͵���DefWindowProc(windows��������Ϣ��Ĭ�ϴ�����)���������Ǵ���
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int __stdcall WinMain(HINSTANCE hInstance,//Ӧ�ó���ʵ�����
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),HWND_DESKTOP,DiglogProc);

	return 1;
}