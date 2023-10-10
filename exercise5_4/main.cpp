#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 5_4, OpenCV version: " << CV_VERSION << std::endl;

    Mat src, gray;

    src = imread("../coins.jpg",IMREAD_COLOR);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        cvtColor(src, gray, COLOR_BGR2GRAY);
        // smooth it, otherwise a lot of false circles may be detected
        GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
        //imshow( "blur-circles", gray );
        vector<Vec3f> circles;
        HoughCircles( gray, circles, HOUGH_GRADIENT, 1, 50, 200, 100, 40, 100);
        for( size_t i = 0; i < circles.size(); i++ ) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            // draw the circle center
            circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // draw the circle outline
            circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }
        imshow( "circles", src );
        moveWindow("circles",50,50);

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
