#ifdef _MSC_VER
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif
//#define _AFXDLL//为了方便是用mfc类  
#include<afxwin.h>  
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


static LPVOID    screenCaptureData = NULL;
static HBITMAP hBitmap;
static HDC hDDC;
static HDC hCDC;
static int nWidth;
static int nHeight;
void initGDI()
{
    nWidth = GetSystemMetrics(SM_CXSCREEN);//得到屏幕的分辨率的x  
    nHeight = GetSystemMetrics(SM_CYSCREEN);//得到屏幕分辨率的y  
    screenCaptureData = new char[nWidth * nHeight * 4];
    memset(screenCaptureData, 0, nWidth);
    // Get desktop DC, create a compatible dc, create a comaptible bitmap and select into compatible dc.  
    hDDC = GetDC(GetDesktopWindow());//得到屏幕的dc  
    hCDC = CreateCompatibleDC(hDDC);//  
    hBitmap = CreateCompatibleBitmap(hDDC, nWidth, nHeight);//得到位图  
    SelectObject(hCDC, hBitmap); //好像总得这么写。  
}
cv::Mat gdiScreenCapture() 
{

    BitBlt(hCDC, 0, 0, nWidth, nHeight, hDDC, 0, 0, SRCCOPY);

    GetBitmapBits(hBitmap, nWidth * nHeight * 4, screenCaptureData);//得到位图的数据，并存到screenCaptureData数组中。  
    cv::Mat img = cv::Mat(cv::Size(nWidth, nHeight), CV_8UC4);//创建一个rgba格式的IplImage,内容为空  
    memcpy(img.data, screenCaptureData, nWidth * nHeight * 4);//这样比较浪费时间，但写的方便。这里必须得是*4，上面的链接写的是*3，这是不对的。  
    cv::Mat img2;
    cv::cvtColor(img, img2, cv::COLOR_BGRA2BGR);
    return img2;
}

