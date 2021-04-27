#ifndef SHAPEDETECTOR_H
#define SHAPEDETECTOR_H

#include "colorRanges.h"
#include "opencv_aee.hpp"
#include "main.hpp"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#define CONTOUR_MIN_AREA 1000
#define SYMBOL_CNT 10
#define MATCH_PERCENTAGE 55

typedef std::vector<cv::Point> contour_t;
typedef std::vector<contour_t> contours_t;
typedef std::vector<cv::Vec4i> hierarchy_t;

enum SYMBOLS {
  BLUE_SHORTCUT,
  DISTANCE_MEASUREMENT,
  FOLLOW_BLACK,
  FOOTBALL,
  GREEN_SHORTCUT,
  INCLINE_MEASUREMENT,
  RED_SHORTCUT,
  SHAPE_COUNTER,
  STOP_LIGHT,
  YELLOW_SHORTCUT
};

struct contours_s {
  contours_t contours;
  hierarchy_t hierarchy;
};

void shapeDetectionSetup();
cv::Mat preprocessImage(cv::Mat frame);
contours_s getContours(cv::Mat frame);

cv::Mat getSymbol(SYMBOLS name);
int checkImageMatch(cv::Mat transformed);

#endif /* SHAPEDETECTOR_H */