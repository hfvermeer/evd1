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
    randn(channels[0], 64, 30);
    randn(channels[1], 64, 30);
    randn(channels[2], 64, 30);

    // Merge channels back into image
    merge(channels, 3, Gnoise);
    Gresult = image + Gnoise;

    return Gresult;
}

int main( int argc, char** argv ) {
    
    std::cout << "Exercise 2_2, OpenCV version: " << CV_VERSION << std::endl;

    // Take a snapshot from the camera and show in window
    Mat image = takeSnapshot();
    imshow("Original image", image);

    // Add Guassian noise to snapshot and show in window
    Mat Gnoise = addGuassNoise(image);
    imshow("Gaussian noise", Gnoise);
    
    // Wait until user press some key
    waitKey(0);
 
    // Kill all windows and release camera
    destroyAllWindows();

    // // Check if the image was loaded

    // if (!cap.isOpened()) { // Check if we succeeded
    //     std::cerr << "Could not open capture" << std::endl;
    //     return -1;
    // }

    // // Create a window to display the captured image
    // cv::namedWindow("Camera Image", cv::WINDOW_NORMAL);

    // while (true) {
    //     cv::Mat frame;
    //     cap >> frame; // Capture a frame from the camera

    //     // Check if the frame was captured successfully
    //     if (frame.empty()) {
    //         std::cerr << "Error: Unable to capture a frame" << std::endl;
    //         break;
    //     }

    //     // Add Gaussian noise to the frame
    //     cv::Mat noisyImage;
    //     cv::randn(noisyImage, cv::Scalar(0), cv::Scalar(25)); // Adjust the standard deviation for desired noise level
    //     cv::add(frame, noisyImage, frame);

    //     // Display the noisy image
    //     cv::imshow("Camera Image", frame);

    //     // Press 'q' to exit the loop
    //     if (cv::waitKey(1) == 'q') {
    //         break;
    //     }
    // }

    // // Release the camera and close the window
    // cap.release();
    // cv::destroyAllWindows();

    return 0;
}
