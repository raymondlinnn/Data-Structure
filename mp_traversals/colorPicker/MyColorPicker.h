#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include <cmath>
#include <algorithm>

using std::max;
using namespace cs225;
/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
    MyColorPicker(double saturation, double alpha, double min);
    HSLAPixel getColor(unsigned x, unsigned y);
private:
    double degree;
    double s;
    double a;
    double min; // the lowest luminance
};
