#include <iostream>
#include <opencv2/opencv.hpp>


int main(int, char**) {
    std::cout << "Exercise 2_1, OpenCV version: " << CV_VERSION << std::endl;

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "Done!" << std::endl;

    return 0;
}
