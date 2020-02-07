
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

    PNG blank(300, 300);
    MyColorPicker mycolor1(0.888, 0.666, 0.222);
    BFS bfs(blank, Point(150, 150), 0.05);

    MyColorPicker mycolor2(0.666, 0.666, 0.666);
    DFS dfs(blank, Point(0, 0), 0.05);

    FloodFilledImage image(blank);
    image.addFloodFill(bfs, mycolor1);
    image.addFloodFill(dfs, mycolor2);
    Animation animation = image.animate(1500);

    PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
    lastFrame.writeToFile("myFloodFill.png");
    animation.write("myFloodFill.gif");



  return 0;
}
