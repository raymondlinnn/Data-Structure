/**
 * @file DFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <stack>
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
using std::stack;
/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG& png, const Point& start, double tolerance);
  ~DFS();
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & p);
  Point pop();
  Point peek() const;
  bool empty() const;

  bool if_traversed(Point p);
  void mark(const Point& p);

private:
    stack<Point> stack;
    Point startPoint;
    PNG copy;
    double tolerance;
    // 2D array to help track traversed point
    int **arr;
    // helper functions to add or minus 1 to x,y coordinate
    Point Next_x(const Point& curr);
    Point Next_y(const Point& curr);
    Point Prev_x(const Point& curr);
    Point Prev_y(const Point& curr);
    // helper to decide whether it has been traversed
};
