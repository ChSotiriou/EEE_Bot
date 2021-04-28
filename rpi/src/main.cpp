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
        cv::Mat colorFiltered = filterColor(frame, BLACK, true);

        float angle = getAngle(colorFiltered);
        printf("[i] %.3f\n", angle);

        cv::imshow("Line Following", frame);
        
        if (cv::waitKey(1) && 0xff == 27) {
            break;
        }        
    }

    closeCV();

	return 0;
}



