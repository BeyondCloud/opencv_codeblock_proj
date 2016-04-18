#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/xfeatures2d.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/features2d.hpp>
//#include "opencv2/xfeatures2d/nonfree.hpp"


#include <stdio.h>
#include <iostream>

//#include "KeyboardCtrl.h"
//#include "Filter.h"
//#include "opencv2/core/cuda.hpp"
//#include "opencv2/../../../sources/modules/cudaarithm/include/opencv2/cudaarithm.hpp"


int threshold_value = 152;
int threshold_type = 0;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

using namespace std;
using namespace cv;


int main(int argc, char *argv[])
{
    Mat img,img_gray,dst;

    img = imread("test.jpg",1);

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;
    cv::initModule_nonfree() ;
   SurfFeatureDetector detector( minHessian );




    /// Convert the image to Gray
    cvtColor( img, img_gray, COLOR_RGB2GRAY );
    threshold( img_gray, dst, threshold_value, max_BINARY_value,threshold_type );
    imshow("result",dst);
    waitKey(0);



/*
    while(kbctrl.listenKey()){
        cap >> img;
        imshow("cap",img);
        filter.subtractImg(img);
        waitKey(1);
    }
*/
    return 0;
}
