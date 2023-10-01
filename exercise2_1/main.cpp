#include <iostream>
#include <opencv2/opencv.hpp>


int main(int, char**) {
    std::cout << "Exercise 2_1, OpenCV version: " << CV_VERSION << std::endl;

    // Use dark_flower.bmp in local folder
    cv::Mat inputImage = cv::imread("./dark_flower.bmp", cv::IMREAD_COLOR);
    
    std::vector<cv::Mat> channels;
    cv::split(inputImage, channels);
 
    // Show each channel
    cv::imshow("Blue", channels[0]);
    cv::imshow("Green", channels[1]);
    cv::imshow("Red", channels[2]);

    // Save each channel as a separate image
    cv::imwrite("./blue.bmp", channels[0]);
    cv::imwrite("./green.bmp", channels[1]);
    cv::imwrite("./red.bmp", channels[2]);

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
    cv::imwrite("./hue.bmp", channels[0]);
    cv::imwrite("./saturation.bmp", channels[1]);
    cv::imwrite("./value.bmp", channels[2]);

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "Done!" << std::endl;

    return 0;
}
