#include "pcd8544.h"

class screen {
public:
  screen();
  void init();
  void redraw();
  void putPixel(uint8_t, uint8_t);
  void clearPixel(uint8_t, uint8_t);
  void clear();
private:
  bool buffMap[84][48];
  bool map[84][48];
  pcd8544 lcd;

  bool anyPixelDeleted();
  void mapToBitmap();
};
