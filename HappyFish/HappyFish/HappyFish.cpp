#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
 
int main() {
	Mat image;
	image = cv::imread("Resource Flies/HappyFish.jpg");

	Mat image2 = image.clone();

	cv::Rect rectangle(40, 90, image.cols - 80, image.rows - 170);

	cv::Mat result;
	cv::Mat bgModel, fgModel;

	cv::grabCut(image,
		result,
		rectangle,
		bgModel, fgModel,
		1,
		cv::GC_INIT_WITH_RECT);
	cout << "ok" << endl;

	cv::compare(result, cv::GC_PR_FGD, result, cv::CMP_EQ);

	cv::Mat foreground(image.size(), CV_8UC3, cv::Scalar(255, 255, 255));

	image.copyTo(foreground, ~result);

	cv::rectangle(image, rectangle, cv::Scalar(255, 255, 255), 1);

	imwrite("img_1.jpg", image);
	
	imwrite("Foregroundjpg", foreground);
	Mat background = image2 - foreground;
	imwrite("Background.jpg", background);

	return 0;
	

}