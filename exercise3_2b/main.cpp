#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 3_2b, OpenCV version: " << CV_VERSION << std::endl;

    Mat src = imread("../bars.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
                // Show the Original image
        imshow("bars image",src);
        moveWindow("bars image", 50, 100);

        // Create bit image
        Mat dst = src.clone();
        // Threshold
        threshold(src,dst,130,255,THRESH_BINARY_INV);
        // Show the Threshold image
        imshow("Threshold bars",dst);
        moveWindow("Threshold bars", 400, 100);

        Mat morph_img = src.clone();

        // Mat kernel1 = getStructuringElement(MORPH_RECT, Size(1,5));
        int kdata1[] = {1,1,1,1,1};
        Mat kernel1 (5,1,CV_8U,kdata1);

        Mat kernel2 = getStructuringElement(MORPH_RECT, Size(19,1));

        // Get Vertical Bar
        morphologyEx( dst, morph_img, MORPH_OPEN, kernel1);

        // Show the Opening image
        imshow("Result 1",morph_img);
        moveWindow("Result 1", 750, 100);

        // Show the inverted opening image
        bitwise_not(morph_img,morph_img);
        imshow("Inv Result 1",morph_img);
        moveWindow("Inv Result 1", 1050, 100);

        // Get Horizontal Bars
        morphologyEx( dst, morph_img, MORPH_OPEN, kernel2);

        // Show the Opening image
        imshow("Result 2",morph_img);
        moveWindow("Result 2", 1400, 100);

        // Show the inverted opening image
        bitwise_not(morph_img,morph_img);
        imshow("Inv Result 2",morph_img);
        moveWindow("Inv Result 2", 1700, 100);

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
