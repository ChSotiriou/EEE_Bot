// Include files for required libraries
#include "main.hpp"



int main(int argc, char **argv) {

    Pi2c i2c(EEEBOT_ADDR);

    robot_s bot = {&i2c};

    wiringPiSetup();
    setupCamera(320 * IMAGE_RESIZE, 240 * IMAGE_RESIZE);
    shapeDetectionSetup();

    uint32_t shapeDetect_time = millis();
    
    cv::namedWindow("Symbols");

    printf("[+] Starting\n");

    while (1) {
        
        cv::Mat frame;
        while(frame.empty()) {
            frame = captureFrame();
        } 

        // Filter Colors
        cv::Mat colorFiltered = filterColor(frame, MAGIC_CARD);
        contours_s contours =  getContours(colorFiltered);
        
        // Transform Frame
        if (contours.contours.size() != 0 && contours.contours[0].size() == 4) {
            // cv::drawContours(frameContours, contours.contours, 0, {0, 255, 255}, 4);
            frame = transformPerspective(contours.contours[0], colorFiltered, 320 * IMAGE_RESIZE, 240 * IMAGE_RESIZE);
            
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
            int match = checkImageMatch(frame);
            if (match != -1) {
                /* 
                    Send Command to Arduino
                */
                if (millis() - shapeDetect_time > 1000) {
                    printf("[i] Found Match: %d\n", match);

                    generateArduinoCommand(&bot, match);

                    shapeDetect_time = millis();
                }
            }
        }        

        cv::imshow("Symbols", frame);
        
        if (cv::waitKey(1) && 0xff == 27) {
            break;
        }        
    }

    closeCV();

	return 0;
}



