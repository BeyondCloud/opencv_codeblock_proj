
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


int thresh = 100;
int max_thresh = 255;





using namespace std;
using namespace cv;

Mat img,img_gray;

/// Function header
void thresh_callback(int, void* );
int main(int argc, char *argv[])
{


    img = imread("test.jpg",1);

    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;





    /// Convert the image to Gray
    cvtColor( img, img_gray, COLOR_RGB2GRAY );
    //rectangle( img, btnLeft vertex(x,y), topRight vertex(x,y),color, thickness, lineType );
    rectangle( img_gray, Point( 15, 250 ), Point( 250, 50), Scalar( 0, 55, 255 ), +3, 4 );
    circle( img_gray, Point( 500, 200 ), 32.0, Scalar( 0, 0, 255 ), 3, 8 );
    imshow("result",img_gray);


    blur( img_gray, img_gray, Size(3,3) );

    /// Create Window
    char* source_window = "Source";
    namedWindow( source_window, WINDOW_AUTOSIZE );
    imshow( source_window, img );

    createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );

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
/** @function thresh_callback */
void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( img_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( 100,100,100 );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}
