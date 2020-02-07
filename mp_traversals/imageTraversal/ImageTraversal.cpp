#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator():
startPoint(Point()), traversal(NULL)
{
  /** NOTHING */
}

ImageTraversal::Iterator::Iterator(ImageTraversal *traversal, const Point& x):
startPoint(x), traversal(traversal)
{
  current = traversal->peek();
}

/**
 * Iterator pre increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {

        // traversal is not empty (because we make sure it's not empty
        // by using != operator)
        // check if the top(front) has been traversed
        // normal case
        current = traversal->pop();
        traversal->mark(current);
        traversal->add(current);
        while(!traversal->empty() && traversal->if_traversed(traversal->peek()))
            current = traversal->pop();
        if (!traversal->empty())
            current = traversal->peek();
    return *this;

}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {

    // why are we only comparing traversal here? what about start and current?
    bool t_empty = false, o_empty = false;

    if (traversal == NULL)
        t_empty = true;
    if (other.traversal == NULL)
        o_empty = true;

    if (!t_empty)
        t_empty = traversal->empty();
    if (!o_empty)
        o_empty = other.traversal->empty();

    // both empty then the traversals are equal, return false
    if (t_empty && o_empty)
        return false;
    // both not empty then compare the traversals
    // how to compare traversals without overloaded !=? compare pointer
    else if ((!t_empty) && (!o_empty))
        return (traversal != other.traversal);
    else
        return true; // one is empty while the other is not, return true
}
