#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 6_3b, OpenCV version: " << CV_VERSION << std::endl;

    VideoCapture Img;
    Mat frame;
    Img.open(0);

    /* Check if camera is present */
    if( !Img.isOpened()) {
        std::cout << "Could Not take a snapshot, probably no camera connected." << std::endl;

    }
    else {
        /* Template image */
        Mat templ = imread("../naam.png");
        imshow("Template", templ);
        /* Threshold template image */
        //threshold(templ, templ, 100, 255, 0);

        /* replacement image */
        Mat Replacement = imread("../sb.png");

        /* Single array for template matching */
        Mat aMatch;

        /* Create windows */
        namedWindow("Resultaat", WINDOW_AUTOSIZE);
        //resizeWindow("Resultaat",1600,1200);
        moveWindow("Resultaat",50,50);

        Mat ProcessingFrame;

        // Localizing the best match with minMaxLoc
        double minVal, maxVal;
        Point minLoc, maxLoc, matchLoc;

        while ( waitKey(5) != 27) {
            /* Proces next frame */
            Img >> frame;

            /* If there is no next frame, exit */
            if(frame.empty()) break;

            /* Threshold frame to value 100, deleting not-interesting information */
            threshold(frame, ProcessingFrame, 100, 255, 0);

            /* Calculate frame size for matching patern */
            int result_cols =  ProcessingFrame.cols - templ.cols + 1;
            int result_rows = ProcessingFrame.rows - templ.rows + 1;

            /* Check if template is smaller than the video size. */
            if(result_cols < 0 || result_rows < 0) {
                std::cout << "Formaat van het Template is te groot voor de video en zal nooit matchen." << std::endl;
                break;
            }
            //aMatch.create( result_rows, result_cols, CV_32FC1);

            /* Match by template */
            matchTemplate(ProcessingFrame, templ, aMatch, TM_SQDIFF_NORMED);

            /* Sort the results by most corresponding value */
            minMaxLoc(aMatch, &minVal, &maxVal, &minLoc, &maxLoc);

            /* For method TM_SQDIFF_NORMED use the minimum */
            matchLoc = minLoc;

            /* Values smaller than 0.61 are usable */
            if (minVal < 0.61) {
                /* Copy replacement image to place where template is found */
                Replacement.copyTo(frame(Rect(matchLoc.x + Replacement.cols, matchLoc.y +  Replacement.rows, Replacement.cols, Replacement.rows)));
            }
            /* Output! */
            imshow("Resultaat", frame);
        }

        // Wait for a key press, then kill all windows
        cv::waitKey(0);
        cv::destroyAllWindows();

        /* Once the loop ended, delete windows and go back to normal state */
        destroyAllWindows();
    }

    std::cout << "Done!" << std::endl;

    return 0;
}
