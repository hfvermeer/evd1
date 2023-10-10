#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 4_1, OpenCV version: " << CV_VERSION << std::endl;

    Mat src = imread("../carpet.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        // Show the Original image
        imshow("Original image",src);
        moveWindow("Original image", 50, 100);

        Mat dst = src.clone();
        GaussianBlur(src,dst,Size(17,17),7);

        // Show the Filter image
        imshow("Filter image",dst);
        moveWindow("Filter image", 350, 100);

        threshold(dst,dst,140,255,THRESH_BINARY_INV);
        // Show the Result image
        imshow("Result image",dst);
        moveWindow("Result image", 650, 100);

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
