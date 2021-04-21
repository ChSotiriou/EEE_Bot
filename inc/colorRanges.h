#ifndef COLORRANGES_H
#define COLORRANGES_H

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

/*
Color Range Definitions
*/
struct colorRange {
  int MINH, MAXH;
  int MINS, MAXS;
  int MINV, MAXV;
};

const struct colorRange RED = {
  0, 14,
  180, 255,
  120, 255
};
const struct colorRange GREEN = {
  40, 70,
  180, 255,
  120, 255
};
const struct colorRange BLUE = {
  105, 135,
  180, 255,
  120, 255
};

/*
Determine the number of pixels in a provided range.
Frame should be in HSV format
*/
int getPixelCount(cv::Mat frame, struct colorRange range);


#endif /* COLORRANGES_H */