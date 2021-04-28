#ifndef MAIN_HPP
#define MAIN_HPP

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <wiringPi.h>

#include "pi2c.h"

#include "robotControl.h"
#include "shapeDetector.h"
#include "colorRanges.h"
#include "opencv_aee.hpp"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#define DETECTION_DELAY 3000

const float IMAGE_RESIZE = 1;

#endif /* MAIN_HPP */
