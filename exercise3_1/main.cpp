#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 3_1, OpenCV version: " << CV_VERSION << std::endl;

    Mat src = imread("../shading_c.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        // Show the Original image
        imshow("Original image",src);
        moveWindow("Original image", 50, 100);

        Mat dst;
        threshold(src,dst,100,255,THRESH_BINARY);
        // Show the Threshold image
        imshow("Threshold",dst);
        moveWindow("Threshold", 350, 100);

        threshold(src,dst,0,255,THRESH_BINARY | THRESH_OTSU);
        // Show the OTSU image
        imshow("OTSU",dst);
        moveWindow("OTSU", 650, 100);

        threshold(src,dst,0,255,THRESH_BINARY | THRESH_TRIANGLE);
        // Show the TRIANGLE image
        imshow("TRIANGLE",dst);
        moveWindow("TRIANGLE", 950, 100);

        adaptiveThreshold(src,dst,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV,15,15);
        // Show the Adaptive image
        imshow("Adaptive",dst);
        moveWindow("Adaptive", 1250, 100);
    }

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "Done!" << std::endl;

    return 0;
}
