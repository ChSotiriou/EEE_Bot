/*
Color Detector
*/

// Include files for required libraries
#include <stdio.h>
#include <iostream>

#include "colorRanges.h"

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

    cv::Mat frameHSV;       // Convert the frame to HSV and apply the limits
    cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);
     
    int redPixels = getPixelCount(frameHSV, RED);
    int greenPixels = getPixelCount(frameHSV, GREEN);
    int bluePixels = getPixelCount(frameHSV, BLUE);

    if (redPixels > greenPixels && redPixels > bluePixels) {
        printf("The majority of the image is red\n");
    } else if (greenPixels > redPixels && greenPixels > bluePixels) {
        printf("The majority of the image is green\n");
    } else if (bluePixels > redPixels && bluePixels > greenPixels) {
        printf("The majority of the image is blue\n");
    } 

    printf(
    "\
    Red Pixels\t\t%d\n\
    Green Pixels\t%d\n\
    Blue Pixels\t\t%d\n\
    \n", redPixels, greenPixels, bluePixels);

	return 0;
}



