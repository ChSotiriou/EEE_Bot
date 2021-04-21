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

#define COLOR_COUNT 6
const char *color[COLOR_COUNT] = {
    "red", "orange", "yellow", "green", "blue", "purple"
};

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
     
    int pixelCount[COLOR_COUNT]; 
    pixelCount[0] = getPixelCount(frameHSV, RED);
    pixelCount[1] = getPixelCount(frameHSV, ORANGE);
    pixelCount[2] = getPixelCount(frameHSV, YELLOW);
    pixelCount[3] = getPixelCount(frameHSV, GREEN);
    pixelCount[4] = getPixelCount(frameHSV, BLUE);
    pixelCount[5] = getPixelCount(frameHSV, PURPLE);

    int maxi = 0;
    for (int i = 0; i < COLOR_COUNT; i++) {
        if (pixelCount[i] > pixelCount[maxi]) {
            maxi = i;
        }
    }
    printf("The majority of the image is %s\n", color[maxi]);

    printf(
    "\
    Red Pixels      %d\n\
    Orange Pixels   %d\n\
    Yellow Pixels   %d\n\
    Green Pixels    %d\n\
    Blue Pixels     %d\n\
    Purple Pixels   %d\n\
    \n", pixelCount[0], pixelCount[1], pixelCount[2], pixelCount[3], pixelCount[4], pixelCount[5]);

	return 0;
}



