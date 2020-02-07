#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(double saturation, double alpha, double min)
:degree(0), s(saturation), a(alpha), min(min)
{}


HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
    double l = max(fabs(cos(degree + 0.25 * M_PI)), min);
    double h = fabs(sin(degree)) * 360;
    HSLAPixel pixel(h, s, l, a);
    degree += 0.001 * M_PI;
    return pixel;
}
