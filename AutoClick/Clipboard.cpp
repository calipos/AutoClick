#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

int testClipboard()
{
	HWND hWnd = NULL;
	if (OpenClipboard(hWnd))//打开剪切板
	{
		EmptyClipboard();//清空剪切板
		HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 1000);//分配内存
		char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
		strcpy(pData, "this is a ClipBoard Test.");
		SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
		GlobalUnlock(hHandle);//解除锁定
		CloseClipboard();//关闭剪切板
	}
	else
	{
		std::cout<<"OpenClipboard err"<<std::endl;
		return -1;
	}


	//OpenClipboard(hWnd);
	//EmptyClipboard();
	//if (IsClipboardFormatAvailable(CF_TEXT))
	//{
	//	HANDLE h = GetClipboardData(CF_TEXT);//获取剪切板数据
	//	char* p = (char*)GlobalLock(h);
	//	GlobalUnlock(h);
	//	CloseClipboard();
	//}

	return 0;
}

int keyIn(const int& key0, const int& key1 = -1);
int keyIn(const std::string& comment)
{
	if (comment.length()>900)
	{
		std::cout << "comment too long" << std::endl;
		return -1;
	}
	HWND hWnd = NULL;
	if (OpenClipboard(hWnd))//打开剪切板
	{
		EmptyClipboard();//清空剪切板
		HANDLE hHandle = GlobalAlloc(GMEM_FIXED, 1000);//分配内存
		char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
		strcpy(pData, comment.data());
		SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
		GlobalUnlock(hHandle);//解除锁定
		CloseClipboard();//关闭剪切板
		keyIn(VK_LCONTROL, 'V');
	}
	else
	{
		std::cout << "OpenClipboard err" << std::endl;
		return -1;
	}
	return 0;
}
int paste()
{
	//keybd_event('J', 0, 0, 0); //按下
	//keybd_event('J', 0, 2, 0); //松开
	//keybd_event(0x0d, 0, 0, 0);//回车
	//keybd_event(0x0d, 0, 2, 0);
	keybd_event(17, 0, 0, 0);
	keybd_event(118, 0, 0, 0);
	keybd_event(118, 0, 2, 0);
	keybd_event(17, 0, 2, 0);
	Sleep(1);
	return 0;
}

int keyIn(const int& key0, const int& key1)
{
	//keybd_event(VK_LWIN, 0, 0, 0);
	//keybd_event('M', 0, 0, 0);
	//keybd_event('M', 0, KEYEVENTF_KEYUP, 0);
	//keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
	if (key1>=0)
	{
		keybd_event(key0, 0, 0, 0);
		keybd_event(key1, 0, 0, 0);
		Sleep(100);
		keybd_event(key1, 0, 2, 0);
		keybd_event(key0, 0, 2, 0);
		//
	}
	else
	{
		keybd_event(key0, 0, 0, 0);
		keybd_event(key0, 0, 2, 0);
		Sleep(100);
	}
	return 0;
}