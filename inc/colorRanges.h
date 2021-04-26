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
  0, 10,
  180, 255,
  120, 255
};
const struct colorRange ORANGE = {
  10, 20,
  180, 255,
  120, 255
};
const struct colorRange YELLOW = {
  20, 45,
  180, 255,
  120, 255
};
const struct colorRange GREEN = {
  45, 70,
  180, 255,
  120, 255
};
const struct colorRange BLUE = {
  71, 130,
  180, 255,
  120, 255
};
const struct colorRange PURPLE = {
  140, 170,
  130, 200,
  70, 100
};

const struct colorRange MAGIC_CARD = {
    140, 168,
    68, 255,
    0, 173
};
const struct colorRange MAGIC_IMG = {
    145, 155,
    250, 255,
    250, 255
};


/*
Determine the number of pixels in a provided range.
Frame should be in HSV format
*/
int getPixelCount(cv::Mat frame, struct colorRange range);
cv::Mat filterColor(cv::Mat frame, struct colorRange range);

#endif /* COLORRANGES_H */