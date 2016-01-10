// OpenCV-color-canvas.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char key = ' ';
	double f = 1000.0/cv::getTickFrequency();

	cv::VideoCapture cap(0);

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	if (!cap.isOpened()) return -1;

	cv::namedWindow("Video", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);
	cv::namedWindow("Processed", CV_WINDOW_AUTOSIZE|CV_WINDOW_FREERATIO);

	cv::Mat src_img, out_img, mask_img;
	cv::Mat dst_img = cv::Mat::zeros(480, 640, CV_8UC3);
	cv::Mat dst2_img = cv::Mat::zeros(480, 640, CV_8UC3);
	cv::bitwise_not(dst2_img, dst2_img);

	vector<Mat> mv;

	cv::Scalar paint(0,0,255);

	while (1) {

		cap >> src_img;
		cv::imshow("Video", src_img);

		char in_key = cv::waitKey(10);
		if (in_key != -1) key = in_key;

		switch (key) {
			case 27:	// quit
			case 'q':
				return 0;
			case ' ':	// return to initial state (no operation)
				cv::imshow("Processed", src_img); break;

			case 'y':
			case 'Y':	// Lab transformation and thresholding to extract yellow area
			{
				Mat lab_img, a_img, b_img;
				cvtColor(src_img, lab_img, CV_BGR2Lab);
				vector<Mat> planes;
				split(lab_img, planes);
				threshold(planes[2], b_img, 128.+40., 255., THRESH_BINARY);
				threshold(planes[1], a_img, 128.-30., 255., THRESH_TOZERO);
				threshold(a_img, a_img, 128.+30., 255., THRESH_BINARY_INV);
				bitwise_and(b_img, a_img, b_img);
				imshow("Processed", b_img); break;
			}

			case 's'://start painting
			case 'S':
			{
				Mat lab_img, a_img, b_img;
				cvtColor(src_img, lab_img, CV_BGR2Lab);
				vector<Mat> planes;
				split(lab_img, planes);
				threshold(planes[2], b_img, 128.+40., 255., THRESH_BINARY);
				threshold(planes[1], a_img, 128.-30., 255., THRESH_TOZERO);
				threshold(a_img, a_img, 128.+30., 255., THRESH_BINARY_INV);
				bitwise_and(b_img, a_img, b_img);

				vector<vector<Point>> contours;
				vector<Vec4i> hierarchy;
				cv::findContours(b_img, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

				int maxk = 0;
				double tmparea, maxarea = cv::contourArea(Mat(contours[0]));
				for ( size_t k = 1; k < contours.size(); k++) {
					if ((tmparea = cv::contourArea(Mat(contours[k]))) > maxarea) {
						maxk = k; maxarea = tmparea;
					}
				}
				cv::drawContours(dst_img, contours, maxk, paint, CV_FILLED, 8, hierarchy);
				cv::drawContours(dst2_img, contours, maxk, cv::Scalar(0,0,0), CV_FILLED, 8, hierarchy);
//				cv::split(dst_img, mv); 
//				cv::add(mv[0],mv[1],mask_img); cv::add(mask_img,mv[2],mask_img);
//				out_img = src_img.clone();
//				mask_img = dst_img.clone();
				cv::bitwise_and(src_img, dst2_img, out_img);
				cv::bitwise_or(out_img, dst_img, out_img);
//				cv::add(src_img,dst_img,out_img);
//				cv::flip(out_img,out_img,1);
				cv::imshow("Processed", out_img); break;
			}
			case 'e':// stop painting
			case 'E':
			{
				cv::bitwise_or(src_img, dst_img, out_img);
				cv::imshow("Processed", out_img); break;
			}
			case 'c':// clear painting
			case 'C':
			{
				dst_img = cv::Mat::zeros(480, 640, CV_8UC3);
				dst2_img = cv::Mat::zeros(480, 640, CV_8UC3);
				cv::bitwise_not(dst2_img, dst2_img);
				cv::imshow("Processed", src_img); break;
				break;
			}
			case 'r':
			case 'R':
			{
				paint = cv::Scalar(0,0,255,0);
				cv::bitwise_or(src_img, dst_img, out_img);
				cv::imshow("Processed", out_img); break;
			}
			case 'g':
			case 'G':
			{
				paint = cv::Scalar(0,255,0,0);
				cv::bitwise_or(src_img, dst_img, out_img);
				cv::imshow("Processed", out_img); break;
			}
			case 'b':
			case 'B':
			{
				paint = cv::Scalar(255,0,0,0);
				cv::bitwise_or(src_img, dst_img, out_img);
				cv::imshow("Processed", out_img); break;
			}
			default:
				break;
		};


	}
	return 0;
}

