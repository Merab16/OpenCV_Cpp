#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


using namespace std;
using namespace cv;

HWND windowHWND = FindWindowA("Albion Online Client", NULL);

Mat getScreen() {
    HDC windowDC = GetDC(windowHWND);
    HDC newDC = CreateCompatibleDC(windowDC);
    int Width = GetDeviceCaps(windowDC, HORZRES);
    int Height = GetDeviceCaps(windowDC, VERTRES);
    HBITMAP hBmp = CreateCompatibleBitmap(windowDC, Width, Height);
    SelectObject(newDC, hBmp);
    BitBlt(newDC, 0, 0, Width, Height, windowDC, 0, 0, SRCCOPY | CAPTUREBLT);
    //Описание рабочего массива бит совместимого контекста в памяти
    BITMAPINFO BMI;
    BMI.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    BMI.bmiHeader.biWidth = Width;
    BMI.bmiHeader.biHeight = -Height;
    BMI.bmiHeader.biPlanes = 1;
    BMI.bmiHeader.biBitCount = 32;
    BMI.bmiHeader.biCompression = BI_RGB;
    Mat screen = Mat(Height, Width, CV_8UC4);
    GetDIBits(newDC, hBmp, 0, Height, screen.data, &BMI, DIB_RGB_COLORS);

    // освобождаем ресурсы
    ReleaseDC(windowHWND, windowDC);
    DeleteObject(hBmp);
    DeleteDC(newDC);
    return screen;
}


int main()
{
    while (true) {
        Mat screen = getScreen();

        namedWindow("output", WINDOW_NORMAL);

        imshow("output", screen);
        waitKey(1);
    }
    return 0;
}