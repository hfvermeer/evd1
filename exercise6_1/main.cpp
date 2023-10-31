#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 6_1, OpenCV version: " << CV_VERSION << std::endl;

    Mat frame,src;
    uint8_t test = (uint8_t)12/0.7;
    VideoCapture capture("../dices.mp4");
    /* Set up blob detector */
    SimpleBlobDetector::Params params;

    /* Delete black areas smaller than 40 pixels or bigger than 100 pixels */
    params.filterByArea = true;
    params.minArea = 40;
    params.maxArea = 100;

    /* Only accept BLOBs with a black color (Frames are thresholded so it is 0 or 255) */
    params.filterByColor = true;
    params.blobColor = 0;

    /* Only accept circular shapes */
    params.filterByCircularity = true;
    params.minCircularity = 0.1;

    params.maxThreshold=255;
    params.minThreshold=210;

    /* Create BLOB detector */
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    /* Create vector creating the blobs found by the detector */
    vector<KeyPoint> blobs;
    if( !capture.isOpened()) {
        std::cout << "Het absolute path naar het bestand '../dices.mp4' is incorrect. Pas het path aan naar het juiste adres om de applicatie te starten." << std::endl;
    }
    else {
    namedWindow("DiceRecognition", WINDOW_AUTOSIZE);
    moveWindow("DiceRecognition", 50, 50);

    while(waitKey(10) != 27) {
        /* Proces next frame */
        capture >> frame;

        /* If there is no next frame, exit */
        if(frame.empty()) break;
        src = frame.clone();
        /* convert image to grayscale */
        cvtColor(frame, frame, COLOR_BGR2GRAY);

        /* Detect BLOBs */
        detector->detect(frame, blobs);

        /* Put a red circle around results */
        drawKeypoints(src, blobs, src, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

        /* Output sum of dices to screen */
        String SumOfDices = format("Total number: %i", static_cast<int>(blobs.size()));
        putText(src, SumOfDices, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(83, 84, 198), 2, LINE_AA);

        /* Output screen in window */
        imshow("DiceRecognition", src);
    }

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    /* Once the loop ended, delete windows and go back to normal state */
    destroyAllWindows();

    std::cout << "Done!" << std::endl;

    }

    return 0;
}
