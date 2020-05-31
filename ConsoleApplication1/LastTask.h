#pragma once
#pragma once
#pragma once
#include <string>
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

class LastTask {
public:
	cv::Mat GradientEdges(cv::Mat a);
	void ExecuteLast();
};
