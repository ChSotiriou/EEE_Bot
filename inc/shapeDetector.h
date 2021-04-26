#ifndef SHAPEDETECTOR_H
#define SHAPEDETECTOR_H

#include "colorRanges.h"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

typedef std::vector<std::vector<cv::Point>> contours_t;
typedef std::vector<cv::Vec4i> hierarchy_t;

struct contours_s {
  contours_t contours;
  hierarchy_t hierarchy;
};

cv::Mat preprocessImage(cv::Mat frame);
contours_s getContours(cv::Mat frame);

#endif /* SHAPEDETECTOR_H */