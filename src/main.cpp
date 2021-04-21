/*
Color Detector
*/

// Include files for required libraries
#include <stdio.h>
#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

int main(int argc, char **argv)
{
    // Check argument count
    if (argc != 2) {
        printf("Usage: %s <image>\n", argv[0]);
        exit(1);
    }

    cv::Mat frame = cv::imread(argv[1]); // Open an image file and store in a new matrix variable

    cv::namedWindow("Shape Detection Tester");

    int gaussianSize = 11;    
    cv::createTrackbar("Gaussian Size", "Shape Detection Tester", &gaussianSize, 15, NULL);
    
    int threshold1 = 150, threshold2 = 255;
    cv::createTrackbar("Threshold 1", "Shape Detection Tester", &threshold1, 300, NULL);
    cv::createTrackbar("Threshold 2", "Shape Detection Tester", &threshold2, 300, NULL);


    while (1) {
        gaussianSize    = cv::getTrackbarPos("Gaussian Size", "Shape Detection Tester");
        threshold1      = cv::getTrackbarPos("Threshold 1", "Shape Detection Tester");
        threshold2      = cv::getTrackbarPos("Threshold 2", "Shape Detection Tester");

        cv::Mat processed;
        cv::GaussianBlur(frame, processed, cv::Size(gaussianSize, gaussianSize), 0, 0);
        cv::cvtColor(processed, processed, cv::COLOR_BGR2GRAY);

        cv::Canny(processed, processed, threshold1, threshold2, 3);

        cv::Mat combined, processed_bgr;
        cv::cvtColor(processed, processed_bgr, cv::COLOR_GRAY2BGR);
        cv::hconcat(frame, processed_bgr, combined); 

        cv::imshow("Shape Detection Tester", combined);

        if (cv::waitKey(1) && 0xff == 27) {
            break;
        }
    }

    cv::destroyAllWindows();

	return 0;
}



