// Include files for required libraries
#include "main.hpp"



int main(int argc, char **argv) {
    setupCamera(320, 240);
    cv::namedWindow("Symbols");

    cv::createTrackbar("Low Hue", "Symbols", &myColor.MINH, 179, NULL);      // Create trackbar controls for each HSV limit
    cv::createTrackbar("High Hue", "Symbols", &myColor.MAXH, 179, NULL);

    cv::createTrackbar("Low Sat", "Symbols", &myColor.MINS, 255, NULL);
    cv::createTrackbar("High Sat", "Symbols", &myColor.MAXS, 255, NULL);

    cv::createTrackbar("Low Value", "Symbols", &myColor.MINV, 255, NULL);
    cv::createTrackbar("High Value", "Symbols", &myColor.MAXV, 255, NULL);


    while (1) {

        myColor.MINH   = cv::getTrackbarPos("Low Hue", "Symbols");        // Update the variables with the trackbar setting
        myColor.MAXH   = cv::getTrackbarPos("High Hue", "Symbols");
        myColor.MINS   = cv::getTrackbarPos("Low Sat", "Symbols");
        myColor.MAXS   = cv::getTrackbarPos("High Sat", "Symbols");
        myColor.MINV   = cv::getTrackbarPos("Low Value", "Symbols");
        myColor.MAXV   = cv::getTrackbarPos("High Value", "Symbols");

        cv::Mat frame;
        while(frame.empty()) {
            frame = captureFrame();
        } 

        // filter for pink
        cv::Mat processed = filterColor(frame, myColor);

        cv::Mat combined;
        cv::cvtColor(processed, processed, cv::COLOR_GRAY2BGR);
        cv::hconcat(frame, processed, combined);
        // get contours
        // contours_s contours = getContours(processed);
        // cv::drawContours(processed, contours.contours, -1, (30, 255, 255), 4, cv::LINE_8);

        cv::imshow("Symbols", combined);

        if (cv::waitKey(1) && 0xff == 27) {
            break;
        }
    }

    closeCV();

	return 0;
}



