#include "shapeDetector.h"

int gaussianSize = 11;    
int threshold1 = 228, threshold2 = 168;
int kernel = 3;

cv::Mat preprocessImage(cv::Mat frame) {
  cv::Mat ret;
  cv::GaussianBlur(frame, ret, cv::Size(gaussianSize, gaussianSize), 0, 0);
  return ret;
}

cv::Point getLineCenter(cv::Mat frame) {
  cv::Point ret = {0, 0};

  // Crop Frame (bottom third)
  cv::Mat cropped = frame(cv::Rect(0, 2 * frame.rows / 3, frame.cols, frame.rows / 3)); 

  // Convert to grayscale
  cv::Mat gray;
  cv::cvtColor(cropped, gray, cv::COLOR_BGR2GRAY);

  gray = preprocessImage(gray);


  // Add threshold filter
  cv::threshold(gray, gray, 60, 255, cv::THRESH_BINARY_INV);

  // Find Contours
  contours_s contours;
  cv::findContours(
      gray, contours.contours, contours.hierarchy, 
      cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE
  );

  if (contours.contours.size() > 0) {
      cv::Moments M = cv::moments(contours.contours[0]);

      ret.x = (int) (M.m10 / M.m00); 
      ret.y = (int) (M.m01 / M.m00);
  }

  cv::imshow("Line Following", gray);

  return ret;
}
