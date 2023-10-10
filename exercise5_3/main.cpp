#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 5_3, OpenCV version: " << CV_VERSION << std::endl;

    Mat src,dst,dist;

    src = imread("../connectedballs.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
         threshold(src,dst,100,255,THRESH_BINARY_INV);
        // Show the Original image
        imshow("Original image",src);
        moveWindow("Original image", 50, 100);

        distanceTransform(dst,dist,DIST_L1,3); // destination will be a 32-bit floating-point image
        normalize(dist, dist, 0, 255, NORM_MINMAX,CV_8U);  // destination is maped between 0 and 255 and converted to 8-bit grayscale image
        imshow("Distance",dist);
        moveWindow("Distance", 450, 100);

        threshold(dist,dst,100,255,THRESH_BINARY);
        imshow("Dest",dst);
        moveWindow("Dest", 800, 100);

        Mat ndst;
        int balls = connectedComponents(dst,ndst,8);

        normalize(ndst, ndst, 0, 255, NORM_MINMAX,CV_8U); // For showing the found Labels by connectedComponents
        imshow("Labels",ndst);
        moveWindow("Labels",  1200, 100);

        char Text[20]; sprintf(Text,"number of balls = %d",balls-1);
        putText(src, Text, Point(10,10), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(0,0,0), 1, 8);
        imshow("Result",src);
        moveWindow("Result", 1600, 100);

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
