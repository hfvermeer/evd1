#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 4_3, OpenCV version: " << CV_VERSION << std::endl;

    Mat src = imread("../gol.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        // Show the Original image
        namedWindow("Original image", WINDOW_NORMAL);
        moveWindow("Original image", 50, 100);
        resizeWindow("Original image",600,600);
        imshow("Original image",src);

        namedWindow("Result", WINDOW_NORMAL);
        moveWindow("Result", 750, 100);
        resizeWindow("Result",600,600);
        int8_t kdata[] = {1, 1, 1, 1, 10, 1, 1, 1, 1};
        Mat kernel1(3,3,CV_8U, kdata);

        Mat dst1 = src.clone(),dst2 = src.clone();
        Mat Arr3 = src.clone(),Arr12 = src.clone(),Arr13 = src.clone();
        // Fill complete image with constant value
        Arr3 = 3; Arr12 = 12; Arr13 = 13;
        while (true) {
            // set all "0" values to 1
            threshold(src,src,1,1,THRESH_BINARY_INV);
            // convolution filter
            filter2D(src,dst1,CV_8U,kernel1);
            // Make copy of result
            dst1.copyTo(dst2);
            // When pixel value in src is 12 or 13, then 255 in result
            inRange(dst1,Arr12,Arr13,dst1);
            // When pixel value in src is 3, then 255 in result
            inRange(dst2,Arr3,Arr3,dst2);
            // put all restult to 1 image
            bitwise_or(dst1,dst2,src);
            // make bitvalue 255 -> 0 black and 0 -> 255 white
            bitwise_not(src,src);
            imshow("Result",src);
                       if (waitKey(100)== 27) break;
        }

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
