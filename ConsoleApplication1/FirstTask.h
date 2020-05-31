#pragma once
#include <string>
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class FirstTask {
public:
	void FactorizeColorLayers(cv::Mat& image);
	int ExecuteFirstTask();
	void Correction(cv::Mat& img);
	void Histogramm(cv::Mat& img);
};