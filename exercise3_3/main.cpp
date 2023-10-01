#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 3_3, OpenCV version: " << CV_VERSION << std::endl;

    Mat src = imread("../gear.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        // Show the Original image
        imshow("Gear image",src);
        moveWindow("Gear image", 50, 100);

        // Create bit image
        Mat dst = src.clone();
        // Threshold
        threshold(src,dst,130,255,THRESH_BINARY);

        // Floodfill from point (0, 0)
        Mat im_floodfill = dst.clone();
        floodFill(im_floodfill, Point(0,0), Scalar(0));
        // Display images
        imshow("Flood",im_floodfill);
        moveWindow("Flood", 450, 100);
        // Invert floodfilled image
        Mat im_floodfill_inv;
        bitwise_not(im_floodfill, im_floodfill_inv);

        // Combine the two images to get the foreground.
        Mat im_out;
        bitwise_and(dst,im_floodfill_inv,im_out);

        // Display images
        imshow("Floodfilled",im_out);
        moveWindow("Floodfilled", 850, 100);

        // Display images
        imshow("Floodfilled",im_out);
        moveWindow("Floodfilled", 850, 100);

        //  the resulting skeleton
        Mat skel(im_out.size(), CV_8UC1, Scalar(0));
        // needed if in-place processing is not possible
        Mat temp, eroded = im_out.clone();
        Mat kernel = getStructuringElement(MORPH_CROSS, Size(3,3));

        bitwise_not(im_out,im_out);
        do {
            erode(im_out,eroded,kernel);
            dilate(eroded,temp,kernel);
            subtract(im_out,temp,temp);
            bitwise_or(skel,temp,skel);
            eroded.copyTo(im_out);

        } while (countNonZero(im_out));
        imshow("Skeleton", skel);
        moveWindow("Skeleton", 1250, 100);

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
