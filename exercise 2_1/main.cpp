#include <iostream>
#include <opencv2/opencv.hpp>


int main(int, char**) {
    std::cout << "Exercise 2_1, OpenCV version: " << CV_VERSION << std::endl;

    // Use dark_flower.bmp in local folder
    auto filename = "C:/embedded/opencv/cvtest/dark_flower.bmp";;
    cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR);

    
    // Show image
    cv::imshow("Image", img);
    cv::waitKey(0);


}
