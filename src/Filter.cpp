#include "Filter.h"

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "iostream"
using namespace cv;
using namespace std;
VideoCapture cap(0);
Filter::Filter()
{
     setsubtract_tar();
}
void Filter::subtractImg(Mat &src)
{
    cvtColor(src, src, CV_BGR2GRAY);
    src -= subtract_tar;
    imshow("after subtract",src);
}
void Filter::setsubtract_tar()
{

    Mat frame;
    cap >> frame;
    cvtColor(frame, subtract_tar, CV_BGR2GRAY);
    imshow("subtract target",subtract_tar);
}

