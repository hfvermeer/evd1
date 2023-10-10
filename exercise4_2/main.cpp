#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 4_2, OpenCV version: " << CV_VERSION << std::endl;

    Mat src = Mat::zeros(200,200,CV_8U);
    rectangle(src,Point(50,50),Point(150,150),Scalar(255),FILLED);

    // Show the Source image
    imshow("Source image",src);
    moveWindow("Source image", 50, 100);

    Mat dst1 = src.clone(),dst2 = src.clone(),dst3 = src.clone();
    GaussianBlur(src,dst1,Size(5,5),0);
    GaussianBlur(src,dst2,Size(15,15),0,0);
    GaussianBlur(dst1,dst3,Size(5,5),0,0);

    // Show the Dst1 image
    imshow("Dst1 image",dst1);
    moveWindow("Dst1 image", 500, 100);

    // Show the Dst2 image
    imshow("Dst2 image",dst2);
    moveWindow("Dst2 image", 1000, 100);

    // Show the Dst3 image
    imshow("Dst3 image",dst3);
    moveWindow("Dst3 image", 1500, 100);

    // Wait for a key press, then kill all windows
    cv::waitKey(0);
    cv::destroyAllWindows();

    std::cout << "Done!" << std::endl;

    return 0;
}
