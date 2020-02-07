/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
using std::queue;
/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);
  ~BFS();
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & p);
  Point pop();
  Point peek() const;
  bool empty() const;

  bool if_traversed(Point p);
  void mark(const Point& p);
private:
    queue<Point> queue;
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
