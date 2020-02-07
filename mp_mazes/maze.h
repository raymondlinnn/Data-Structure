#pragma once

#include <utility>
#include "dsets.h"
#include <vector>
#include "cs225/PNG.h"

using std::vector;
using std::make_pair;
using std::pair;
using namespace cs225;

class SquareMaze {
public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
    void erase(PNG* out);
private:
    int w;
    int h;
    DisjointSets dset;
    struct square{
        square() {
            right = true;
            down = true;
        }
        bool right;
        bool down;
    };

    // a compressed 1D vector contains square and coordinate to
    // represent the whole maze
    vector<square> Squares;
    void reset();
    int reduce(int x, int y) const;
    bool valid(int x, int y) const;

    // a structure to store wall

};
