#pragma once
#include "Image.h"

class StickerSheet{
public:
    Image *base;
    Image *stickersheet;
    unsigned max_count;
    unsigned cur_count;
    unsigned *xl;
    unsigned *yl;

    StickerSheet(const Image &picture, unsigned max);

    StickerSheet(const StickerSheet&other);

    ~StickerSheet();

    const StickerSheet& operator=(const StickerSheet &other);

    void changeMaxStickers(unsigned max);

    int addSticker(Image &sticker, unsigned x, unsigned y);

    bool translate(unsigned index, unsigned x, unsigned y);

    void removeSticker(unsigned index);

    Image *getSticker(unsigned index);

    Image render() const;

    void clear();

    void copy(StickerSheet const &that);
};
