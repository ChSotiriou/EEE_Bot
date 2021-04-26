#include "colorRanges.h"

int getPixelCount(cv::Mat frame, struct colorRange range) {
  cv::Mat output = filterColor(frame, range);
  return cv::countNonZero(output);
}

cv::Mat filterColor(cv::Mat frame, struct colorRange range) {
  cv::Mat ret;
  cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV);
  cv::inRange(
    frame, 
    cv::Scalar(range.MINH, range.MINS, range.MINV),
    cv::Scalar(range.MAXH, range.MAXS, range.MAXV),
    ret
  );
  return ret;
}