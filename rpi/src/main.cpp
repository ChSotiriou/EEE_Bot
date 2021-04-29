// Include files for required libraries
#include "main.hpp"

int main(int argc, char **argv) {

    Pi2c i2c(EEEBOT_ADDR);

    robot_s bot = {&i2c};

    wiringPiSetup();
    setupCamera(320 * IMAGE_RESIZE, 240 * IMAGE_RESIZE);

    cv::namedWindow("Line Following");    

    printf("[+] Starting\n");

    while (1) {
        cv::Mat frame;
        while(frame.empty()) {
            frame = captureFrame();
        } 

        // Find Line
        cv::Point lineCenter = getLineCenter(frame);
        lineCenter.y += 2 * frame.cols / 3;

        float error = (frame.cols / 2) - lineCenter.x;

        sendError(&bot, error);
        
        if (cv::waitKey(1) && 0xff == 27) {
            break;
        }        
    }

    closeCV();

	return 0;
}



