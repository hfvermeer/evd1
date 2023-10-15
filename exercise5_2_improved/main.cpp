#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

/**
 * Helper function to display text in the center of a contour
 */
void setLabel(Mat& im, const string label, vector<Point>& contour)
{
    int fontface = FONT_HERSHEY_SIMPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;

    Size text = getTextSize(label, fontface, scale, thickness, &baseline);
    Rect r = boundingRect(contour);

    Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    rectangle(im, pt + Point(0, baseline), pt + Point(text.width, -text.height), Scalar(255,255,255), FILLED);
    putText(im, label, pt, fontface, scale, Scalar(0,0,0), thickness, 8);
}


int main(int, char**) {
    std::cout << "Exercise 5_2, OpenCV version: " << CV_VERSION << std::endl;

    Mat src;

    // Mat src=imread("../shapes.jpg");
    // if(!src.data) {
    //     std::cout << "Could not open image!" << CV_VERSION << std::endl;
    // }
    // else {
        Mat gray,bw,dst,guassian,tres,debug;
        vector<vector<Point> > contours;
        vector<Point> approx;

        VideoCapture capture(0);

        namedWindow("Debug", WINDOW_AUTOSIZE);
        moveWindow("Debug", 50, 150);

        namedWindow("dst", WINDOW_AUTOSIZE);
        moveWindow("dst", 50, 100);


        while(waitKey(30) != 27)
        {
            capture >> src;
            // Convert to grayscale
            cvtColor(src, gray, COLOR_BGR2GRAY);

            // Use gaussian blur to remove noise
            GaussianBlur(gray, guassian, Size(5, 5), 0);

            // Use threshold to binarize the image
            threshold(guassian, tres, 100, 255, THRESH_BINARY);

            // Use Canny instead of threshold to catch squares with gradient shading
            Canny(tres, bw, 80, 240, 3);

            // Find contours
            findContours(bw, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);        

            // Copy guassian to debug and convert to color
            guassian.copyTo(debug);
            cvtColor(debug, debug, COLOR_GRAY2BGR);

            // split debug into channels
            vector<Mat> channels;
            split(debug, channels);

            // add canny edges to blue channel
            channels[0] = channels[0] | bw;

            // merge channels back into debug
            merge(channels, debug);

            src.copyTo(dst);
            for (unsigned int i = 0; i < contours.size(); i++)  // Repeat the number of contours (.size)
            {
                // Approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // Skip small or non-convex objects (closed polygon)
                if ((contourArea(contours[i])) < 100 || !isContourConvex(approx))
                    continue;

                // Draw the in green contour on debug
                drawContours(debug, contours, i, Scalar(0, 255, 0), 1);

                // Draw corner points in red on debug
                for (unsigned int j = 0; j < approx.size(); j++)
                    circle(debug, approx[j], 3, Scalar(0, 0, 255), -1);

                // Label detected objects
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
            imshow("Debug", debug);
            imshow("dst", dst);
        }
        destroyAllWindows();

        std::cout << "Done!" << std::endl;

    // }

    return 0;
}
