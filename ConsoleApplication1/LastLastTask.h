#pragma once
#include <string>
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class LastLastTask {
public:
	void SomeCounts(cv::Mat img);
	void PrintResult(cv::Mat img);
	void ExecuteLast();
}; 
