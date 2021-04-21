/*
Color Detector
*/

// Include files for required libraries
#include "main.hpp"

int main(int argc, char **argv)
{
    // Check argument count
    if (argc != 2) {
        printf("Usage: %s <image>\n", argv[0]);
        exit(1);
    }

    cv::Mat frame = cv::imread(argv[1]); // Open an image file and store in a new matrix variable

    cv::namedWindow("Shape Detection Tester");

    int gaussianSize = 11;    
    cv::createTrackbar("Gaussian Size", "Shape Detection Tester", &gaussianSize, 15, NULL);
    
    int threshold1 = 172, threshold2 = 217;
    cv::createTrackbar("Threshold 1", "Shape Detection Tester", &threshold1, 300, NULL);
    cv::createTrackbar("Threshold 2", "Shape Detection Tester", &threshold2, 300, NULL);


    while (1) {
        gaussianSize    = cv::getTrackbarPos("Gaussian Size", "Shape Detection Tester");
        threshold1      = cv::getTrackbarPos("Threshold 1", "Shape Detection Tester");
        threshold2      = cv::getTrackbarPos("Threshold 2", "Shape Detection Tester");

        // Preprocess Image
        cv::Mat processed;
        cv::GaussianBlur(frame, processed, cv::Size(gaussianSize, gaussianSize), 0, 0);
        cv::cvtColor(processed, processed, cv::COLOR_BGR2GRAY);

        // Find Edges
        cv::Canny(processed, processed, threshold1, threshold2, 3);

        // Dilate Image
        cv::Mat maskMorph = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
        cv::dilate(processed, processed, maskMorph);

        // Find Contours
        contours_t contours;
        hierarchy_t hierarchy;
        cv::Mat draw_contour = frame.clone();
        cv::findContours(processed, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
        cv::drawContours(draw_contour, contours, -1, (255, 255, 255), cv::LINE_8);

        cv::Mat combined, processed_bgr;
        cv::cvtColor(processed, processed_bgr, cv::COLOR_GRAY2BGR);
        cv::hconcat(frame, processed_bgr, combined);
        cv::hconcat(combined, draw_contour, combined);

        cv::imshow("Shape Detection Tester", combined);

        if (cv::waitKey(1) && 0xff == 27) {
            break;
        }
    }

    cv::destroyAllWindows();

	return 0;
}



