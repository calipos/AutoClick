#ifdef _MSC_VER
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif
//#define _AFXDLL//Ϊ�˷�������mfc��  
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
    nWidth = GetSystemMetrics(SM_CXSCREEN);//�õ���Ļ�ķֱ��ʵ�x  
    nHeight = GetSystemMetrics(SM_CYSCREEN);//�õ���Ļ�ֱ��ʵ�y  
    screenCaptureData = new char[nWidth * nHeight * 4];
    memset(screenCaptureData, 0, nWidth);
    // Get desktop DC, create a compatible dc, create a comaptible bitmap and select into compatible dc.  
    hDDC = GetDC(GetDesktopWindow());//�õ���Ļ��dc  
    hCDC = CreateCompatibleDC(hDDC);//  
    hBitmap = CreateCompatibleBitmap(hDDC, nWidth, nHeight);//�õ�λͼ  
    SelectObject(hCDC, hBitmap); //�����ܵ���ôд��  
}
cv::Mat gdiScreenCapture() 
{

    BitBlt(hCDC, 0, 0, nWidth, nHeight, hDDC, 0, 0, SRCCOPY);

    GetBitmapBits(hBitmap, nWidth * nHeight * 4, screenCaptureData);//�õ�λͼ�����ݣ����浽screenCaptureData�����С�  
    cv::Mat img = cv::Mat(cv::Size(nWidth, nHeight), CV_8UC4);//����һ��rgba��ʽ��IplImage,����Ϊ��  
    memcpy(img.data, screenCaptureData, nWidth * nHeight * 4);//�����Ƚ��˷�ʱ�䣬��д�ķ��㡣����������*4�����������д����*3�����ǲ��Եġ�  
    cv::Mat img2;
    cv::cvtColor(img, img2, cv::COLOR_BGRA2BGR);
    return img2;
}

