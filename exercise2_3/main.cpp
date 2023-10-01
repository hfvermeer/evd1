#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 2_1, OpenCV version: " << CV_VERSION << std::endl;

    Mat src;

    src = imread("../licenseplate1.jpg",IMREAD_COLOR);
    if(!src.data) {
        std::cout << "Could not open image!" << std::endl;
    }
    else {
        // Create a window source image
        namedWindow("Original image", WINDOW_NORMAL);
        //moveWindow("Original image", 50, 1100);
        //resizeWindow("Original image", 700,500);
        imshow("Original image",src);

        Point2f srcTri[3];
        Point2f dstTri[3];

        Mat warp_dst = Mat::zeros(65,230,src.type());
        srcTri[0] = Point2f(29,67);
        srcTri[1] = Point2f(255,9);
        srcTri[2] = Point2f(26,132);

        dstTri[0] = Point2f(0,0);
        dstTri[1] = Point2f(229,0);
        dstTri[2] = Point2f(0,64);

        Mat warp_mat = getAffineTransform(srcTri,dstTri);
        warpAffine(src,warp_dst,warp_mat,warp_dst.size());

        namedWindow("Warp image", WINDOW_NORMAL);
        //moveWindow("Warp image", 800, 1100);
        resizeWindow("Warp image", 700,300);
        imshow("Warp image",warp_dst);
    }

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "Done!" << std::endl;

    return 0;
}
