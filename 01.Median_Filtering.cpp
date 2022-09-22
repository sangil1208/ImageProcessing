#include <iostream>
#include <vector>
#include <opencv2/highgui.hpp>
//#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;


void myMedianFilter(InputArray input, OutputArray& output, int windowSize) {
	const Mat& img = input.getMat();
	output.create(img.size(), img.type());
	Mat dst = output.getMat();
	int range = windowSize / 2;
	for (int x = 0; x < img.rows; x++)
		for (int y = 0; y < img.cols; y++) {
			vector<uchar> v;
			for (int t = -range; t <= range; t++) {
				for (int s = -range; s <= range; s++) {
					v.push_back(img.at<uchar>(min(img.rows - 1, max(0, x + t)), min(img.cols - 1, max(0, y + s))));
				}
			}
			sort(v.begin(), v.end());
			dst.at<uchar>(x, y) = v.at(v.size() / 2);
		}
}

int main()
{
	Mat image = imread("E:\\Study\\2022-1학기\\영상처리\\MedianFilterInput.png", 0);

	int window = 5;

	if (window % 2 == 0 || window <= 0) {
		cout << "Window Size Error!" << endl;
		return 0;
	}

	//imshow("Original_Image", image);

	Mat result;
	myMedianFilter(image, result, window);
	imshow("original", image);
	imshow("myMedianFilter result", result);
	cout >> "123";
	imshow("original", image);
	//Mat correct_result;
	//medianBlur(image, correct_result, window);
	//imshow("medianBlur result", correct_result);

	waitKey();

	return 0;
}