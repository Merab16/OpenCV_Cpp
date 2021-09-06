#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>
#include <Windows.h>


using namespace cv;
using namespace std;


///////////////// Images ////////////////////// 
string path = "Resources/lambo.png";
Mat img = imread(path);



Mat imgHSV, mask;
Vec3b pixel;
Vec3b pixelHSV;

float eps = 0.7;

int R, G, B;
int H, S, V;

int hmin = 0, smin = 0, vmin = 0;
int hmax = 179, smax = 255, vmax = 255;


void printCoor(int event, int x, int y, int, void*) {


	switch (event)
	{
	case EVENT_LBUTTONDOWN:

		cout << x << "," << y << endl;
		pixel = img.at<Vec3b>(Point(x, y));
		pixelHSV = imgHSV.at<Vec3b>(Point(x, y));
		H = int(pixelHSV[0]);
		S = int(pixelHSV[1]);
		V = int(pixelHSV[2]);
		hmax = (1 + eps) * H; smax = (1 + eps) * S; vmax = (1 + eps) * V;
		hmin = (1 - eps) * H; smin = (1 - eps) * S; vmin = (1 - eps) * V;
		cout << pixel << endl;
		cout << pixelHSV << endl;


		R = int(pixel[2]);
		G = int(pixel[1]);
		B = int(pixel[0]);
		cout << "R: " << R << endl;
		cout << "G: " << G << endl;
		cout << "B: " << B << endl;
		cout << "Left Button Pressed" << endl;
		break;
	case EVENT_RBUTTONDOWN:
		cout << "Right Button Pressed" << endl;
		break;
	}

}


int main() {
	//resize(img, img, Size(640, 480));
	



	POINT cursorPos;
	int posX, posY;




	/*namedWindow("Trackbars", (640, 400));
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Sat Min", "Trackbars", &smin, 255);
	createTrackbar("Sat Max", "Trackbars", &smax, 255);
	createTrackbar("Val Min", "Trackbars", &vmin, 255);
	createTrackbar("Val Max", "Trackbars", &vmax, 255);*/

	


	
		
	



	while (true) {
		//cap.read(img);
		cvtColor(img, imgHSV, COLOR_BGR2HSV);
		

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);
	

		//imshow("Image HSV", imgHSV);
		imshow("Image RGB", img);
		imshow("Image Mask", mask);
		setMouseCallback("Image RGB", printCoor);
		waitKey(1000/60);

	}



	return 0;
}