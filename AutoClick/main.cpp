
#include<iostream>
#include<conio.h>
#include<windows.h>
#include <string>
#include<opencv2/opencv.hpp>


#ifdef NDEBUG
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"libjpeg-turbo.lib")
#pragma comment(lib,"libjasper.lib")
#pragma comment(lib,"IlmImf.lib")
#pragma comment(lib,"libtiff.lib")
#pragma comment(lib,"libwebp.lib")
#pragma comment(lib,"libpng.lib")
#pragma comment(lib,"zlib.lib")
#pragma comment(lib,"opencv_world412.lib")
#endif
#ifdef _DEBUG
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"libjpeg-turbod.lib")
#pragma comment(lib,"libjasperd.lib")
#pragma comment(lib,"IlmImfd.lib")
#pragma comment(lib,"libtiffd.lib")
#pragma comment(lib,"libwebpd.lib")
#pragma comment(lib,"libpngd.lib")
#pragma comment(lib,"zlibd.lib")
#pragma comment(lib,"opencv_world412d.lib")
#endif
using namespace std;

extern void initGDI();
extern cv::Mat gdiScreenCapture();
extern int testClipboard();
extern int keyIn(const int& key0, const int& key1 = -1);
extern int keyIn(const std::string& comment);
cv::Size getScreenSize()
{
	POINT currentP;
	POINT pMin{ -1,-1 }, pMax{ -1,-1 };
	//while (true)
	//{
	//	GetCursorPos(&currentP);//获取鼠标坐标 
	//	std::cout << currentP.x << "," << currentP.y << std::endl;
	//}
	while (1) {

		GetCursorPos(&currentP);//获取鼠标坐标 
		if (pMin.x == currentP.x && pMin.y == currentP.y)
		{
			break;
		}
		pMin.x = currentP.x;
		pMin.y = currentP.y;
		//mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, currentP.x - 1, currentP.y - 1, 0, 0);
		SetCursorPos(currentP.x - 1300, currentP.y - 1300);//更改鼠标坐标 
	}
	while (1) {
		GetCursorPos(&currentP);//获取鼠标坐标 
		if (pMax.x == currentP.x && pMax.y == currentP.y)
		{
			break;
		}
		pMax.x = currentP.x;
		pMax.y = currentP.y;
		//mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, currentP.x + 1300, currentP.y + 1300, 0, 0);
		SetCursorPos(currentP.x + 1300, currentP.y + 1300);//更改鼠标坐标 
	}
	std::cout << pMin.x << "," << pMin.y << std::endl;
	std::cout << pMax.x << "," << pMax.y << std::endl;
	SetCursorPos((pMin.x + pMax.x) * .5, (pMin.y + pMax.y) * .5);//更改鼠标坐标 
	return cv::Size(pMax.x, pMax.y);
}
void getBack2Desk(const cv::Size&screenSize)
{
	keyIn(VK_LWIN,'M');
	return;
}
int main() 
{
	initGDI();
	cv::Mat thisScreen = gdiScreenCapture();
	cv::Size screenSize = getScreenSize();

	getBack2Desk(screenSize);
	keyIn(VK_LWIN, 'R');
	keyIn("123");
	//testClipboard();
	//keyIn(VK_LCONTROL, 'V');
	float k = screenSize.height * 1. / screenSize.width;
	//for(int i=0;i< screenSize.width;i++)	
	//{
	//	SetCursorPos(i, k * i);
	//	//mouse_event(MOUSEEVENTF_RIGHTDOWN , 0, 0, 0, 0);
	//	Sleep(1);
	//	//mouse_event( MOUSEEVENTF_RIGHTUP , 0, 0, 0, 0);
	//}
	return 0;
}
