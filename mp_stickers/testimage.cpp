#include "Image.h"

#include <iostream>

int main() {
  Image alma;

  std::cout << "Using Image::lighten to create `lighten.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");

  std::cout << "Using Image::saturate to create `saturate.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  std::cout << "Using Image::scale to create `scale.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(2);
  alma.writeToFile("scale2x.png");

  std::cout << "Using Image::scale2 to create `scale_w_h.png`..." << std::endl;
  alma.readFromFile("alma.png");
  alma.scale(1200, 1200);
  alma.writeToFile("scale_w_h.png");

  return 0;
}
