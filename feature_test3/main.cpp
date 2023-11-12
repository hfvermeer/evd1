#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Function to perform circle detection
void detectCircles(int, void*);

Mat originalImage;

int main(int argc, char** argv) {
    // Check if the filename is provided
    if (argc != 2) {
        cout << "Usage: ./grape_counter <image_filename>" << endl;
        return -1;
    }

    // Read the image
    originalImage = imread(argv[1], IMREAD_COLOR);

    // Check if the image is loaded successfully
    if (originalImage.empty()) {
        cout << "Could not open or find the image." << endl;
        return -1;
    }

    // Resize the image to 640 pixels for the largest proportion
    double aspectRatio = (double)originalImage.cols / (double)originalImage.rows;
    Size newSize;
    if (aspectRatio > 1.0) {
        newSize = Size(640, static_cast<int>(640 / aspectRatio));
    } else {
        newSize = Size(static_cast<int>(640 * aspectRatio), 640);
    }

    resize(originalImage, originalImage, newSize);

    // Create a window
    namedWindow("Grape Counter", WINDOW_AUTOSIZE);

    // Create trackbar to adjust parameters
    int param1 = 50; // can be adjusted based on the image
    int param2 = 30; // can be adjusted based on the image
    createTrackbar("Param1", "Grape Counter", &param1, 100, detectCircles);
    createTrackbar("Param2", "Grape Counter", &param2, 100, detectCircles);

    // Initial circle detection
    detectCircles(0, 0);

    // Wait for a key press and close the window
    waitKey(0);
    destroyAllWindows();

    return 0;
}

void detectCircles(int, void*) {
    // Convert the image to grayscale
    Mat grayImage;
    cvtColor(originalImage, grayImage, COLOR_BGR2GRAY);

    // Apply GaussianBlur to reduce noise and improve circle detection
    GaussianBlur(grayImage, grayImage, Size(9, 9), 2, 2);

    // Use Hough Circle Transform to detect circles
    vector<Vec3f> circles;
    HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1, grayImage.rows / 8, 200, 100, 0, 0);

    // Draw circles on the original image
    Mat resultImage = originalImage.clone();
    for (size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(resultImage, center, radius, Scalar(0, 255, 0), 2);
    }

    // Display the result image
    imshow("Grape Counter", resultImage);
}
