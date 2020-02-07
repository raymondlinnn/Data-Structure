#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <queue>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance):
tolerance(tolerance)
{
    startPoint = Point(start.x, start.y);
    copy = png;
    queue.push(start);

    // set up the 2D array
    int h = png.height(), w = png.width();
    arr = new int* [w];
    for (int x = 0; x < w; ++x)
        arr[x] = new int [h];

    for (int x = 0; x < w; ++x)
        for (int y = 0; y < h; ++y)
            arr[x][y] = 0;

}

BFS::~BFS(){
    for (int x = 0; x < (int)copy.width(); ++x)
        delete[] arr[x];
    delete[] arr;
}

Point BFS::Next_x(const Point& curr) {
    return Point(curr.x + 1, curr.y);
}

Point BFS::Next_y(const Point& curr) {
    return Point(curr.x, curr.y + 1);
}

Point BFS::Prev_x(const Point& curr) {
    return Point(curr.x - 1, curr.y);
}

Point BFS::Prev_y(const Point& curr) {
    return Point(curr.x, curr.y - 1);
}

bool BFS::if_traversed(Point p) {
    if (arr[p.x][p.y] == 1)
        return true;
    else
        return false;
}

void BFS::mark(const Point& p) {
    arr[p.x][p.y] = 1;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  return ImageTraversal::Iterator(this, startPoint);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
 void BFS::add(const Point & p) {
     HSLAPixel& origin = copy.getPixel(startPoint.x, startPoint.y);
     if (p.x + 1 < copy.width() && !if_traversed(Next_x(p))
     && calculateDelta(origin, copy.getPixel(Next_x(p).x, Next_x(p).y)) < tolerance)
         queue.push(Next_x(p));


     if (p.y + 1 < copy.height() && !if_traversed(Next_y(p))
     && calculateDelta(origin, copy.getPixel(Next_y(p).x, Next_y(p).y)) < tolerance)
         queue.push(Next_y(p));


     if (p.x >= 1 && !if_traversed(Prev_x(p))
     && calculateDelta(origin, copy.getPixel(Prev_x(p).x, Prev_x(p).y)) < tolerance)
         queue.push(Prev_x(p));


     if (p.y >= 1 && !if_traversed(Prev_y(p))
     && calculateDelta(origin, copy.getPixel(Prev_y(p).x, Prev_y(p).y)) < tolerance)
         queue.push(Prev_y(p));

 }

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
    Point temp = queue.front();
    queue.pop();
    return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
    return queue.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  return queue.empty();
}
