//for MSVC++ uncomment the following line
#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "FirstTask.h"
#include "SecondTask.h"
#include "Third.h"
#include "FourthTask.h"
#include "LastTask.h"
#include "LastLastTask.h"

using namespace cv;
using namespace std;

void ChooseTask()
{
	const char *mainText =
		"1 - Task\n"
		"2 - Task\n"
		"3 - Task\n"
		"4 - Task\n"
		"5 - Task\n"
		"6 - Task\n";

	cout << mainText;

	cout << "\nInput number\n";
	int choice;
	cin >> choice;

	switch (choice)
	{
		case 1:
		{
			FirstTask first;
			first.ExecuteFirstTask();
			break;
		}
		case 2:
		{
			SecondTask second;
			second.ExecuteSecondTask();
			break;
		}
		case 3:
		{
			Third third;
			third.ExecuteThird();
			break;
		}
		case 4:
		{
			FourthTask fourth;
			fourth.ExecuteFourth();
			break;
		}
		case 5:
		{
			LastTask last;
			last.ExecuteLast();
			break;
		}
		case 6:
		{
			LastLastTask lastLast;
			lastLast.ExecuteLast();
			break;
		}
	}
	ChooseTask();
}

int main(int argc, char** argv)
{
	ChooseTask();
}