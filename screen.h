#include "pcd8544.h"

class screen {
public:
  screen();
  void init();
  void redraw();
  void setBitmapByte(uint8_t, uint8_t, uint8_t);
  void putPixel(uint8_t, uint8_t);
  void clearPixel(uint8_t, uint8_t);
  void clear();
private:
  uint8_t bitmap[6][84];
  uint8_t buffBitmap[6][84];
  bool map[84][48];
  pcd8544 lcd;

  bool anyPixelDeleted();
  void mapToBitmap();
};
