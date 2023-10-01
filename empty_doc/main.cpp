#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**) {
    std::cout << "Exercise 2_3, OpenCV version: " << CV_VERSION << std::endl;

    Mat src = imread("../shading_c.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {

        // start here

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "Done!" << std::endl;
    }



    return 0;
}
