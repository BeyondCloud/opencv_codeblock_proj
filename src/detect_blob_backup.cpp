#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <conio.h>
#include <ctime>



using namespace std;
using namespace cv;


static void help()
{
    cout << "\n This program demonstrates how to use BLOB to detect and filter region \n"
        "Usage: \n"
        "  ./detect_blob <image1(../data/detect_blob.png as default)>\n"
        "Press a key when image window is active to change descriptor";
}




int main(int argc, char *argv[])
{

    VideoCapture cap(0); // open the camera 1

//
//	if (!cap.isOpened()) //return -1 when no camera found
//		return -1;

    vector<String> fileName;
    Mat img;
    CommandLineParser parser(argc, argv, "{@input |bolb.png| }{h help | | }");

    if (parser.has("h"))
    {
        help();
        return 0;
    }
    fileName.push_back(parser.get<string>("@input"));
    img = imread(fileName[0], IMREAD_COLOR);
   // cap >> img;
    if (img.rows*img.cols <= 0)
    {
        cout << "Image " << fileName[0] << " is empty or cannot be found\n";
        return(0);
    }

    SimpleBlobDetector::Params pDefaultBLOB;
    // This is default parameters for SimpleBlobDetector

    pDefaultBLOB.thresholdStep = 10;
    pDefaultBLOB.minThreshold = 10;
    pDefaultBLOB.maxThreshold = 220;
    pDefaultBLOB.minRepeatability = 2;
    pDefaultBLOB.minDistBetweenBlobs = 10;

    pDefaultBLOB.filterByColor = false;
    pDefaultBLOB.blobColor = 0;

    pDefaultBLOB.filterByArea = true;
    pDefaultBLOB.minArea = 25;
    pDefaultBLOB.maxArea = 50;

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
    {
        palette.push_back(Vec3b((uchar)rand(), (uchar)rand(), (uchar)rand()));
    }
    help();

    // Param for second BLOB detector we want area between 500 and 2900 pixels
    typeDesc.push_back("BLOB");
    pBLOB.push_back(pDefaultBLOB);
    pBLOB.back().filterByArea = true;
    pBLOB.back().minArea = 30;
    pBLOB.back().maxArea = 700;

    vector<double> desMethCmp;
    vector<KeyPoint> keyImg1;
    Ptr<Feature2D> b;
    b = SimpleBlobDetector::create(*pBLOB.begin());

    // We can detect keypoint with detect method
    vector<KeyPoint>  keyImg;
    vector<Rect>  zone;
    vector<vector <Point> >  region;
    Mat   desc, result(img.rows, img.cols, CV_8UC3);


    Mat subtract_tar,frame, greyMat;
    cap >> frame;
	cvtColor(frame, subtract_tar, CV_BGR2GRAY);




    Ptr<SimpleBlobDetector> sbd = b.dynamicCast<SimpleBlobDetector>();

while(true){
        cap >> img;
        imshow("cap",img);

        clock_t begin = clock();
        cvtColor(img,greyMat, CV_BGR2GRAY);
        greyMat -= subtract_tar;
        for (int j = 0; j<greyMat.rows; j++)
        {
            for (int i = 0; i<greyMat.cols; i++)
            {
                if (greyMat.at<uchar>(j, i) < 30)
                    greyMat.at<uchar>(j, i) = 0; //black
                else
                {
                    greyMat.at<uchar>(j, i) = 255; //white
                }
            }
        }



        sbd->detect(greyMat, keyImg, Mat());
        drawKeypoints(greyMat, keyImg, result);

        //guess loop end at here
        int i = 0;
        char sizeTxt[4] = "";
        // text color of circle size
        cv::Scalar c = cv::Scalar(0,255,0);
        //iterate over each detected center and draw circle
        //Circle(image, center, radius, color, thickness=1, lineType=8, shift=0)
        for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); k++, i++)
        {
                    //draw circle use random colors
            //circle(result, k->pt, (int)k->size, palette[i % 65536]);
                    //circle size txt
            sprintf(sizeTxt,"%d", (int)k->size);
            putText(result,sizeTxt ,k->pt, FONT_HERSHEY_DUPLEX,2,c);
        }
        imshow("area", result);
        waitKey(1);
        if (_kbhit() )
		{
			switch (_getch())
			{
                    case 's':
					cap >> frame;
					cvtColor(frame, subtract_tar, CV_BGR2GRAY);
					imshow("subtract_target", subtract_tar);
					break;
				case 'e':
					return -1;
					break;
			}
		}
    clock_t end = clock();
    cout << "clockCycle"<<  CLOCKS_PER_SEC/double(end - begin)<<endl;

}



    return 0;
}
