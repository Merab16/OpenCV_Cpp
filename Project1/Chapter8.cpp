#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
#include <Windows.h>


using namespace cv;
using namespace std;


///////////////// Images ////////////////////// 

//void getContours(Mat img, Mat targetCanny) {
//
//	vector<vector<Point>> contours;
//	vector<Vec4i> hierarchy;
//	Canny(img, targetCanny, 25, 50);
//
//	findContours(targetCanny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//	drawContours(img, contours, -1, Scalar(255, 0, 255), 1);
//}



Mat getMat(HWND hWND) {

	HDC deviceContext = GetDC(hWND); // Получает инфу из hWND 
	HDC memoryDiviceContext = CreateCompatibleDC(deviceContext); // создает контроллер домена памяти 

	RECT windowRect;
	GetClientRect(hWND, &windowRect); // получает размеры окна

	// перенос размеров окна в отдельные переменные 
	int height = windowRect.bottom;
	int widht = windowRect.right;

	HBITMAP bitmap = CreateCompatibleBitmap(deviceContext, widht, height); // создает растворовое изображение 


	SelectObject(memoryDiviceContext, bitmap); // заменяет старый объект новым (обновляет окно)
	// copy data into bitmap
	BitBlt(memoryDiviceContext, 0, 0, widht, height, deviceContext, 0, 0, SRCCOPY); // перенос цвета 

	BITMAPINFOHEADER bi; // BITMAPINFOHEADER - структур, которая содержи твсю инфу изображения
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = widht;
	bi.biHeight = -height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 1;
	bi.biYPelsPerMeter = 2;
	bi.biClrUsed = 3;
	bi.biClrImportant = 4;

	Mat mat = Mat(height, widht, CV_8UC4);
	// копирует биты из bitmap в memoryDiviceContext методом DIB_RGB_COLORS
	GetDIBits(memoryDiviceContext, bitmap, 0, height, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	DeleteObject(bitmap);
	DeleteDC(memoryDiviceContext);
	ReleaseDC(hWND, deviceContext);


	return mat;
}



LPCWSTR windowTitle = L"Albion Online Client";
HWND hWND = FindWindow(NULL, windowTitle);
Mat target = getMat(hWND);
Mat templ; Mat result;


int match_method;
int max_Trackbar = 5;



int main() {

	//int hmin = 0, smin = 0, vmin = 0;
	//int hmax = 170, smax = 240, vmax = 255;


	//Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));

	while (!hWND) {
		system("cls");
		cout << "Start the game..." << endl;
		hWND = FindWindow(NULL, windowTitle);
		Sleep(100);
	}


	
	namedWindow("output", WINDOW_NORMAL);
	//namedWindow("Trackbars", (640, 400));
	//createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	//createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	//createTrackbar("Sat Min", "Trackbars", &smin, 255);
	//createTrackbar("Sat Max", "Trackbars", &smax, 255);
	//createTrackbar("Val Min", "Trackbars", &vmin, 255);
	//createTrackbar("Val Max", "Trackbars", &vmax, 255);

	while (true) {
		//windowTitle = L"Albion Online Client";
		hWND = FindWindow(NULL, windowTitle);
		target = getMat(hWND);

		//Mat targetCanny, targetGray, targetDil;
		//cvtColor(target, targetGray, COLOR_BGR2GRAY);
		//blur(targetGray, targetGray, Size(3, 3));
		//int a = 100;
		//Canny(targetGray, targetCanny, a, 2 * a);
		//dilate(targetCanny, targetDil, kernel);

		//Scalar lower(hmin, smin, vmin);
		//Scalar upper(hmax, smax, vmax);

		//Mat targetHSV, mask;
		//cvtColor(target, targetHSV, COLOR_BGR2HSV);
		//inRange(targetHSV, lower, upper, mask);



	//	getContours(target, targetDil);
		imshow("output", target);
		waitKey(1);
	}


	return 0;
}