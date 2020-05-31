#include "pch.h"
#include <opencv2/opencv.hpp>                                                                     
#include <opencv2/core.hpp>
#include "opencv2/imgproc.hpp" 
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>
#include "LastLastTask.h"

using namespace std;
using namespace cv;

Mat output1, output2, abs_grad_x, abs_grad_y, grad,
	threshold1, threshold2, threshold3,
	threshold4, threshold5, threshold6,
	threshold7, threshold8, threshold9,
	max_res, max_res1, max_res2,
	output3, output4, abs_grad_x1, abs_grad_y1, grad1, grad3,
	magnitude_result1, magnitude_result, magnitude_result3;

Mat result11, result21, result3, result1_x, result2_y;
Mat resultofadd1, resultofsqrt1, resultofmax1, resultofsqrt3;
Mat abs_result1_x, abs_result2_y;


void LastLastTask::SomeCounts(Mat img)
{

	/*
	*Фильтр для 1 случая
	*/
	float kernelX[25] = {-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,2};
	float kernelY[25] = { -2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2};
	Mat filterX(5, 5, CV_32F, kernelX);
	Mat filterY(5, 5, CV_32F, kernelY);

	/*Функция применяет произвольный 
	линейный фильтр к изображению.*/
	filter2D(img, output1, CV_64F, filterX);
	filter2D(img, output2, CV_64F, filterY);

	/*
	*Преобразование матрицы (derivatives)
	*/
	convertScaleAbs(output1, abs_grad_x);
	convertScaleAbs(output2, abs_grad_y);

	/*
	*Вычисляет взвешенную сумму двух массивов
	*/
	addWeighted(abs_grad_x, 1, abs_grad_y, 1, 0, grad);

	//Максимум
	max_res = max(abs_grad_x, abs_grad_y);

	/*
	*Рассчитывает величину 2D векторов
	*/
	magnitude(output1, output2, magnitude_result);

	/*Функция применяет пороговое значение фиксированного уровня к многоканальному массиву. 
	Эта функция обычно используется для получения двухуровневого (двоичного) изображения из 
	изображения в градациях серого (сравнение также может использоваться для этой цели) или 
	для удаления шума, то есть фильтрации пикселей со слишком маленькими или слишком большими 
	значениями. */
	threshold(magnitude_result, threshold1, 177, 200, THRESH_BINARY);
	threshold(grad, threshold2, 177, 200, THRESH_BINARY);
	threshold(max_res, threshold3, 177, 200, THRESH_BINARY);

	/*
	*Фильтр для 2 случая
	*/
	float kernel2X[25] = { 0,-0.3,0,0.3,0,-0.58,-1,0,1,0.58,-1,-1,0,1,1,-0.58,-1,0,1,0.58,0,-0.3,0,0.3,0};
	float kernel2Y[25] = { 0,-0.58,-1,-0.58,0,-0.3,-1,-1,-1,-0.3,0,0,0,0,0,0.3,1,1,1,0.3,0,0.58,1,0.58,0};

	/*Функция применяет произвольный
	линейный фильтр к изображению.*/
	Mat filter2X(5, 5, CV_32F, kernel2X);
	Mat filter2Y(5, 5, CV_32F, kernel2Y);
	
	/*Функция применяет произвольный
	линейный фильтр к изображению.*/
	filter2D(img, output3, CV_64F, filter2X);
	filter2D(img, output4, CV_64F, filter2Y);

	/*
	*Преобразование матрицы
	*/
	convertScaleAbs(output3, abs_grad_x1);
	convertScaleAbs(output4, abs_grad_y1);

	/*
	*Вычисляет взвешенную сумму двух массивов
	*/
	addWeighted(abs_grad_x1, 0.5, abs_grad_y1, 0.5, 0, grad1);

	//Максимум
	max_res1 = max(abs_grad_x1, abs_grad_y1);

	/*
	*Рассчитывает величину 2D векторов
	*/
	magnitude(output3, output4, magnitude_result1);

	/*Функция применяет пороговое значение фиксированного уровня к многоканальному массиву.
	Эта функция обычно используется для получения двухуровневого (двоичного) изображения из
	изображения в градациях серого (сравнение также может использоваться для этой цели) или
	для удаления шума, то есть фильтрации пикселей со слишком маленькими или слишком большими
	значениями. */
	threshold(magnitude_result1, threshold4, 177, 200, THRESH_BINARY);
    threshold(grad1, threshold5, 177, 200, THRESH_BINARY);
	threshold(max_res1, threshold6, 177, 200, THRESH_BINARY);


	/*Размытие изображения с использованием фильтра Гаусса
	Функция сворачивает исходное изображение с указанным kernel
	*/
	GaussianBlur(img, img, Size(5, 5), 0, 0, BORDER_DEFAULT);

	//Применяем Sobel к x
	Sobel(img, result1_x, CV_64F, 1, 0, 5, 1, 0, BORDER_DEFAULT);
	//Применяем Sobel к y
	Sobel(img, result2_y, CV_64F, 0, 1, 5, 1, 0, BORDER_DEFAULT);

	/*
	*Преобразование матрицы (derivatives)
	*/
	convertScaleAbs(result1_x, abs_result1_x);
	convertScaleAbs(result2_y, abs_result2_y);

	/*
	*Вычисляет взвешенную сумму двух массивов
	*/
	addWeighted(abs_result1_x, 1, abs_result2_y, 1, 0, grad3);

	//Максимум
	max_res2 = max(abs_result1_x, abs_result2_y);

	/*
	*Рассчитывает величину 2D векторов
	*/
	magnitude(result1_x, result2_y, magnitude_result3);

	/*Функция применяет пороговое значение фиксированного уровня к многоканальному массиву.
	Эта функция обычно используется для получения двухуровневого (двоичного) изображения из
	изображения в градациях серого (сравнение также может использоваться для этой цели) или
	для удаления шума, то есть фильтрации пикселей со слишком маленькими или слишком большими
	значениями. */
	threshold(magnitude_result3, threshold5, 177, 200, THRESH_BINARY);
	threshold(grad3, threshold6, 177, 200, THRESH_BINARY);
	threshold(max_res2, threshold7, 177, 200, THRESH_BINARY);

	waitKey(0);
}

void LastLastTask::PrintResult(Mat img)
{
	SomeCounts(img);

	double m = sum(threshold1)[0];
	double k = m / 255;
	cout << "magnitude  = " << k << "\n";
	double m1 = sum(threshold2)[0];
	double k1 = m1 / 255;
	cout << "addWeighted  = " << k1 << "\n";
	double m2 = sum(threshold3)[0];
	double k2 = m2 / 255;
	cout << "max" << k2 << "\n";

	cout << "---------------------------------------------------------------------------" << "\n";

	double p = sum(threshold4)[0];
	double k3 = p / 255;
	cout << "magnitude  = " << k3 << "\n";
	double p1 = sum(threshold5)[0];
	double k4 = p1 / 255;
	cout << "addWeighted = " << k4 << "\n";

	double p2 = sum(threshold6)[0];
	double k5 = p2 / 255;
	cout << "max =  "<< k5 << "\n";

	cout << "-----------------------------------------------------------------------------" << "\n";

	cout << "Sobel" << "\n";
	double c = sum(threshold7)[0];
	double k6 = c / 255;
	cout << "magnitude  = " << k6 << "\n";
	double c1 = sum(threshold8)[0];
	double k7 = c1 / 255;
	cout << "addWeighted = " << k7 << "\n";
	double c2 = sum(threshold9)[0];
	double k8 = c2 / 255;
	cout << "max = " << k8 << "\n";
}


void LastLastTask::ExecuteLast()
{
	Mat originalImage = imread("1.jpg", IMREAD_GRAYSCALE);
	if (originalImage.empty()) {
		cout << "Error opening image" << endl;
		return;
	}
	PrintResult(originalImage);
}
