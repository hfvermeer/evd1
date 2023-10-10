#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 6_2, OpenCV version: " << CV_VERSION << std::endl;

    Mat src,work;

    src = imread("../Tekst.bmp",IMREAD_GRAYSCALE);
    if(!src.data) {
        ui->statusBar->showMessage(QString("Could not open image!"),0);
    }
    else {

        double minV, maxV;
        Point minL, maxL;
        Mat MatchingSpace;

        // Show the Original image
        imshow("Original image",src);
        moveWindow("Original image", 50, 100);

        /* Place and size of 'L' */
        int x = 147, y = 21, width = 12, height = 14;
        /* Create template */
        Rect roi_rect(x,y,width,height);
        Mat roi = src(roi_rect);
        //imshow("ROI",roi);
        work = src.clone();

        while (true) {
            MatchingSpace.create(src.cols-(roi.cols+1),src.rows-(roi.rows+1),CV_32F);
            matchTemplate(work, roi, MatchingSpace, TM_CCOEFF_NORMED);
            minMaxLoc(MatchingSpace,&minV,&maxV,&minL,&maxL);

            if (maxV >= 0.53) {
                // set rectangle arounf letter 'L'
                rectangle(src, maxL, Point( maxL.x + roi.cols , maxL.y + roi.rows ), Scalar::all(0), 1, 8, 0 );
                // remove letter 'L' from search (work) image
                rectangle(work,maxL, Point( maxL.x + roi.cols , maxL.y + roi.rows ),Scalar::all(0),FILLED);
            }
            else {
                break; /* no match anymore, stop searching */
            }
        }
        // Show Result and work image
        imshow("Work",work);
        moveWindow("Work", 350, 100);

        imshow( "Result", src );
        moveWindow("Result", 650, 100);

    }

    std::cout << "Done!" << std::endl;

    return 0;
}
