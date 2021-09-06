#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

bool use_mask;
int match_method;
int max_Trackbar = 5;

Mat img, img_temp, result, mask;
//Mat cam;
string wnd_name = "Image";
string wndRes_name = "Image Result";




void MatchingMethod(int, void*)
{
	Mat img_display;
	img.copyTo(img_display);
	int result_cols = img.cols - img_temp.cols + 1;
	int result_rows = img.rows - img_temp.rows + 1;
	cout << "Img Cols: " << img.cols << endl;
	cout << "Img Rows: " << img.rows << endl;

	cout << "Temp Cols: " << img_temp.cols << endl;
	cout << "Temp Rows: " << img_temp.rows << endl;

	result.create(result_rows, result_cols, CV_32FC1);

	bool method_accepts_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);
	if (use_mask && method_accepts_mask)
	{
		matchTemplate(img, img_temp, result, match_method, mask);
	}
	else
		matchTemplate(img, img_temp, result, match_method);

	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}
	rectangle(img_display, matchLoc, Point(matchLoc.x + img_temp.cols, matchLoc.y + img_temp.rows), Scalar(255, 0, 0), 2, 8, 0);
	rectangle(result, matchLoc, Point(matchLoc.x + img_temp.cols, matchLoc.y + img_temp.rows), Scalar(255, 0, 0), 2, 8, 0);
	imshow(wnd_name, img_display);
	//resize(result, result, img.size());
//	imshow(wndRes_name, result);
	return;
}



int main() {
	//VideoCapture cap(2);
	use_mask = true;
	string path = "D:\\C++\\openCV_proj\\Project1\\Project1\\Resources\\shapes.png";
	string path_temp = "D:\\C++\\openCV_proj\\Project1\\Project1\\Resources\\triangle.jpg";
	img = imread(path);
	img_temp = imread(path_temp);
	//cvtColor(img_temp, img_temp, COLOR_BGR2HSV);
	cvtColor(img_temp, mask, COLOR_BGR2HSV);


	namedWindow(wnd_name, WINDOW_AUTOSIZE);
	//namedWindow(wndRes_name, WINDOW_AUTOSIZE);

	string trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	createTrackbar(trackbar_label, wnd_name, &match_method, max_Trackbar, MatchingMethod);



	//while (true) {
	//	cap.read(cam);
	//	//imshow("Image", cam);
	MatchingMethod(0, 0);
	//	waitKey(1);
	//}



	//imshow("Image", img);
	//imshow("Image Temp", img_temp);

	waitKey(0);
	return 0;
}