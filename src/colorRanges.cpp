#include "colorRanges.h"

int getPixelCount(cv::Mat frame, struct colorRange range) {
  cv::Mat output;
  cv::inRange(
    frame, 
    cv::Scalar(range.MINH, range.MINS, range.MINV),
    cv::Scalar(range.MAXH, range.MAXS, range.MAXV),
    output
  );

  return cv::countNonZero(output);
}