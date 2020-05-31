#include "pch.h"
#include <opencv2/opencv.hpp>                                                                     
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp" 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include "SecondTask.h"

using namespace std;
using namespace cv;

void SecondTask::LaplaseOfGaussian(Mat& image)
{
	cout <<
		"\nWrite params for method\n"
		"kernel_size: ";
	int kernel_size;
	cin >> kernel_size;

	cout << "scale: ";
	int scale;
	cin >> scale;

	cout << "delta: ";
	int delta;
	cin >> delta;

	GaussianBlur(image, image, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Mat abs_dst, dst;
	Laplacian(image, dst, CV_16S, kernel_size, scale, delta, BORDER_DEFAULT);

	convertScaleAbs(dst, abs_dst);

	imshow("Image", abs_dst);
	waitKey(0);
}

void SecondTask::Erosion(Mat& image)
{
	cout <<
		"\nWrite params for method\n"
		"erosion_elem from 0 to 2: ";
	int erosion_elem;
	cin >> erosion_elem;

	cout <<
		"erosion_size: ";
	int erosion_size;
	cin >> erosion_size;

	int erosion_type;
	if (erosion_elem == 0)
	{
		erosion_type = MORPH_RECT;
	}
	else if (erosion_elem == 1)
	{
		erosion_type = MORPH_CROSS;
	}
	else if (erosion_elem == 2)
	{
		erosion_type = MORPH_ELLIPSE;
	}
	Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
	Mat erosion_dst;
	erode(image, erosion_dst, element);
	imshow("Image", erosion_dst);
	waitKey(0);
}

void SecondTask::Dilation(Mat& image)
{
	cout <<
		"\nWrite params for method\n"
		"dilation_elem from 0 to 2: ";
	int dilation_elem;
	cin >> dilation_elem;

	cout <<
		"dilation_size: ";
	int dilation_size;
	cin >> dilation_size;

	int dilation_type;

	if (dilation_elem == 0)
	{
		dilation_type = MORPH_RECT;
	}
	else if (dilation_elem == 1)
	{
		dilation_type = MORPH_CROSS;
	}
	else if (dilation_elem == 2)
	{
		dilation_type = MORPH_ELLIPSE;
	}
	Mat element = getStructuringElement(dilation_type, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
	Mat dilation_dst;
	dilate(image, dilation_dst, element);
	imshow("Image", dilation_dst);
	waitKey(0);
}

void SecondTask::Morphology_Operations(int morph_operator, Mat& image)
{
	cout <<
		"\nWrite params for method\n"
		"morph_elem: ";
	int morph_elem;
	cin >> morph_elem;

	cout <<
		"morph_size: ";
	int morph_size;
	cin >> morph_size;

	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	Mat outputImage;
	morphologyEx(image, outputImage, morph_operator, element);
	imshow("Image", outputImage);
	waitKey(0);
}

void SecondTask::Sharpe(Mat& image)
{
	Mat output;
	GaussianBlur(image, output, cv::Size(0, 0), 3);
	cout <<
		"\nWrite params for method\n"
		"alpha: ";
	int alpha;
	cin >> alpha;

	cout << "betta: ";
	int betta;
	cin >> betta;

	cout << "gamma: ";
	int gamma;
	cin >> gamma;

	addWeighted(image, alpha, output, betta, gamma, output);
	imshow("Image", output);
	waitKey(0);
}

void SecondTask::GetSobel(Mat& image)
{
	cout <<
		"\nWrite params for method\n"
		"scale: ";
	int scale;
	cin >> scale;

	cout << "delta: ";
	int delta;
	cin >> delta;

	Mat sobelx;
	Sobel(image, sobelx, CV_32F, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	imshow("Image", sobelx);
	waitKey(0);
}
void SecondTask::ImageLogic(Mat& image)
{
	cout << "\nInput number\n";
	int choice;
	cin >> choice;
	cout << "Your choice is " << choice;

	switch (choice)
	{
	case 0:
	{
		imshow("Image", image);
		waitKey(0);
		break;
	}
	case 1:
	{
		cout <<
			"\nWrite uneven params for method\n"
			"size: ";
		int size;
		cin >> size;
		size % 2 == 0 ? size + 1 : size;

		Mat blurImage;
		blur(image, blurImage, Size(size, size), Point(-1, -1));
		imshow("Image", blurImage);
		waitKey(0);
		break;
	}
	case 2:
	{
		Mat gaussian;
		GaussianBlur(image, gaussian, Size(31, 31), 0, 0);
		imshow("Image", gaussian);
		waitKey(0);
		break;
	}
	case 3:
	{
		Mat median;
		medianBlur(image, median, 31);
		imshow("Image", median);
		waitKey(0);
		break;
	}
	case 4:
	{
		LaplaseOfGaussian(image);
		break;
	}
	case 5:
	{
		GetSobel(image);
		break;
	}
	case 6:
	{
		Sharpe(image);
		break;
	}
	case 7:
	{
		Erosion(image);
		break;
	}
	case 8:
	{
		Dilation(image);
		break;
	}
	case 9:
	{
		Morphology_Operations(2, image);
		break;
	}
	case 10:
	{
		Morphology_Operations(3, image);
		break;
	}
	case 11:
	{
		return;
	}
	}
	ImageLogic(image);
}
int SecondTask::ExecuteSecondTask()
{
	const char *mainText =
		"0 - Original\n"
		"1 - Box filter\n"
		"2 - Gaussian filter\n"
		"3 - Median filter\n"
		"4 - Laplacian of Gaussian filter\n"
		"5 - Sobel filter\n"
		"6 - Sharpening filter\n"
		"7 - Erosion filter\n"
		"8 - Dilation filter\n"
		"9 - Opening filter\n"
		"10 - Closing filter\n"
		"11 - Exit\n";
	cout << mainText;

	Mat originalImage = imread("img1_1.jpg", IMREAD_GRAYSCALE);
	if (originalImage.empty()) {
		cout << "Error opening image" << endl;
		return -1;
	}
	ImageLogic(originalImage);
}
