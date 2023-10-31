#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**) {
    std::cout << "Exercise 6_3b, OpenCV version: " << CV_VERSION << std::endl;

    /* Load video */
    VideoCapture Img;
    Mat sceneMat;
    Img.open(0);
    /* Check if path is correct */
    if( !Img.isOpened()) {

        std::cout << "Could Not take a snapshot, probably no camera connected." << std::endl;

    } else {

        Mat objectMat = imread("../naam.png", IMREAD_GRAYSCALE);

        namedWindow("img", WINDOW_NORMAL);
        resizeWindow("img",1500,1000);
        moveWindow("img",50,50);

        while(1)  {
            Img >> sceneMat;

            //vector of keypoints
            vector<KeyPoint > keypointsO;
            vector<KeyPoint > keypointsS;

            Mat descriptors_object, descriptors_scene;

            //-- Step 1: Extract keypoints and Calculate descriptors (feature vectors)
            // need the xfeateres2d lib (part of opencv_contrib) for these functions !!
            Ptr<xfeatures2d::SURF> detector = xfeatures2d::SURF::create(400);

            detector->detectAndCompute(sceneMat, Mat(), keypointsS, descriptors_scene);
            detector->detectAndCompute(objectMat, Mat(), keypointsO, descriptors_object);

            //-- Step 2: Matching descriptor vectors using FLANN matcher
            FlannBasedMatcher matcher;
            vector< DMatch > matches;
            matcher.match( descriptors_object, descriptors_scene, matches );

            //-- Quick calculation of max and min distances between keypoints
            double max_dist = 0; double min_dist = 100;

            for( int i = 0; i < descriptors_object.rows; i++ ){
                double dist = matches[i].distance;
                if( dist < min_dist ) min_dist = dist;
                if( dist > max_dist ) max_dist = dist;
            }

            vector< DMatch > good_matches;

            for( int i = 0; i < descriptors_object.rows; i++ ){
                if( matches[i].distance <= 3*min_dist ){
                good_matches.push_back( matches[i]);
                }
            }

            good_matches.reserve(matches.size());

            if( (good_matches.size() >=10)){
                vector< Point2f > obj;
                vector< Point2f > scene;

                for( unsigned int i = 0; i < good_matches.size(); i++ ){
                //-- Get the keypoints from the good matches
                obj.push_back( keypointsO[ good_matches[i].queryIdx ].pt );
                scene.push_back( keypointsS[ good_matches[i].trainIdx ].pt );
                }

                Mat H = findHomography( obj, scene, RANSAC );

                //-- Get the corners from the image_1 ( the object to be "detected" )
                vector< Point2f > obj_corners(4);
                obj_corners[0] = Point(0,0); obj_corners[1] = Point( objectMat.cols, 0 );
                obj_corners[2] = Point( objectMat.cols, objectMat.rows ); obj_corners[3] = Point( 0, objectMat.rows );
                vector< Point2f > scene_corners(4);

                perspectiveTransform( obj_corners, scene_corners, H);

                //-- Draw lines between the corners (the mapped object in the scene - image_2 )
                line( sceneMat, scene_corners[0] , scene_corners[1], 0, 2 ); //TOP line
                line( sceneMat, scene_corners[1] , scene_corners[2], 0, 2 );
                line( sceneMat, scene_corners[2] , scene_corners[3], 0, 2 );
                line( sceneMat, scene_corners[3] , scene_corners[0], 0, 2 );

            }
            imshow("img",sceneMat);
            if(waitKey(30) >= 0) break;
        }
        destroyAllWindows();
    }

    std::cout << "Done!" << std::endl;

    return 0;
}
