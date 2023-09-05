#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**){
    std::cout << "Hello, from cvtest! version " << CV_VERSION << std::endl;

    auto filename = "C:/embedded/opencv/cvtest/dark_flower.bmp";
    auto image = cv::imread(filename); // cv::Mat

    cv::imshow("image", image);
    cv::waitKey();

}
