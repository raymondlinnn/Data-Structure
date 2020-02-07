#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 *
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance):
tolerance(tolerance)
{
    startPoint = Point(start.x, start.y);
    copy = png;
    stack.push(start);

    // set up the 2D array
    int h = png.height(), w = png.width();
    arr = new int* [w];
    for (int x = 0; x < w; ++x)
        arr[x] = new int [h];

    for (int x = 0; x < w; ++x)
        for (int y = 0; y < h; ++y)
            arr[x][y] = 0;

}

DFS::~DFS(){
    for (int x = 0; x < (int)copy.width(); ++x)
        delete[] arr[x];
    delete[] arr;
}

Point DFS::Next_x(const Point& curr) {
    return Point(curr.x + 1, curr.y);
}

Point DFS::Next_y(const Point& curr) {
    return Point(curr.x, curr.y + 1);
}

Point DFS::Prev_x(const Point& curr) {
    return Point(curr.x - 1, curr.y);
}

Point DFS::Prev_y(const Point& curr) {
    return Point(curr.x, curr.y - 1);
}

bool DFS::if_traversed(Point p) {
    return arr[p.x][p.y] == 1;
}

void DFS::mark(const Point& p) {
    arr[p.x][p.y] = 1;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  return ImageTraversal::Iterator(this, startPoint);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & p) {
    HSLAPixel& origin = copy.getPixel(startPoint.x, startPoint.y);

    if (p.x + 1 < copy.width() && !if_traversed(Next_x(p))
    && calculateDelta(origin, copy.getPixel(Next_x(p).x, Next_x(p).y)) < tolerance)
        stack.push(Next_x(p));

    if (p.y + 1 < copy.height() && !if_traversed(Next_y(p))
    && calculateDelta(origin, copy.getPixel(Next_y(p).x, Next_y(p).y)) < tolerance)
        stack.push(Next_y(p));

    if (p.x >= 1 && !if_traversed(Prev_x(p))
    && calculateDelta(origin, copy.getPixel(Prev_x(p).x, Prev_x(p).y)) < tolerance)
        stack.push(Prev_x(p));

    if (p.y >= 1 && !if_traversed(Prev_y(p))
    && calculateDelta(origin, copy.getPixel(Prev_y(p).x, Prev_y(p).y)) < tolerance)
        stack.push(Prev_y(p));

}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
    Point temp = stack.top();
    stack.pop();
    return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
    return stack.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  return stack.empty();
}
