#include "pcd8544.h"

class screen {
public:
  screen();
  void init();
  void redraw();
  void setBitmapByte(int, uint8_t);
  void putPixel(int, int);
  void clear();
  void mapToBitmap();
private:
  uint8_t bitmap[504];
  bool map[84][48];
  pcd8544 lcd;
};
