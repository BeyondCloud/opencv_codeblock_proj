#ifndef Filter_H
#define Filter_H
using namespace std;
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
class Filter
{

    public:
        Filter();
        void subtractImg(Mat &);
        void setsubtract_tar();

    private:
        Mat subtract_tar;

};

#endif
