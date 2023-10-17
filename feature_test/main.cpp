#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat src, sharpened, selective, levels, edges, dst;
vector<vector<Point>> contours;
vector<Point> approx;


int main(int argc, char **argv) {
    std::cout << "Pilot for corner count feature extractor, OpenCV version: " << CV_VERSION << std::endl;

    string filename;

    // Get filename from arguments
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    } else {
        std::cout << "Filename: " << argv[1] << std::endl;
        filename = argv[1];
    }

    // Read image
    src=imread(filename);
    if(!src.data) {
        std::cout << "Could not open image!" << CV_VERSION << std::endl;
    }

    else {
        // Possible rotate image if it is in portrait mode
        if (src.cols > src.rows) {
            cv::rotate(src, src, cv::ROTATE_90_CLOCKWISE);
        } 

        // Resize image
        uint16_t originalWidth = src.cols;
        uint16_t originalHeight = src.rows;
        uint16_t newHeight = 720;
        uint16_t newWidth = originalWidth * newHeight / originalHeight;
        cv::resize(src, src, cv::Size(newWidth, newHeight));

        // Show Sharpened Image
        namedWindow("Original Image", WINDOW_AUTOSIZE);
        imshow("Original Image", src);
        moveWindow("Original Image", 25, 25);

        // Split rgb image into channels
        vector<Mat> channels;
        split(src, channels);
     
        // Make selective channel by subtracting the blue channel from the red channel
        selective = channels[2] - channels[0];

        // Show selective channel
        namedWindow("Selective Channel", WINDOW_AUTOSIZE);
        imshow("Selective Channel", selective);
        moveWindow("Selective Channel", 400, 50);

        // Clip levels from 8 to 128 and apply gaussian blur
        threshold(selective, levels, 48, 255, THRESH_TRUNC);
        levels = 48 - levels;
        threshold(levels, levels, 40, 255, THRESH_TRUNC);
        // GaussianBlur(levels, levels, Size(5, 5), 0);

        // Show levels image
        namedWindow("Levels Image", WINDOW_AUTOSIZE);
        imshow("Levels Image", levels);
        moveWindow("Levels Image", 800, 50);

        // Find canny Edges
        Canny(levels, edges, 16, 200, 5);

        // find contours
        findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

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
            drawContours(dst, contours, i, Scalar(0, 255, 0), 2);

        }

        channels[2] = channels[2] | edges;
        // channels[1] = channels[1] | edges2;
        merge(channels, dst);

        // Show debug image
        namedWindow("Result Image", WINDOW_AUTOSIZE);
        imshow("Result Image", dst);
        moveWindow("Result Image", 1200, 50);

        // Sharpen image with 5x5 kernel
        // Mat unsharp = (Mat_<float>(5,5) <<
        //     1,  1,  1,  1,  1,
        //     1,  0,  -2,  0,  1,
        //     1,  -2,  -8,  -2,  1,
        //     1,  0,  -2,  0,  1,
        //     1,  1,  1,  1,  1);
        // filter2D(selective, selective, -1, unsharp);



        // // Apply treshold with val 8 - 255
        // // threshold(blur, treshold, 0, 255, THRESH_BINARY | THRESH_OTSU);
        // threshold(selective, treshold, 24, 255, THRESH_BINARY);

        // // Morph with opening to round of jagged edges
        // Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(45,45));
        // morphologyEx(treshold, treshold, MORPH_OPEN, kernel);

        // // Show treshold image
        // namedWindow("Treshold Image", WINDOW_AUTOSIZE);
        // imshow("Treshold Image", treshold);
        // moveWindow("Treshold Image", 800, 50);

        // // Use canny from treshold to find edges
        // Canny(treshold, edges, 80, 240, 3);

        // // Use canny from green channel to find edges
        // Canny(channels[1], edges2, 80, 240, 3);

        // Add edges to red channel and merge back into debug


        // // Find contours
        // findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);        

        // A


        // Mat gray,bw,dst,guassian,tres,debug;


        // VideoCapture capture(0);

        // namedWindow("Debug", WINDOW_AUTOSIZE);
        // moveWindow("Debug", 50, 150);

        // namedWindow("dst", WINDOW_AUTOSIZE);
        // moveWindow("dst", 50, 100);


        // while(waitKey(30) != 27)
        // {
        //     capture >> src;
        //     // Convert to grayscale
        //     cvtColor(src, gray, COLOR_BGR2GRAY);

        //     // Use gaussian blur to remove noise
        //     GaussianBlur(gray, guassian, Size(5, 5), 0);

        //     // Use threshold to binarize the image
        //     threshold(guassian, tres, 100, 255, THRESH_BINARY);

        //     // Use Canny instead of threshold to catch squares with gradient shading
        //     Canny(tres, bw, 80, 240, 3);



        //     // Copy guassian to debug and convert to color
        //     guassian.copyTo(debug);
        //     cvtColor(debug, debug, COLOR_GRAY2BGR);

        //     // split debug into channels
        //     vector<Mat> channels;
        //     split(debug, channels);

        //     // add canny edges to blue channel
        //     channels[0] = channels[0] | bw;

        //     // merge channels back into debug
        //     merge(channels, debug);

        //     src.copyTo(dst);
        //     for (unsigned int i = 0; i < contours.size(); i++)  // Repeat the number of contours (.size)
        //     {
        //         // Approximate contour with accuracy proportional
        //         // to the contour perimeter
        //         approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

        //         // Skip small or non-convex objects (closed polygon)
        //         if ((contourArea(contours[i])) < 100 || !isContourConvex(approx))
        //             continue;

        //         // Draw the in green contour on debug
        //         drawContours(debug, contours, i, Scalar(0, 255, 0), 1);

        //         // Draw corner points in red on debug
        //         for (unsigned int j = 0; j < approx.size(); j++)
        //             circle(debug, approx[j], 3, Scalar(0, 0, 255), -1);

        //         // Label detected objects
        //         if (approx.size() >= 3 && approx.size() <= 6) {
        //             switch (approx.size()) {
        //             case 3 : setLabel(dst, "TRIANGEL", contours[i]);
        //                 break;
        //             case 4:  setLabel(dst, "RECTANGLE", contours[i]);
        //                 break;
        //             case 5:  setLabel(dst, "PENTAGON", contours[i]);
        //                 break;
        //             case 6:  setLabel(dst, "HEXAGON", contours[i]);
        //                 break;
        //             }
        //         }
        //         else {
        //             // Detect and label circles
        //             double area = contourArea(contours[i]);
        //             Rect r = boundingRect(contours[i]);
        //             int radius = r.width / 2;

        //             if (abs(1 - (static_cast<double>(r.width) / static_cast<double>(r.height))) <= 0.2 &&
        //                     abs(1 - (area / (CV_PI * (radius*radius)))) <= 0.2)
        //                 setLabel(dst, "CIRCLE", contours[i]);
        //         }
        //     }
        //     imshow("Debug", debug);

        waitKey(0);
        destroyAllWindows();

    }

    std::cout << "Done!" << std::endl;

    return 0;
}
