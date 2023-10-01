#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 3_2c, OpenCV version: " << CV_VERSION << std::endl;

    Mat src = imread("../ballstripes.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        // Show the Original image
        imshow("ballstripes image",src);
        moveWindow("ballstripes image", 50, 100);

        // Create bit image
        Mat dst = src.clone();
        // Threshold
        threshold(src,dst,130,255,THRESH_BINARY_INV);

        // Show the Threshold image
        imshow("Threshold ballstripes",dst);
        moveWindow("Threshold ballstripes", 450, 100);

        Mat morph_img = src.clone();

        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(10,10));

        morphologyEx( dst, morph_img, MORPH_OPEN, kernel);

        // Show the opening image
        imshow("Result balls",morph_img);
        moveWindow("Result balls", 850, 100);

        // Show the inverted opening image
        bitwise_not(morph_img,morph_img);
        imshow("Inv Result balls",morph_img);
        moveWindow("Inv Result balls", 1100, 100);

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
