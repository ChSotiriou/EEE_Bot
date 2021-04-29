#ifndef SHAPEDETECTOR_H
#define SHAPEDETECTOR_H

#include "colorRanges.h"
#include "opencv_aee.hpp"
#include "main.hpp"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

typedef std::vector<cv::Point> contour_t;
typedef std::vector<contour_t> contours_t;
typedef std::vector<cv::Vec4i> hierarchy_t;

struct contours_s {
  contours_t contours;
  hierarchy_t hierarchy;
};

cv::Mat preprocessImage(cv::Mat frame);
cv::Point getLineCenter(cv::Mat frame);


#endif /* SHAPEDETECTOR_H */