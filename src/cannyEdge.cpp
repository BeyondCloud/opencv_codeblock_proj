#include "opencv2/highgui/highgui.hpp"

cv::VideoCapture captureDevice(0);
int main()
{
    while (true)
    {

        cv::Mat source;
        captureDevice.read(source);
        cv::Mat src_host = cv::imread("file.png", cv::IMREAD_GRAYSCALE);
        cv::cuda::GpuMat dst, src;
        cv::cuda::GpuMat d_source(source);
        gpu::GpuMat d_greyscale, d_blurred, d_dst;

        gpu::cvtColor(d_source, d_greyscale, CV_BGR2GRAY);
        gpu::blur(d_greyscale, d_blurred, Size(3, 3));

        int ratio = 3;
        int kernel_size = 3;
        gpu::Canny(d_blurred, d_dst, lowThreshold, lowThreshold * ratio, kernel_size);

        cv::Mat cannyEdge(d_dst);
        cv::imshow("Canny edge video", cannyEdge);


    }
    return 0;
}
