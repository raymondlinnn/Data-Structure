#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    SquareMaze mz;
    mz.makeMaze(20, 20);
    PNG out = *mz.drawMaze();
    mz.erase(&out);
    out.writeToFile("creative.png");
    return 0;
}
