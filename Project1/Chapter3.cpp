#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/imgproc.hpp> 
#include <iostream>


using namespace cv;
using namespace std;


///////////////// Resize and Crope ////////////////////// 


int main() {
	string path = "Resources/test.png";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	resize(img, imgResize, Size(640, 480));

	Rect roi(200, 200, 300, 300);
	imgCrop = img(roi);


	imshow( "Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);
	

	waitKey(0);
	return 0;
}

 