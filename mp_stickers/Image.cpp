#include "Image.h"
#include <string>

    void Image::lighten(){
        for (unsigned x = 0; x < this->width(); x++) {
              for (unsigned y = 0; y < this->height(); y++) {
                  HSLAPixel & pixel = this->getPixel(x, y);
                  double lm = pixel.l + 0.1;
                  if (lm >= 1){pixel.l = 1;}
                  else{pixel.l = lm;}
              }
          }
    }

    void Image::lighten(double amount){
        for (unsigned x = 0; x < this->width(); x++) {
              for (unsigned y = 0; y < this->height(); y++) {
                  HSLAPixel & pixel = this->getPixel(x, y);
                  double lm = pixel.l + amount;
                  if (lm >= 1){pixel.l = 1;}
                  else{pixel.l = lm;}
              }
          }
    }

    void Image::darken(){
        for (unsigned x = 0; x < this->width(); x++) {
              for (unsigned y = 0; y < this->height(); y++) {
                  HSLAPixel & pixel = this->getPixel(x, y);
                  double lm = pixel.l - 0.1;
                  if (lm <= 0){pixel.l = 0;}
                  else{pixel.l = lm;}
              }
          }
    }

    void Image::darken(double amount){
        for (unsigned x = 0; x < this->width(); x++) {
              for (unsigned y = 0; y < this->height(); y++) {
                  HSLAPixel & pixel = this->getPixel(x, y);
                  double lm = pixel.l - amount;
                  if (lm <= 0){pixel.l = 0;}
                  else{pixel.l = lm;}
              }
          }
    }

    void Image::saturate(){
        for (unsigned x = 0; x < this->width(); x++) {
                  for (unsigned y = 0; y < this->height(); y++) {
                      HSLAPixel & pixel = this->getPixel(x, y);
                      double sm = pixel.s + 0.1;
                      if (sm >= 1){pixel.s = 1;}
                      else{pixel.s = sm;}
                  }
              }
      }

    void Image::saturate(double amount){
        for (unsigned x = 0; x < this->width(); x++) {
                  for (unsigned y = 0; y < this->height(); y++) {
                      HSLAPixel & pixel = this->getPixel(x, y);
                      double sm = pixel.s + amount;
                      if (sm >= 1){pixel.s = 1;}
                      else{pixel.s = sm;}
                  }
              }
    }

    void Image::desaturate(){
        for (unsigned x = 0; x < this->width(); x++) {
                  for (unsigned y = 0; y < this->height(); y++) {
                      HSLAPixel & pixel = this->getPixel(x, y);
                      double sm = pixel.s - 0.1;
                      if (sm <= 1){pixel.s = 0;}
                      else{pixel.s = sm;}
                  }
              }
    }

    void Image::desaturate(double amount){
        for (unsigned x = 0; x < this->width(); x++) {
                    for (unsigned y = 0; y < this->height(); y++) {
                        HSLAPixel & pixel = this->getPixel(x, y);
                        double sm = pixel.s - amount;
                        if (sm <= 1){pixel.s = 0;}
                        else{pixel.s = sm;}
                    }
                }
    }

    void Image::grayscale(){
        for (unsigned x = 0; x < this->width(); x++) {
                    for (unsigned y = 0; y < this->height(); y++) {
                        HSLAPixel & pixel = this->getPixel(x, y);
                        pixel.s = 0;
                    }
                }
    }

    void Image::rotateColor(double degrees){
        for (unsigned x = 0; x < this->width(); x++) {
                  for (unsigned y = 0; y < this->height(); y++) {
                      HSLAPixel & pixel = this->getPixel(x, y);
                      double dg = pixel.h + degrees;
                      if (dg >= 360){pixel.h = dg - 360;}
                      else if(dg <= 0){pixel.h = dg + 360;}
                      else{pixel.h = dg;}
                  }
              }
    }

    void Image::illinify(){
        for (unsigned x = 0; x < this->width(); x++) {
                  for (unsigned y = 0; y < this->height(); y++) {
                      HSLAPixel & pixel = this->getPixel(x, y);
                      if (pixel.h > 113.5 && pixel.h < 293.5) {
                          pixel.h = 216;}
                      else {pixel.h = 11;}
                  }
              }
    }

    void Image::scale(double factor){
        Image *new1 = new Image(*this);
        this->resize(width() * factor, height() * factor);
        for (unsigned x = 0; x < width(); x++) {
                  for (unsigned y = 0; y < height(); y++) {
                      int x1 = x / factor;
                      int y1 = y / factor;
                      HSLAPixel & pixel1 = this->getPixel(x, y);
                      HSLAPixel & pixel2 = new1->getPixel(x1, y1);
                      pixel1 = pixel2;
                  }
              }
    delete new1;
    }

    void Image::scale(unsigned w, unsigned h){
        Image *new1 = new Image(*this);
        double coef1 = (double)w / width();
        double coef2 = (double)h / height();
        double coef = (coef1 < coef2) ? coef1 : coef2;
        this->resize(width() * coef, height() * coef);
        for (unsigned x = 0; x < width(); x++) {
                  for (unsigned y = 0; y < height(); y++) {
                      int x1 = x / coef;
                      int y1 = y / coef;
                      HSLAPixel & pixel1 = this->getPixel(x, y);
                      HSLAPixel & pixel2 = new1->getPixel(x1, y1);
                      pixel1 = pixel2;
                  }
              }
    delete new1;
    }
