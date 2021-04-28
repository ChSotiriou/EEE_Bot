#include "colorRanges.h"

int getPixelCount(cv::Mat frame, struct colorRange range) {
  cv::Mat output = filterColor(frame, range, false);
  return cv::countNonZero(output);
}

cv::Mat filterColor(cv::Mat frame, struct colorRange range, bool bgr = true) {
  cv::Mat ret;
  cv::cvtColor(frame, ret, cv::COLOR_BGR2HSV);
  cv::inRange(
    ret, 
    cv::Scalar(range.MINH, range.MINS, range.MINV),
    cv::Scalar(range.MAXH, range.MAXS, range.MAXV),
    ret
  );
  
  if (bgr) {
    cv::cvtColor(ret, ret, cv::COLOR_GRAY2BGR);
  }
  return ret;
}