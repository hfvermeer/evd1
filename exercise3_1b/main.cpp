#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat src;
Mat dst;

const int blocksize_slider_max = 45;
int blocksize_slider;
int c_slider_max = 255;
int c_slider;

static void on_trackbar( int, void* )
{
    adaptiveThreshold(src,dst,255,ADAPTIVE_THRESH_GAUSSIAN_C,THRESH_BINARY_INV, ((2 + c_slider) | 0x01) , blocksize_slider);
    imshow( "Adaptive Treshold", dst );
}

int main(int, char**) {
    std::cout << "Exercise 3_1b, OpenCV version: " << CV_VERSION << std::endl;

    src = imread("../shading_c.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        // Show the Original image
        imshow("Original image",src);
        moveWindow("Original image", 50, 100);

        blocksize_slider = 5;
        c_slider = 41;

        namedWindow("Adaptive Treshold", WINDOW_AUTOSIZE); // Create Window
        createTrackbar( "Blocksize", "Adaptive Treshold", &blocksize_slider, blocksize_slider_max, on_trackbar );
        createTrackbar( "C", "Adaptive Treshold", &c_slider, c_slider_max, on_trackbar );
        on_trackbar( blocksize_slider, 0 );
    }

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "Done!" << std::endl;

    return 0;
}
