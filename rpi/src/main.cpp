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
        cv::Mat colorFiltered = filterColor(frame, MAGIC_CARD, true);
        contours_s contours =  getContours(colorFiltered);
        
        // Transform Frame
        if (contours.contours.size() != 0 && contours.contours[0].size() == 4) {
            // cv::drawContours(frameContours, contours.contours, 0, {0, 255, 255}, 4);
            cv::Mat transformed = transformPerspective(contours.contours[0], colorFiltered, 320 * IMAGE_RESIZE, 240 * IMAGE_RESIZE);
            
            cv::cvtColor(transformed, transformed, cv::COLOR_BGR2GRAY);
            int match = checkImageMatch(transformed);
            if (match != -1) {
                if (
                    match == 0 ||
                    match == 2 ||
                    match == 4 ||
                    match == 6 ||
                    match == 9
                ) { // if image is one from irrecognizable group
                    /*
                        Identify which of the four images it actually is
                    */
                    cv::Mat transformedColorFrame = transformPerspective(contours.contours[0], frame, 320 * IMAGE_RESIZE, 240 * IMAGE_RESIZE);
                    frame = transformedColorFrame;

                    int pixelCount[6];                 
                    pixelCount[0] = getPixelCount(transformedColorFrame, BLUE);
                    pixelCount[1] = getPixelCount(transformedColorFrame, GREEN);
                    pixelCount[2] = getPixelCount(transformedColorFrame, RED_LEFT);
                    pixelCount[3] = getPixelCount(transformedColorFrame, RED_RIGHT);
                    pixelCount[4] = getPixelCount(transformedColorFrame, YELLOW);
                    pixelCount[5] = getPixelCount(transformedColorFrame, BLACK);

                    // Find max
                    int maxi = 0;
                    for (int i = 0; i < 6; i++) {
                        if (pixelCount[i] > pixelCount[maxi]) {
                            maxi = i;
                        }
                    }

                    switch (maxi) {
                        case 0:
                            match = BLUE_SHORTCUT;
                            break;
                        case 1:
                            match = GREEN_SHORTCUT;
                            break;
                        case 2:
                        case 3:
                            match = RED_SHORTCUT;
                            break;
                        case 4:
                            match = YELLOW_SHORTCUT;
                            break;
                        case 5:
                            match = FOLLOW_BLACK; 
                            break;
                    } 
                }

                /* 
                    Send Command to Arduino
                */
                if (millis() - shapeDetect_time > DETECTION_DELAY) {
                    printf("[i] Found Match: %d\n", match);

                    generateArduinoCommand(&bot, match);

                    shapeDetect_time = millis();
                }

                // frame = transformed;
            }
        }        

        cv::Mat combined;
        hconcat(frame, colorFiltered, combined);
        cv::imshow("Symbols", combined);
        
        if (cv::waitKey(1) && 0xff == 27) {
            break;
        }        
    }

    closeCV();

	return 0;
}



