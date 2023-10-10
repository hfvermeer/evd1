#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 5_1, OpenCV version: " << CV_VERSION << std::endl;

    Mat src,dst;

    src = imread("../shading_c.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        // Show the Original image
        imshow("Original image",src);
        moveWindow("Original image", 50, 100);

        Canny(src,dst,120,255);
        imshow("Canny image",dst);
        moveWindow("Canny image", 450, 100);

        // Find number of objects (cells)
        Mat ndst;
        int cells = connectedComponents(dst,ndst,8);

        char Text[20]; sprintf(Text,"number of cells = %d",cells-1);
        putText(src, Text, Point(10,10), FONT_HERSHEY_SIMPLEX, 0.4, Scalar(255,255,255), 1, 8);
        imshow("Original image",src);

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
