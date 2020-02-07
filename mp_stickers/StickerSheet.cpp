#include "StickerSheet.h"

void StickerSheet::copy(StickerSheet const &that){
        max_count = that.max_count;
        cur_count = that.cur_count;
        base = new Image(*(that.base));
        xl = new unsigned[max_count];
        yl = new unsigned[max_count];
        stickersheet = new Image[max_count];
        for(unsigned i = 0; i < cur_count; i++){
            this->stickersheet[i] = that.stickersheet[i];
            this->xl[i] = that.xl[i];
            this->yl[i] = that.yl[i];
        }
    }

void StickerSheet::clear(){
        delete[] stickersheet;
        delete base;
        delete[] xl;
        delete[] yl;
}

StickerSheet::StickerSheet(const Image &picture, unsigned max){
    max_count = max;
    cur_count = 0;
    xl = new unsigned[max];
    yl = new unsigned[max];
    stickersheet = new Image[max];
    base = new Image(picture);
}

StickerSheet::StickerSheet(const StickerSheet&other){
    copy(other);
}

StickerSheet::~StickerSheet(){
    clear();
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
    if(this != &other){
        clear();
        copy(other);
    }
    return *this;
}


void StickerSheet::changeMaxStickers(unsigned max){
    Image *tempsheet = new Image[max];
    unsigned *temp_x = new unsigned[max];
    unsigned *temp_y = new unsigned[max];
    if(cur_count <= max){
        max_count = max;
        for(unsigned i = 0; i < cur_count; i++){
            tempsheet[i] = stickersheet[i];
            temp_x[i] = this->xl[i];
            temp_y[i] = this->yl[i];
        }
    }else{
        cur_count = max;
        max_count = max;
        for(unsigned i = 0; i < cur_count; i++){
            tempsheet[i] = stickersheet[i];
            temp_x[i] = this->xl[i];
            temp_y[i] = this->yl[i];
        }
}
    delete[] stickersheet;
    delete[] xl;
    delete[] yl;
    stickersheet = new Image[max_count];
    xl = new unsigned[max_count];
    yl = new unsigned[max_count];

    for(unsigned i = 0; i < max_count; i++){
        stickersheet[i] = tempsheet[i];
        xl[i] = temp_x[i];
        yl[i] = temp_y[i];
    }
    delete[] tempsheet;
    delete[] temp_x;
    delete[] temp_y;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    if(cur_count < max_count){
        stickersheet[cur_count] = sticker;
        xl[cur_count] = x;
        yl[cur_count] = y;
        cur_count++;
        return cur_count - 1;
    }else{
        return -1;
    }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if(index < cur_count){
        xl[index] = x;
        yl[index] = y;
        return true;
    }else{
        return false;
    }
}

void StickerSheet::removeSticker(unsigned index){
    if(index < cur_count - 1){
        for(unsigned i = index; i < cur_count - 1; i++){
            stickersheet[i] = stickersheet[i + 1];
            xl[i] = xl[i + 1];
            yl[i] = yl[i + 1];
        }
    }
        cur_count--;
}

Image* StickerSheet::getSticker(unsigned index){
    if(index < cur_count){
        return &stickersheet[index];
    }else{
        return nullptr;
    }
}

Image StickerSheet::render() const{
    Image after_render(*base);
    unsigned bw = after_render.width();
    unsigned bh = after_render.height();
    unsigned maxw = bw;
    unsigned maxh = bh;
    for(int i = 0; i < (int)cur_count; i++){
        if(xl[i] + stickersheet[i].width() >= maxw){
            maxw = xl[i] + stickersheet[i].width();
        }
        if(yl[i] + stickersheet[i].height() >= maxh){
            maxh = yl[i] + stickersheet[i].height();
        }
    }
    after_render.resize(maxw, maxh);


    for(int i = 0; i < (int)cur_count; i++){
        for (unsigned x = xl[i]; x < xl[i] + stickersheet[i].width(); x++) {
              for (unsigned y = yl[i]; y < yl[i] + stickersheet[i].height(); y++) {
                  HSLAPixel & pixel1 = after_render.getPixel(x, y);
                  HSLAPixel & pixel2 = stickersheet[i].getPixel(x - xl[i], y - yl[i]);
                  if(pixel2.a != 0){
                     pixel1 = pixel2;
                  }
              }
          }
    }
    return after_render;
}

/*            after_render.scale(xl[i] + stickersheet[i]->width(), yl[i] + stickersheet[i]->height());
            for (unsigned x = xl[i]; x < xl[i] + stickersheet[i]->width(); x++) {
                  for (unsigned y = yl[i]; y < yl[i] + stickersheet[i]->height(); y++) {
                      HSLAPixel & pixel1 = after_render.getPixel(x, y);
                      HSLAPixel & pixel2 = stickersheet[i]->getPixel(x, y);
                      pixel1 = pixel2;
                  }
              }



              for(unsigned i = 0; i < cur_count; i++){
                  if(xl[i] + stickersheet[i]->width() < after_render.width()){
                      if(yl[i] + stickersheet[i]->height() < after_render.height()){
                          for (unsigned x = xl[i]; x < xl[i] + stickersheet[i]->width(); x++) {
                                for (unsigned y = yl[i]; y < yl[i] + stickersheet[i]->height(); y++) {
                                    HSLAPixel & pixel1 = after_render.getPixel(x, y);
                                    HSLAPixel & pixel2 = stickersheet[i]->getPixel(x - xl[i], y - xl[i]);
                                    pixel1 = pixel2;
                                }
                            }
                      }
                  }else{
                      unsigned newWidth = 0;
                      unsigned newHeight = 0;
                      if(xl[i] + stickersheet[i]->width() >= after_render.width()){
                          newWidth = xl[i] + stickersheet[i]->width();
                      }else{
                          newWidth = after_render.width();
                      }
                      if(yl[i] + stickersheet[i]->height() >= after_render.height()){
                          newHeight = xl[i] + stickersheet[i]->height();
                      }else{
                          newHeight = after_render.height();
                      }
                      after_render.resize(newWidth, newHeight);
                      for (unsigned x = xl[i]; x < xl[i] + stickersheet[i]->width(); x++) {
                            for (unsigned y = yl[i]; y < yl[i] + stickersheet[i]->height(); y++) {
                                HSLAPixel & pixel1 = after_render.getPixel(x, y);
                                HSLAPixel & pixel2 = stickersheet[i]->getPixel(x - xl[i], y - xl[i]);
                                pixel1 = pixel2;
                            }
                        }
                    }
                }
*/
