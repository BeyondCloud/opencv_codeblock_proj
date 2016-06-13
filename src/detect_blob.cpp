//=============Path of Blob detector=================
//opencv/sources/modules/features2d/src/blobdetector.cpp
//===================================================

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <conio.h>
#include <ctime>
#include "ShareMem.h"
#define MAX_TOUCH 5
TCHAR name[] = TEXT("bitmap");

using namespace std;
using namespace cv;


struct blob {
    int x=0;
    int y=0;
    int size=0;
};

int main(int argc, char *argv[])
{


    VideoCapture cap(0); // open the camera 1
    //=====test code below
    Mat test;
    cap >> test;

    //==============================


	if (!cap.isOpened()) //return -1 when no camera found
		return -1;

    SimpleBlobDetector::Params pDefaultBLOB;
    //minThreshold + n * thresholdStep < maxThreshold ,n=0,1,2...
    pDefaultBLOB.thresholdStep = 9;
    pDefaultBLOB.minThreshold = 10;
    pDefaultBLOB.maxThreshold = 145;
    pDefaultBLOB.minRepeatability = 2;
    pDefaultBLOB.minDistBetweenBlobs = 10;

    pDefaultBLOB.filterByColor = false;
    pDefaultBLOB.blobColor = 0;

    pDefaultBLOB.filterByArea = true;
    pDefaultBLOB.minArea = 40;
    pDefaultBLOB.maxArea = 600;

    pDefaultBLOB.filterByCircularity = false;
    pDefaultBLOB.minCircularity = 0.9f;
    pDefaultBLOB.maxCircularity = (float)1e37;

    pDefaultBLOB.filterByInertia = false;
    pDefaultBLOB.minInertiaRatio = 0.1f;
    pDefaultBLOB.maxInertiaRatio = (float)1e37;

    pDefaultBLOB.filterByConvexity = false;
    pDefaultBLOB.minConvexity = 0.95f;
    pDefaultBLOB.maxConvexity = (float)1e37;

    // Descriptor array for BLOB
    vector<String> typeDesc;
    // Param array for BLOB
    vector<SimpleBlobDetector::Params> pBLOB;
    vector<SimpleBlobDetector::Params>::iterator itBLOB;

    // Color palette,will be used to generate random color to draw circle later
    vector< Vec3b >  palette;
    for (int i = 0; i<65536; i++)
        palette.push_back(Vec3b((uchar)rand(), (uchar)rand(), (uchar)rand()));

    typeDesc.push_back("BLOB");
    pBLOB.push_back(pDefaultBLOB);


    vector<double> desMethCmp;
    Ptr<Feature2D> b;
    b = SimpleBlobDetector::create(*pBLOB.begin());

    // We can detect keypoint with detect method
    vector<KeyPoint>  keyImg;
 // vector<Rect>  zone;
 // vector<vector <Point> >  region;

    Mat subtract_tar,frame, greyMat,result;
    cap >> greyMat;
    greyMat = cv::Mat(greyMat, cv::Rect(40,100,540,200));
	cvtColor(greyMat, subtract_tar, CV_BGR2GRAY);

    Ptr<SimpleBlobDetector> sbd = b.dynamicCast<SimpleBlobDetector>();
    blob blob_table[MAX_TOUCH];
    ShareMem sh(name,sizeof(blob_table));
    vector<KeyPoint>::iterator k;
    while(true){
        clock_t begin = clock();   //this is used to calculate frame rate
        cap >> frame;
       frame = cv::Mat(frame, cv::Rect(40,100,540,200));
      imshow("orig",frame);
        cvtColor(frame,greyMat, CV_BGR2GRAY);
        greyMat -= subtract_tar;

        sbd->detect(greyMat, keyImg, Mat());
        drawKeypoints(greyMat, keyImg, result);

        int i = 0,index=0;
        char sizeTxt[7] = "";
        //cv::Scalar c = cv::Scalar(0,255,0); // text color of circle size

        //iterate over each detected center and draw circle
        //Circle(greyMat, center, radius, color, thickness=1, lineType=8, shift=0)

        for(int i = 0 ; i < MAX_TOUCH;i++)
            blob_table[i].size = 0;
        for (k = keyImg.begin(); k != keyImg.end(); k++, i++)
        {
                    //draw circle use random colors
            circle(greyMat, k->pt, (int)k->size, palette[i % 65536],3);
                    //circle size txt
            sprintf(sizeTxt,"%d", (int)k->size);
            putText(greyMat,sizeTxt ,k->pt, FONT_HERSHEY_DUPLEX,2,Scalar(255,255,255));
            index   = k-keyImg.begin();
           if(index < MAX_TOUCH && index >=0)
            {
                cout<<index;
                Point t = k->pt;
                blob_table[index].x = t.x;
                blob_table[index].y = t.y;
                blob_table[index].size = (int)k->size;
            }
        }

        sh.writeMem(blob_table);
        imshow("area", greyMat);
        waitKey(2);

        if (_kbhit() )
		{
			switch (_getch())
			{
                case 's':
					cap >> frame;
					frame = cv::Mat(frame, cv::Rect(40,100,540,200));
					cvtColor(frame, subtract_tar, CV_BGR2GRAY);
					imshow("subtract_target", subtract_tar);
					break;
                case 'e':
                    sh.freeMem();
                    cap.release();
                    cout << "Release camera\n";
					return -1;
					break;
			}
		}

        clock_t end = clock();
        cout<<"clockCycle="<<CLOCKS_PER_SEC/double(end-begin)<<endl;
    }
    return 0;
}
