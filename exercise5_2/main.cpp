#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 5_2, OpenCV version: " << CV_VERSION << std::endl;



    Mat src=imread("../shapes.jpg");
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }
    else {
        Mat gray,bw,dst;
        vector<vector<Point> > contours;
        vector<Point> approx;

        VideoCapture capture(0);

        namedWindow("dst", WINDOW_AUTOSIZE);
        moveWindow("dst", 50, 100);
        while(waitKey(30) != 27)
        {
            //capture >> src;
            // Convert to grayscale
            cvtColor(src, gray, COLOR_BGR2GRAY);

            // Use Canny instead of threshold to catch squares with gradient shading
            Canny(gray, bw, 80, 240, 3);

            // Find contours
            findContours(bw, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

            src.copyTo(dst);
            for (unsigned int i = 0; i < contours.size(); i++)  // Repeat the number of contours (.size)
            {
                // Approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // Skip small or non-convex objects (closed polygon)
                if ((contourArea(contours[i])) < 100 || !isContourConvex(approx))
                    continue;

                if (approx.size() >= 3 && approx.size() <= 6) {
                    switch (approx.size()) {
                    case 3 : setLabel(dst, "TRIANGEL", contours[i]);
                        break;
                    case 4:  setLabel(dst, "RECTANGLE", contours[i]);
                        break;
                    case 5:  setLabel(dst, "PENTAGON", contours[i]);
                        break;
                    case 6:  setLabel(dst, "HEXAGON", contours[i]);
                        break;
                    }
                }
                else {
                    // Detect and label circles
                    double area = contourArea(contours[i]);
                    Rect r = boundingRect(contours[i]);
                    int radius = r.width / 2;

                    if (abs(1 - (static_cast<double>(r.width) / static_cast<double>(r.height))) <= 0.2 &&
                            abs(1 - (area / (CV_PI * (radius*radius)))) <= 0.2)
                        setLabel(dst, "CIRCLE", contours[i]);
                }
            }
            imshow("dst", dst);
        }
        destroyAllWindows();

        std::cout << "Done!" << std::endl;

    }

    return 0;
}
