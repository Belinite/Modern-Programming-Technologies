#pragma once
#include <string>
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class SecondTask {
public:
	int ExecuteSecondTask();
	void LaplaseOfGaussian(cv::Mat& image);
	void Erosion(cv::Mat& image);
	void Dilation(cv::Mat& image);
	void Morphology_Operations(int morph_operator, cv::Mat& image);
	void Sharpe(cv::Mat& image);
	void GetSobel(cv::Mat& image);
	void ImageLogic(cv::Mat& image);
};
