// Include files for required libraries
#include "main.hpp"



int main(int argc, char **argv) {

    Pi2c i2c(EEEBOT_ADDR);

    robot_s bot = {&i2c};

    wiringPiSetup();
    setupCamera(320, 240);
    shapeDetectionSetup();

    uint32_t shapeDetect_time = millis();
    
    cv::namedWindow("Symbols");

    while (1) {
        
        cv::Mat frame;
        while(frame.empty()) {
            frame = captureFrame();
        } 

        // Filter Colors
        cv::Mat colorFiltered = filterColor(frame, MAGIC_CARD);
        contours_s contours =  getContours(colorFiltered);
        
        // Transform Frame
        if (contours.contours.size() != 0 && contours.contours[0].size()) {
            // cv::drawContours(frameContours, contours.contours, 0, {0, 255, 255}, 4);
            frame = transformPerspective(contours.contours[0], colorFiltered, 320, 240);
            
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
            int match = checkImageMatch(frame);
            if (match != -1) {
                printf("%d\n", match);
                /* 
                    Send Command to Arduino
                */
                if (millis() - shapeDetect_time > 1000) {
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



