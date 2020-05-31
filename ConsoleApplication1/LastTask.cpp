#include "pch.h"
#include <opencv2/opencv.hpp>                                                                     
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp" 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <iostream>
#include <string>
#include "LastTask.h"

using namespace std;
cv::RNG rng(12345);

cv::Mat LastTask::GradientEdges(cv::Mat a) {
	cv::Mat gradient_edges;
	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y;

	cv::Sobel(a, grad_x, -1, 1, 0, 3);
	cv::Sobel(a, grad_y, -1, 0, 1, 3);
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, gradient_edges);

	return gradient_edges;
}

void LastTask::ExecuteLast()
{
	// Load image
	cv::Mat image1 = cv::imread("1.jpg");
	if (image1.empty()) {
		cout << "Error opening image" << endl;
		return;
	}
	cv::cvtColor(image1, image1, cv::COLOR_BGR2RGB);
	cv::Mat image1_gray;
	cv::cvtColor(image1, image1_gray, cv::COLOR_BGR2GRAY);

	// Detect edges by gradient
	cv::Mat gradient_edges;
	cv::Mat grad_x, grad_y;
	cv::Mat abs_grad_x, abs_grad_y;

	gradient_edges = GradientEdges(image1_gray);
	cv::imshow("Gradient edges", gradient_edges);

	// Detect edges by Canny
	cv::Mat canny_edges;
	cv::Canny(image1_gray, canny_edges, 10, 350);
	cv::namedWindow("Canny");
	cv::imshow("Canny", canny_edges);

	// Detect edges for color channes
	// RGB
	std::vector<cv::Mat> channels;
	cv::split(image1, channels);
	cv::imshow("R channels gradient edges", GradientEdges(channels[0]));
	cv::imshow("G channels gradient edges", GradientEdges(channels[1]));
	cv::imshow("B channels gradient edges", GradientEdges(channels[2]));

	// HSV
	cv::Mat hsv;
	cv::cvtColor(image1, hsv, CV_RGB2HSV);
	cv::split(hsv, channels);
	cv::imshow("H channels gradient edges", GradientEdges(channels[0]));
	cv::imshow("S channels gradient edges", GradientEdges(channels[1]));
	cv::imshow("V channels gradient edges", GradientEdges(channels[2]));

	// Find contours
	vector<vector<cv::Point> > contours;
	vector<cv::Vec4i> hierarchy;
	cv::Mat drawing = cv::Mat::zeros(canny_edges.size(), CV_8UC3);
	findContours(canny_edges, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size(); i++)
	{

		cv::Scalar color = cv::Scalar(255, 255, 255);
		drawContours(drawing, contours, (int)i, color, 1, cv::LINE_8, hierarchy, 0);

	}
	cv::imshow("Contours", drawing);
	cv::waitKey(0);
}