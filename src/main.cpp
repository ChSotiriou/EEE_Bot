/*
**********************************************
Tool to make it easier to find the HSV values needed to isolate a chosen colour.
The raw camera feed is shown along with the inRange result. Silders allow the HSV limits to be changed during runtime.
**********************************************
*/

// Include files for required libraries
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

int main( )
{
    cv::namedWindow("HSV Tester");   // Create a GUI window called photo

    int lowH = 0, highH = 179, lowS = 0, highS = 255, lowV = 0, highV = 255;    // Initialise some variables for HSV limits

    cv::createTrackbar("Low Hue", "HSV Tester", &lowH, 179, NULL);      // Create trackbar controls for each HSV limit
    cv::createTrackbar("High Hue", "HSV Tester", &highH, 179, NULL);

    cv::createTrackbar("Low Sat", "HSV Tester", &lowS, 255, NULL);
    cv::createTrackbar("High Sat", "HSV Tester", &highS, 255, NULL);

    cv::createTrackbar("Low Value", "HSV Tester", &lowV, 255, NULL);
    cv::createTrackbar("High Value", "HSV Tester", &highV, 255, NULL);

    cv::Mat frame = cv::imread("img/opencv.png"); // Open an image file and store in a new matrix variable

    while(1)    // Main loop to perform image processing
    {
        lowH    = cv::getTrackbarPos("Low Hue", "HSV Tester");        // Update the variables with the trackbar setting
        highH   = cv::getTrackbarPos("High Hue", "HSV Tester");
        lowS    = cv::getTrackbarPos("Low Sat", "HSV Tester");
        highS   = cv::getTrackbarPos("High Sat", "HSV Tester");
        lowV    = cv::getTrackbarPos("Low Value", "HSV Tester");
        highV   = cv::getTrackbarPos("High Value", "HSV Tester");

        cv::Mat frameHSV;       // Convert the frame to HSV and apply the limits
        cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);
        cv::inRange(frameHSV, cv::Scalar(lowH, lowS, lowV), cv::Scalar(highH, highS, highV), frameHSV);

        cv::Mat comparison;     // Join the two into a single image
        cv::cvtColor(frameHSV, frameHSV, cv::COLOR_GRAY2BGR);   
        cv::hconcat(frame, frameHSV, comparison);

        cv::imshow("HSV Tester", comparison); //Display the image in the window

        int key = cv::waitKey(1);   // Wait 1ms for a keypress (required to update windows

        key = (key==255) ? -1 : key;    // Check if the esc key has been pressed
        if (key == 27)
            break;
	}

	cv::destroyAllWindows();

	return 0;
}



