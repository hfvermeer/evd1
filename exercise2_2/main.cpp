#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

Mat takeSnapshot(void) {
    Mat image;
    VideoCapture cap(0);

    cap >> image;

    return image;
}

Mat addGuassNoise(Mat image) {
    // Create local structures
    Mat Gnoise = image.clone();
    Mat channels[3];
    Mat Gresult;
    
    // Split image into channels
    split(Gnoise, channels);

    // Add noise to each channel
    randn(channels[0], 128, 30);
    randn(channels[1], 128, 30);
    randn(channels[2], 128, 30);

    // Merge channels back into image
    merge(channels, 3, Gnoise);
    Gresult = image + Gnoise - 128;

    return Gresult;
}

Mat addSaltPepperNoise(Mat image) {
    // Create local structures
    Mat SPnoise = Mat::zeros(image.rows, image.cols, CV_8U);
    randu(SPnoise, 0, 255);

    Mat salt = SPnoise > 225;
    Mat pepper = SPnoise < 30;

    Mat SPresult = image.clone();
    SPresult.setTo(255, salt);
    SPresult.setTo(0, pepper);

    return SPresult;
}

int main( int argc, char** argv ) {
    
    std::cout << "Exercise 2_2, OpenCV version: " << CV_VERSION << std::endl;

    // Take a snapshot from the camera and show in window
    Mat image = takeSnapshot();
    imshow("Original image", image);

    // Add Guassian noise to snapshot and show in window
    Mat Gnoise = addGuassNoise(image);
    imshow("Gaussian noise", Gnoise);
    
    // Add some salt and pepper noise to snapshot and show in window
    Mat SPnoise = addSaltPepperNoise(image);
    imshow("Salt and pepper noise", SPnoise);

    // Wait until user press some key, then close all windows
    waitKey(0);
    destroyAllWindows();

    // Show the original noisy barn image
    Mat barn = imread("../barn_noisy.jpg", IMREAD_COLOR);
    imshow("Original barn image", barn);

    // Blur the image with a 5x5 gaussian blur
    Mat barn_blur;
    cv::GaussianBlur(barn, barn_blur, Size(5, 5), 0, 0);
    imshow("Barn image with 5x5 gaussian blur", barn_blur);

    // Blur the image with a Laplacian filter
    Mat barn_laplace;
    Mat barn_laplace_result;
    cv::Laplacian(barn, barn_laplace, CV_8U, 3);
    barn_laplace_result = barn - barn_laplace;
    imshow("Barn image with Laplacian filter", barn_laplace_result);

    // Blur the image with a median filter
    Mat barn_median;
    cv::medianBlur(barn, barn_median, 3);
    imshow("Barn image with median filter", barn_median);

    // Wait until user press some key, then close all windows
    waitKey(0);
    destroyAllWindows();
   
    // Add Guassian noise to barn image and show in window

    return 0;
}
