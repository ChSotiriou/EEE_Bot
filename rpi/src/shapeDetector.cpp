#include "shapeDetector.h"

int gaussianSize = 11;    
int threshold1 = 172, threshold2 = 217;
int kernel = 3;

/* 
  Shape Test Matricies
*/
cv::Mat symbols_img[SYMBOL_CNT];

void shapeDetectionSetup() {
  symbols_img[BLUE_SHORTCUT]        = cv::imread("img/BlueShortCut.PNG");
  symbols_img[DISTANCE_MEASUREMENT] = cv::imread("img/DistanceMeasurement.PNG");
  symbols_img[FOLLOW_BLACK]         = cv::imread("img/FollowBlack.PNG");
  symbols_img[FOOTBALL]             = cv::imread("img/Football.PNG");
  symbols_img[GREEN_SHORTCUT]       = cv::imread("img/GreenShortCut.PNG");
  symbols_img[INCLINE_MEASUREMENT]  = cv::imread("img/InclineMeasurement.PNG");
  symbols_img[RED_SHORTCUT]         = cv::imread("img/RedShortCut.PNG");
  symbols_img[SHAPE_COUNTER]        = cv::imread("img/ShapeCounter.PNG");
  symbols_img[STOP_LIGHT]           = cv::imread("img/StopLight.PNG");
  symbols_img[YELLOW_SHORTCUT]      = cv::imread("img/YellowShortCut.PNG");

  for (int i = 0; i < SYMBOL_CNT; i++) {
    cv::resize(symbols_img[i], symbols_img[i], cv::Size(), IMAGE_RESIZE, IMAGE_RESIZE);
    symbols_img[i] = filterColor(symbols_img[i], MAGIC_IMG);
    cv::cvtColor(symbols_img[i], symbols_img[i], cv::COLOR_BGR2GRAY);
  }
}

cv::Mat preprocessImage(cv::Mat frame) {
  cv::Mat ret;
  cv::GaussianBlur(frame, ret, cv::Size(gaussianSize, gaussianSize), 0, 0);
  return ret;
}

contours_s getContours(cv::Mat frame) {
  cv::Mat img = preprocessImage(frame);

  // Find Edges
  cv::Mat canny;
  cv::Canny(img, canny, threshold1, threshold2, kernel);

  // Dilate Image
  cv::Mat maskMorph = cv::getStructuringElement(
    cv::MORPH_ELLIPSE, cv::Size(11, 11)
  );
  cv::dilate(canny, canny, maskMorph);

  // Find Contours
  contours_s contours;
  contours_t cnts;
  cv::findContours(
    canny, cnts, contours.hierarchy, 
    cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE
  );

  // Remove Small Shapes
  for (unsigned int i = 0; i < cnts.size(); i++) {
    contour_t cnt = cnts[i];
    if (cv::contourArea(cnt) > CONTOUR_MIN_AREA) {
      double peri = cv::arcLength(cnt, true);
      cv::approxPolyDP(cnt, cnt, 0.02 * peri, true);
      
      contours.contours.push_back(cnt);
    }
  }

  return contours;
}

cv::Mat getSymbol(SYMBOLS name) {
  return symbols_img[name];
}

int checkImageMatch(cv::Mat transformed) {
  cv::Mat img = transformed.clone();
  for (int i = 0; i < SYMBOL_CNT; i++) {
    float match = compareImages(img, symbols_img[i]);

    if (match >= MATCH_PERCENTAGE) {
      return i;
    }
  }
  return -1;
}
