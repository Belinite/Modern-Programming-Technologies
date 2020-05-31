#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "FirstTask.h"

using namespace cv;
using namespace std;

void FirstTask::FactorizeColorLayers(Mat& image)
{
	Mat grayImage1;
	cvtColor(image, grayImage1, COLOR_BGR2GRAY);
	imshow("Image", grayImage1);
	waitKey(0);


	Mat grayImage2 = imread("img1_1.jpg", IMREAD_GRAYSCALE);
	imshow("Image", grayImage2);
	waitKey(0);
}

void FirstTask::Correction(Mat& img)
{
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	double gamma_ = 2.2;
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);
	Mat res = img.clone();
	LUT(img, lookUpTable, res);
	imshow("Contrast image", res);
}

void FirstTask::Histogramm(Mat& img)
{
	vector<Mat> bgr_planes;
	split(img, bgr_planes);
	int histSize = 256;
	float range[] = { 0, 256 }; //the upper boundary is exclusive
	const float* histRange = { range };
	bool uniform = true, accumulate = false;
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("Hist", histImage);
	waitKey();

	cvtColor(img, img, COLOR_BGR2GRAY);
	Mat dst;
	equalizeHist(img, dst);
	imshow("Equalized", dst);
	waitKey();
}

int FirstTask::ExecuteFirstTask()
{
	Mat originalImage = imread("img1_1.jpg", IMREAD_COLOR);
	if (originalImage.empty()) {
		cout << "Error opening image" << endl;
		return -1;
	}
	Mat imageClone2 = originalImage.clone();
	Mat outputImage;

	cvtColor(originalImage, outputImage, COLOR_BGR2RGBA);
	imshow("Image", outputImage);
	waitKey(0);

	Mat imageClone = originalImage.clone();
	FactorizeColorLayers(imageClone);

	Correction(imageClone2);
	Histogramm(imageClone);
}

