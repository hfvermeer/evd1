#include <iostream>
#include <opencv2/opencv.hpp>


int main(int, char**) {
    std::cout << "Exercise 2_1, OpenCV version: " << CV_VERSION << std::endl;

    // Use dark_flower.bmp in local folder
    cv::Mat inputImage = cv::imread("C:/embedded/evd1/exercise2_1/dark_flower.bmp", cv::IMREAD_COLOR);
    
    std::vector<cv::Mat> channels;
    cv::split(inputImage, channels);
 
    // Show each channel
    cv::imshow("Blue", channels[0]);
    cv::imshow("Green", channels[1]);
    cv::imshow("Red", channels[2]);

    // Save each channel as a separate image
    cv::imwrite("C:/embedded/evd1/exercise2_1/blue.bmp", channels[0]);
    cv::imwrite("C:/embedded/evd1/exercise2_1/green.bmp", channels[1]);
    cv::imwrite("C:/embedded/evd1/exercise2_1/red.bmp", channels[2]);

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    // Convert the image to a HSV image
    cv::Mat hsvImage;
    cv::cvtColor(inputImage, hsvImage, cv::COLOR_BGR2HSV);

    // Split the HSV image into its channels
    cv::split(hsvImage, channels);
    
    // Show each channel
    cv::imshow("Hue", channels[0]);
    cv::imshow("Saturation", channels[1]);
    cv::imshow("Value", channels[2]);

    // Save each channel as a separate image
    cv::imwrite("C:/embedded/evd1/exercise2_1/hue.bmp", channels[0]);
    cv::imwrite("C:/embedded/evd1/exercise2_1/saturation.bmp", channels[1]);
    cv::imwrite("C:/embedded/evd1/exercise2_1/value.bmp", channels[2]);

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}
