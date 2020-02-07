#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png):copy(png)
{
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  q_trav.push(&traversal);
  q_color.push(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color basecd on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) {
    Animation animation;
    PNG modified = copy;
    while(!q_trav.empty()){
        curr_trav = q_trav.front();
        curr_color = q_color.front();
        q_trav.pop();
        q_color.pop();
        animation.addFrame(modified);

        ImageTraversal::Iterator it = curr_trav->begin();
        for (unsigned i = 0; it != curr_trav->end(); ++it) {
            HSLAPixel& p = modified.getPixel((*it).x, (*it).y);
            p = curr_color->getColor((*it).x, (*it).y);
            ++i;
            // only add frame after "interval"-time operation
            if (i % frameInterval == 0)
                animation.addFrame(modified);
          }
    }
    animation.addFrame(modified);

    return animation;
}
