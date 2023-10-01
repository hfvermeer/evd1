#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 3_2, OpenCV version: " << CV_VERSION << std::endl;

    Mat src = imread("../ballbar.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        // Show the Original image
        imshow("Original image",src);
        moveWindow("Original image", 50, 100);

        // Create bit image
        Mat dst = src.clone();
        // Threshold
        threshold(src,dst,130,255,THRESH_BINARY_INV);
        // Show the Threshold image
        imshow("Threshold",dst);
        moveWindow("Threshold", 400, 100);

        Mat morph_img = dst.clone();
        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(15,15));
        morphologyEx( dst, morph_img, MORPH_OPEN, kernel);

        // Show the opening image
        imshow("Opening",morph_img);
        moveWindow("Opening", 750, 100);
        Mat result = src.clone();
        result = dst - morph_img;

        // Show the inverse opening image
        bitwise_not(morph_img,morph_img);
        imshow("Inv Opening",morph_img);
        moveWindow("Inv Opening", 1100, 100);

        // Show the Result image
        imshow("Result",result);
        moveWindow("Result", 1400, 100);

        // Show the inverse Result image
        bitwise_not(result,result);
        imshow("Inv Result",result);
        moveWindow("Inv Result", 1700, 100);

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
