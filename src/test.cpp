//Press u to update subtract image
//Press e to exit
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <conio.h>
//for sound ctrl
//#include <iomanip>
#include <windows.h>

using namespace std;
using namespace cv;
const int slider_max = 255;
int slider = 34;  //initial valuw of slider
int white_threshold = 100;
char userInput;

Mat subtract_tar,frame, greyMat;
void on_trackbar(int, void*)
{
	double alpha = (double)slider / slider_max;
    white_threshold = slider_max * alpha;

	imshow("Linear Blend", greyMat);

}

int main(int argc, const char** argv)
{


	VideoCapture cap(0); // open the camera 1

	if (!cap.isOpened()) //return -1 when no camera found
		return -1;

	//Mat edges;
	//namedWindow("edges", 1);

	createTrackbar("testTrack", "Linear Blend", &slider, slider_max, on_trackbar);

	cap >> frame;
	cvtColor(frame, subtract_tar, CV_BGR2GRAY);



	for (;;)
	{
		if (_kbhit() )
		{
			switch (_getch())
			{
				case 'u':
					cap >> frame;
					cvtColor(frame, subtract_tar, CV_BGR2GRAY);
					imshow("subtract_target", subtract_tar);
					break;
				case 'e':
                    sh.freeMem();
					return -1;
					break;

			}
		}


		cap >> frame;//frame.rows=480
		cvtColor(frame,greyMat, CV_BGR2GRAY);

		imshow("before", greyMat);
		int whitePixelSum=0;

		greyMat -= subtract_tar;
		for (int j = 0; j<greyMat.rows; j++)
		{
			for (int i = 0; i<greyMat.cols; i++)
			{
				if (greyMat.at<uchar>(j, i) < white_threshold)
					greyMat.at<uchar>(j, i) = 0; //black
				else
				{
					greyMat.at<uchar>(j, i) = 255; //white
					whitePixelSum++;
				}
			}
		}
		createTrackbar("alpha", "Linear Blend", &slider, slider_max, on_trackbar);
		on_trackbar(slider, 0);
		cout << whitePixelSum <<endl;

		waitKey(30);
	}


}
