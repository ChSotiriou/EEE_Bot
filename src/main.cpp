// Include files for required libraries
#include "main.hpp"



int main(int argc, char **argv) {
    setupCamera(320, 240);
    shapeDetectionSetup();
    
    cv::namedWindow("Symbols");

    while (1) {

        cv::Mat frame;
        while(frame.empty()) {
            frame = captureFrame();
        } 

        // Filter Colors
        cv::Mat colorFiltered = filterColor(frame, MAGIC_CARD);
        contours_s contours =  getContours(colorFiltered);
        
        cv::Mat frameContours = frame.clone(); 
        cv::Mat frameTransformed = frame.clone();

        // Transform Frame
        if (contours.contours.size() != 0 && contours.contours[0].size()) {
            cv::drawContours(frameContours, contours.contours, 0, {0, 255, 255}, 4);
            frameTransformed = transformPerspective(contours.contours[0], colorFiltered, 320, 240);
            
            cv::cvtColor(frameTransformed, frameTransformed, cv::COLOR_BGR2GRAY);
            int match = checkImageMatch(frameTransformed);
            if (match != -1) {
                printf("%d\n", match);
            }
        }

        

        cv::imshow("Symbols", frameTransformed);
        
        if (cv::waitKey(1) && 0xff == 27) {
            break;
        }
    }

    closeCV();

	return 0;
}



