#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Метод для отображения картинки
void Show(Mat image)
{
	imshow("Image", image);
	waitKey(0);
}

//Метод для конвертирования в другую цветовую гамму
void ColorTransformation(Mat originalImage, ColorConversionCodes code, Mat outputImage)
{
	cvtColor(originalImage, outputImage, code);
	Show(outputImage);
}

void FactorizeColorLayers(Mat image)
{
	Mat outputImage;
	cvtColor(image, outputImage, COLOR_BGR2GRAY);
	Show(outputImage);

	/*Mat sobelx;
	Sobel(outputImage, sobelx, CV_32F, 1, 0);
	Show(sobelx);*/
	Mat originalImage = imread("img1_1.jpg", IMREAD_GRAYSCALE);
	Show(originalImage);

}

void Correction(Mat img)
{
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	int factor = 256 / 5;
	for (int i = 0; i < 256; ++i)
	{
		p[i] = factor + (i / factor);
	}
	Mat reduced;
    LUT(img, lookUpTable, reduced);
	Show(reduced);
}

int main(int argc, char** argv)
{
	Mat originalImage = imread("img1_1.jpg", IMREAD_COLOR);
	if (originalImage.empty()) {
		cout << "Error opening image" << endl;
		return -1;
	}
	Mat imageClone2 = originalImage.clone();
	Mat outputImage;
	ColorTransformation(originalImage, COLOR_BGR2RGBA, outputImage);

	Mat imageClone = originalImage.clone();
	FactorizeColorLayers(imageClone);

	Correction(imageClone2);
}
