#include "maze.h"
#include <iterator>
#include <algorithm>
#include <queue>

using std::queue;

SquareMaze::SquareMaze() {
    // ?
}


void SquareMaze::makeMaze(int width, int height) {
    reset();

    w = width;
    h = height;

    int total = width * height;
    dset.addelements(total);

    // add sqaure
    Squares.resize(total);
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            square temp;
            int temp_coord = reduce(x, y);
            Squares[temp_coord] = temp;
        }
    }

    int next, curr;
    vector<int> walls, random;
    int total_walls = (height - 1) * (2 * width - 1) + (width - 1);
    for (int i = 0; i < total_walls; ++i) {
        walls.push_back(i);
        random.push_back(i);
    }
    std::random_shuffle(random.begin(), random.end());

    for (int i = 0; i < total_walls; ++i) {
        int idx = walls[random[i]];
        bool right = true;
        int x_cor = idx % (2 * width - 1);
        if (x_cor >= width - 1) {
            x_cor -= width - 1;
            right = false;
        }
        int y_cor = idx / (2 * width - 1);
        curr = reduce(x_cor, y_cor);
        if (right)
            next = curr + 1;
        else
            next = curr + width;
        // prevent cycle
        int p_curr = dset.find(curr);
        int p_next = dset.find(next);
        if (p_curr != p_next) {
            dset.setunion(p_curr, p_next);
            if (right)
                Squares[curr].right = false;
            else
                Squares[curr].down = false;
        }
    }
}


bool SquareMaze::canTravel(int x, int y, int dir) const{
    if (!valid(x, y))   return false;

    if (dir == 3 && valid(x, y - 1)) {
        int temp = reduce(x, y - 1);
        return !Squares[temp].down;
    }else if (dir == 2 && valid(x - 1, y)) {
        int temp = reduce(x - 1, y);
        return !Squares[temp].right;
    }else if (dir == 0 && valid(x + 1, y)){
        int temp = reduce(x, y);
        return !Squares[temp].right;
    }else if (dir == 1 && valid(x, y + 1)) {
        int temp = reduce(x, y);
        return !Squares[temp].down;
    }
    // invalid cases
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (valid(x, y)) {
        int cor = reduce(x, y);
        if (dir == 0) {
            Squares[cor].right = exists;
        }else{
            Squares[cor].down = exists;
        }
    }
}

vector<int> SquareMaze::solveMaze(){
    // path[i] = where it came from
    // this is the most important thing
    vector<int> path;
    // keep track of the distance
    vector<int> distance;
    distance.resize(w * h);
    path.push_back(-2);  // store something special in the origin
    for (int i = 1; i < w * h; ++i)
        path.push_back(-1);

    queue<int> bfs;
    int x, y, curr;
    bfs.push(0);
    while(!bfs.empty()) {
        curr = bfs.front();
        bfs.pop();
        x = curr % w;
        y = curr / h;
        // check if we have been to the next cell
        // calculate the next cell's index
        if (canTravel(x, y, 0) && path[curr + 1] == -1) {
            bfs.push(curr + 1);
            path[curr + 1] = curr;
            distance[curr + 1] = distance[curr] + 1;
        }
        if (canTravel(x, y, 1) && path[curr + w] == -1) {
            bfs.push(curr + w);
            path[curr + w] = curr;
            distance[curr + w] = distance[curr] + 1;
        }
        if (canTravel(x, y, 2) && path[curr - 1] == -1) {
            bfs.push(curr - 1);
            path[curr - 1] = curr;
            distance[curr - 1] = distance[curr] + 1;
        }
        if (canTravel(x, y, 3) && path[curr - w] == -1) {
            bfs.push(curr - w);
            path[curr - w] = curr;
            distance[curr - w] = distance[curr] + 1;
        }
    }

    // find the max distance from the bottom endpoints
    int max = 0;
    int idx;
    for (int i = 0; i < w; ++i) {
        // find the bottom cells
        curr = ((h-1) * w + i);
        if (distance[curr] > max) {
            max = distance[curr];
            idx = curr;
        }
    }
    // find the solution path
    vector<int> solution;

    while (idx != 0) {
        int step = idx - path[idx];
        if (step == 1) {
            solution.insert(solution.begin(), 0);
        }else if (step == w) {
            solution.insert(solution.begin(), 1);
        }else if (step == -1) {
            solution.insert(solution.begin(), 2);
        }else{
            solution.insert(solution.begin(), 3);
        }
        idx = path[idx];
    }

    return solution;
}

PNG* SquareMaze::drawMaze() const {
    int image_w = w * 10 + 1;
    int image_h = h * 10 + 1;

    PNG* out = new PNG(image_w, image_h);
    HSLAPixel black(0, 0, 0);
    // top side
    for (int i = 0; i < image_w; ++i) {
        if (i == 0 || i > 9) {
            HSLAPixel& p = out->getPixel(i, 0);
            p = black;
        }
    }
    // left side
    for (int i = 0; i < image_h; ++i) {
        HSLAPixel& p = out->getPixel(0, i);
        p = black;
    }
    // x, y is the coordinate of the square in maze
    for (int x = 0; x < w; ++x) {
        for (int y = 0; y < h; ++y) {
            // internal right-walls and right side
            if (!canTravel(x, y, 0)) {
                for (int i = 0; i <= 10; ++i) {
                    HSLAPixel& p = out->getPixel((x+1) * 10, y*10 + i);
                    p = black;
                }
            }
            // internal down-walls and bottom side
            if (!canTravel(x, y, 1)) {
                for (int i = 0; i <= 10; ++i) {
                    HSLAPixel& p = out->getPixel(x*10 + i, (y+1) * 10);
                    p = black;
                }
            }
        }
    }


    return out;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* out = drawMaze();
    vector<int> sol = solveMaze();
    HSLAPixel red(0, 1, 0.5, 1);
    int x = 0, y = 0;
    for (int& step : sol) {
        if (step == 0) {
            for (int i = 0; i <= 10; ++i) {
                HSLAPixel& pxl = out->getPixel(x * 10 + 5 + i, y * 10 + 5);
                pxl = red;
            }
            ++x;
        }else if (step == 1) {
            for (int i = 0; i <= 10; ++i) {
                HSLAPixel& pxl = out->getPixel(x * 10 + 5, y * 10 + 5 + i);
                pxl = red;
            }
            ++y;
        }else if (step == 2) {
            for (int i = 0; i <= 10; ++i) {
                HSLAPixel& pxl = out->getPixel(x * 10 + 5 - i, y * 10 + 5);
                pxl = red;
            }
            --x;
        }else{
            for (int i = 0; i <= 10; ++i) {
                HSLAPixel& pxl = out->getPixel(x * 10 + 5, y * 10 + 5 - i);
                pxl = red;
            }
            --y;
        }
    }
    HSLAPixel white(0, 0, 1);
    for (int i = 1; i <= 9; ++i) {
        HSLAPixel& pxl = out->getPixel(x * 10 + i, (y+1) * 10);
        pxl = white;
    }

    return out;
}

void SquareMaze::erase(PNG* out) {
    HSLAPixel white(0, 0, 1);
    HSLAPixel black(0, 0, 0);
    for (int i = 110; i <= 200; ++i) {
        for (int j = 0; j <= 80; ++j) {
            HSLAPixel& pxl = out->getPixel(i, j);
            pxl = white;
            if (i == 110) {
                HSLAPixel& pxl = out->getPixel(i, j);
                pxl = black;
            }
            if (j == 80) {
                HSLAPixel& pxl = out->getPixel(i, j);
                pxl = black;
            }
        }
    }

    for (int i = 0; i <= 70; ++i) {
        for (int j = 130; j <= 200; ++j) {
            HSLAPixel& pxl = out->getPixel(i, j);
            pxl = white;
            if (i == 70) {
                HSLAPixel& pxl = out->getPixel(i, j);
                pxl = black;
            }
            if (j == 130) {
                HSLAPixel& pxl = out->getPixel(i, j);
                pxl = black;
            }
        }
    }

    HSLAPixel blue(216, 0.8, 0.8);
    HSLAPixel orange(11, 0.8, 0.8);
    for (int i = 0; i <= 110; ++i) {
        for (int j = 0; j <= 130; ++j) {
            if (i <= -0.8 * j + 174) {
                HSLAPixel& pxl = out->getPixel(i, j);
                if (pxl.l == 1)
                    pxl = blue;
            }
        }
    }
    for (int i = 70; i <= 200; ++i) {
        for (int j = 80; j <= 200; ++j) {
            if (i >= -0.8 * j + 174) {
                HSLAPixel& pxl = out->getPixel(i, j);
                if (pxl.l == 1)
                    pxl = orange;
            }
        }
    }

}


void SquareMaze::reset() {
    Squares.erase(Squares.begin(), Squares.end());
    dset.data.erase(dset.data.begin(), dset.data.end());
}

int SquareMaze::reduce(int x, int y) const{
    return y * w + x;
}

bool SquareMaze::valid(int x, int y) const{
    return (x >= 0 && x < w && y >= 0 && y < h);
}
