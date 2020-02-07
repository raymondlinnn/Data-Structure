#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
    PNG pic, pic2;
    pic.readFromFile(inputFile);
    pic2.readFromFile(inputFile);
    for (unsigned x = 0; x < pic.width(); x++) {
        for (unsigned y = 0; y < pic.height(); y++) {

            HSLAPixel & pixel = pic.getPixel(x, y);
            HSLAPixel & pixel2 = pic2.getPixel(pic2.width() -1 - x,
             pic2.height() -1 - y);

            pixel2.h = pixel.h;
            pixel2.s = pixel.s;
            pixel2.a = pixel.a;
            pixel2.l = pixel.l;
        }
    }
    pic2.writeToFile(outputFile);
}


PNG myArt(unsigned int width, unsigned int height) {
    PNG png(width, height);
    for (unsigned x = 0; x < png.width(); x++) {
            for (unsigned y = 0; y < png.height(); y++) {
                HSLAPixel & pixel = png.getPixel(x, y);

                pixel.h = 333;
                pixel.s = 0.33;
                pixel.l = 0.66;
                pixel.a = 0.3;
            }
        }

    for (unsigned x = 0; x < png.width() / 3; x++) {
        for (unsigned y = 0; y <png.height() / 3; y++) {
            HSLAPixel & pixel = png.getPixel(x, y);

            pixel.h = 250;
            pixel.s = 0.7;
            pixel.l = 0.6;
            pixel.a = 0.4;
            }
        }
    for (unsigned x = png.width() / 3; x < png.width() * 2 / 3; x++) {
        for (unsigned y = png.height() /3; y <png.height() * 2 / 3; y++) {
            HSLAPixel & pixel = png.getPixel(x, y);

            pixel.h = 120;
            pixel.s = 0.7;
            pixel.l = 0.6;
            pixel.a = 0.4;
        }
    }

    for (unsigned x = png.width() * 2 / 3; x < png.width(); x++) {
        for (unsigned y = png.width() * 2 / 3; y < png.width(); y++) {
            HSLAPixel & pixel = png.getPixel(x, y);

            pixel.h = 22;
            pixel.s = 0.7;
            pixel.l = 0.6;
            pixel.a = 0.4;
        }
    }
    for (unsigned x = png.width() * 1 / 3; x < png.width() * 5 / 6; x++) {
        for (unsigned y = png.width() * 1 / 6; y < png.width() * 1 / 6 + 12; y++) {
            HSLAPixel & pixel = png.getPixel(x, y);

            pixel.h = 240;
            pixel.s = 0.9;
            pixel.l = 0.5;
            pixel.a = 0.6;
        }
    }
    for (unsigned x = png.width() * 5 / 6; x < png.width() * 5 / 6 + 12; x++) {
        for (unsigned y = png.width() * 1 / 6; y < png.width() * 2 / 3; y++) {
            HSLAPixel & pixel = png.getPixel(x, y);

            pixel.h = 240;
            pixel.s = 0.9;
            pixel.l = 0.5;
            pixel.a = 0.6;
        }
    }


  return png;
}
