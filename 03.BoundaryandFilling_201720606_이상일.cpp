#include <iostream>
#include <vector>
#include <windows.h>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

unsigned char se_data_square[] = { 255, 255, 255, 255, 255, 255, 255, 255, 255 };
unsigned char se_data_cross[] = { 0, 255, 0, 255, 255, 255, 0, 255, 0 };
Mat se(3, 3, CV_8UC1, se_data_square);

Mat X;
Mat image_complement;
Mat boundary;

// mouse clicked
void CallBackFunc(int event, int x, int y, int flag, void* userdata) {

	Mat& rf = *(Mat*)(userdata);
	if (event == EVENT_LBUTTONDOWN) {

		X.at<uchar>(y, x) = 255;
		int prev_cnt = 0;

		while (1) {

			Mat dilate_result;

			// region filling
			
			// Xnext = (Xprev dilate se) && (image - boundary)
			dilate(X, dilate_result, se);
			bitwise_and(dilate_result, image_complement, X);

			// filling result = (boundary) || Xprev
			bitwise_or(X, boundary, rf);

			int cur_cnt = 0;
			for (int y = 0; y < rf.rows; y++) {
				for (int x = 0; x < rf.cols; x++) {
					if (rf.at<uchar>(y, x) == 255)
						cur_cnt += 1;
				}
			}

			// exit when filling result is same as previous filling result
			// it means filling does not extends at some point
			if (cur_cnt == prev_cnt)
				break;

			prev_cnt = cur_cnt;

			imshow("Region Filling", rf);
			waitKey(5);

		}

		return;
	}
}

int main() {

	Mat image = imread("E:\\Study\\2022-1학기\\영상처리\\Profile.png", 0);
	Size image_size = image.size();

	X = Mat::zeros(image_size, CV_8UC1);

	Mat erode_result;
	Mat Region_filling;

	// Boundary extraction, image - (image erode se)
	erode(image, erode_result, se);
	subtract(image, erode_result, boundary);
	subtract(image, boundary, image_complement);

	boundary.copyTo(Region_filling);

	imshow("Region Filling", Region_filling);

	// Callback when mouse clicked
	setMouseCallback("Region Filling", CallBackFunc, &Region_filling);
	waitKey(0);

	return 0;
}