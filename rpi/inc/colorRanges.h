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

const struct colorRange BLACK = {
  0, 179,
  0, 255,
  0, 50
};



/*
Determine the number of pixels in a provided range.
Frame should be in HSV format
*/
int getPixelCount(cv::Mat frame, struct colorRange range);
cv::Mat filterColor(cv::Mat frame, struct colorRange range, bool bgr);

#endif /* COLORRANGES_H */