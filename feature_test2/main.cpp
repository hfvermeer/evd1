#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

// Global variables
Mat originalImage;
Mat grayImage;
int lowThreshold = 25;
int highThreshold = 60;

void onTrackbarChange(int, void*) {
    // Apply Canny edge detection with updated parameters
    Mat rawEdges;
    Canny(grayImage, rawEdges, lowThreshold, highThreshold);

    // Close the edges to fill small gaps
    Mat closedEdges;
    Mat kernelClose = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));  // You can adjust the kernel size as needed
    morphologyEx(rawEdges, closedEdges, MORPH_CLOSE, kernelClose);

    // Find contours in the closed edges
    vector<vector<Point>> contours;
    findContours(closedEdges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Fill the largest controur
    Mat largestContourMask = Mat::zeros(closedEdges.size(), CV_8UC1);
    fillPoly(largestContourMask, contours, Scalar(255));

    // Apply opening to remove small pieces
    Mat resultMask;
    Mat kernelOpen = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));  // Round kernel
    morphologyEx(largestContourMask, resultMask, MORPH_OPEN, kernelOpen);

    // Find contours in the opened edges
    contours.clear();
    findContours(resultMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Find the index of the largest contour based on arc length
    size_t largestContourIndex = 0;
    double largestContourArcLength = 0.0;
    for (size_t i = 0; i < contours.size(); ++i) {
        double arcLengthVal = arcLength(contours[i], true);
        if (arcLengthVal > largestContourArcLength) {
            largestContourArcLength = arcLengthVal;
            largestContourIndex = i;
        }
    }

    // Aproximate the largest contour with a polygon
    vector<Point> resultContour;
    approxPolyDP(contours[largestContourIndex], resultContour, 1.0, true);

    // Draw the result contour on the original image
    Mat resultImage = originalImage.clone();
    drawContours(resultImage, vector<vector<Point>>{resultContour}, 0, Scalar(255, 0, 255), 1);     // Draw the contour
        for (size_t i = 0; i < resultContour.size(); ++i) {
        circle(resultImage, resultContour[i], 1, Scalar(255, 0, 255), 2);                           // Draw a dot on each point
    }                                                                
    
    // Display the number of points in contour in console
    cout << "Number of points in contour: " << resultContour.size() << endl;

    imshow("Edge Detection", resultImage);
}

int main(int argc, char** argv) {
    // Check if the filename is provided
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <image_path>" << endl;
        return -1;
    }

    // Read the image and check if it is loaded successfully
    originalImage = imread(argv[1]);
    if (originalImage.empty()) {
        cout << "Error: Could not read the image." << endl;
        return -1;
    }

    // Resize the image to have a maximum side length of 640 pixels
    int maxSideLength = 640;
    int newWidth = static_cast<int>(originalImage.cols * (maxSideLength / static_cast<double>(max(originalImage.cols, originalImage.rows))));
    int newHeight = static_cast<int>(originalImage.rows * (maxSideLength / static_cast<double>(max(originalImage.cols, originalImage.rows))));
    resize(originalImage, originalImage, Size(newWidth, newHeight));

    // Make a grayscale composite by subtracting blue channel from red channel
    Mat redChannel, blueChannel, greenChannel;
    extractChannel(originalImage, redChannel, 2);
    extractChannel(originalImage, blueChannel, 0);
    grayImage = redChannel - blueChannel;               // Subtract blue channel from red channel  
    grayImage.convertTo(grayImage, -1, 2.0, 0);         // Adjust the contrast so that the edges are more visible
    GaussianBlur(grayImage, grayImage, Size(3, 3), 0);  // Apply Gaussian blur to reduce noise

    // Create a window to display the result image and add trackbars
    namedWindow("Edge Detection", WINDOW_NORMAL);
    createTrackbar("Low Threshold", "Edge Detection", &lowThreshold, 255, onTrackbarChange);
    createTrackbar("High Threshold", "Edge Detection", &highThreshold, 255, onTrackbarChange);

    // Run processing algorithm at least once
    onTrackbarChange(0, nullptr);

    // Wait for a key press
    waitKey(0);

    return 0;
}
