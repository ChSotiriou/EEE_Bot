#include "shapeDetector.h"

int gaussianSize = 11;    
int threshold1 = 172, threshold2 = 217;
int kernel = 3;

cv::Mat preprocessImage(cv::Mat frame) {
  cv::Mat ret;
  cv::GaussianBlur(frame, ret, cv::Size(gaussianSize, gaussianSize), 0, 0);
  cv::cvtColor(ret, ret, cv::COLOR_BGR2GRAY);

  return ret;
}

contours_s getContours(cv::Mat frame) {
  cv::Mat img = preprocessImage(frame);
  img = filterColor(img, MAGIC_CARD);
  
  // Find Edges
  cv::Canny(img, img, threshold1, threshold2, kernel);

  // Dilate Image
  cv::Mat maskMorph = cv::getStructuringElement(
    cv::MORPH_ELLIPSE, cv::Size(5, 5)
  );
  cv::dilate(img, img, maskMorph);

  // Find Contours
  contours_s contours;
  cv::Mat draw_contour = frame.clone();
  cv::findContours(
    img, contours.contours, contours.hierarchy, 
    cv::RETR_TREE, cv::CHAIN_APPROX_NONE
  );

  return contours;
}
