#include <iostream>

#include "opencv2/opencv.hpp"

int main()
{
    std::cout << CV_VERSION << std::endl;

    auto filename = "../dark_flower.bmp";
    auto image = cv::imread(filename); // cv::Mat

    cv::imshow("image", image);
    cv::waitKey();

    return 0;
}

