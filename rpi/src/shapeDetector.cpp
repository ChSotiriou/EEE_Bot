#include "shapeDetector.h"

int gaussianSize = 11;    
int threshold1 = 228, threshold2 = 168;
int kernel = 3;

cv::Mat preprocessImage(cv::Mat frame) {
  cv::Mat ret;
  cv::GaussianBlur(frame, ret, cv::Size(gaussianSize, gaussianSize), 0, 0);
  return ret;
}

float getAngle(cv::Mat frame) {
  float angle = 0;
  cv::Mat img = preprocessImage(frame);

  // Find Edges
  cv::Mat canny;
  cv::Canny(img, canny, threshold1, threshold2, 3);

  // Dilate Image
  cv::Mat maskMorph = cv::getStructuringElement(
      cv::MORPH_ELLIPSE, cv::Size(5, 5)
  );
  cv::dilate(canny, canny, maskMorph);

  // Find Contours
  contours_s contours;
  cv::findContours(
      canny, contours.contours, contours.hierarchy, 
      cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE
  );

  if (contours.contours.size() > 0) {
      angle = cv::minAreaRect(contours.contours[0]).angle;

      if (angle < -50) angle += 90;
  }

  return angle;
}
