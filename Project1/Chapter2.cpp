#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>


using namespace cv;
using namespace std;


///////////////// Basic Functions ////////////////////// 


int main() {
	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny1, imgCanny2, imgDil, imgErode;

	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny1, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny1, imgDil, kernel);
	erode(imgDil, imgErode, kernel);

	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	imshow("Image Canny1", imgCanny1);
	imshow("Image Dilation", imgDil);
	imshow("Image Erode", imgErode);


	waitKey(0);
	return 0;
}

