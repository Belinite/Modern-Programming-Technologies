#include "pch.h"
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include "opencv2/features2d.hpp"
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp" 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "FourthTask.h"
using namespace std;
using namespace cv;

int FourthTask::ExecuteFourth()
{
	// Load image
	cv::Mat image1 = cv::imread("sofa1.jpg");
	cv::Mat image1_gray;
	cv::cvtColor(image1, image1_gray, cv::COLOR_BGR2GRAY);

	cv::Mat image2 = cv::imread("sofa2.jpg");
	cv::Mat image2_gray;
	cv::cvtColor(image2, image2_gray, cv::COLOR_BGR2GRAY);

	// Find keaypoints
	vector<cv::KeyPoint> image1_keypoints;
	vector<cv::KeyPoint> image2_keypoints;

	cv::Mat image1_descriptors;
	cv::Mat image2_descriptors;

	cv::Ptr<cv::Feature2D> orb = cv::ORB::create();
	orb->detectAndCompute(image1_gray, cv::Mat(), image1_keypoints, image1_descriptors);
	orb->detectAndCompute(image2_gray, cv::Mat(), image2_keypoints, image2_descriptors);

	// Match features.
	vector<cv::DMatch> matches;
	cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");
	matcher->match(image1_descriptors, image2_descriptors, matches, cv::Mat());

	// Sort matches by score
	std::sort(matches.begin(), matches.end());

	cout << "Num of image1 features: " << image1_keypoints.size() << endl;
	cout << "Num of image2 features: " << image2_keypoints.size() << endl;
	cout << "Num of matches: " << matches.size() << endl;

	// Find good matches which distance less than 3 times of minimum distance
	std::vector< cv::DMatch > good_matches;

	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance < matches[0].distance * 3)
		{
			good_matches.push_back(matches[i]);
		}
	}
	cout << "Num of matches after filter: " << good_matches.size() << endl;

	// Remove not so good matches
	const int numGoodMatches = matches.size() * 0.15;
	matches.erase(matches.begin() + numGoodMatches, matches.end());


	// Draw top matches
	cv::Mat imMatches;
	cv::drawMatches(image1, image1_keypoints, image2, image2_keypoints, matches, imMatches);
	cv::imshow("matches.jpg", imMatches);
}






