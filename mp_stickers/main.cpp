#include "Image.h"
#include "StickerSheet.h"

using namespace cs225;

int main() {

    Image carl;
    Image rick;
    Image morty;
    Image output;

    carl.readFromFile("gcevans.png");
    rick.readFromFile("rick.png");
    rick.scale(300, 300);

    morty.readFromFile("Morty.png");
    morty.scale(360, 360);

    StickerSheet sheet(carl, 5);
    sheet.addSticker(rick, 700, 660);
    sheet.addSticker(morty, 1000, 560);

    output = sheet.render();
    output.writeToFile("myImage.png");

    return 0;
}
