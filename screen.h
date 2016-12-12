#include "pcd8544.h"

class screen {
public:
  screen();
  void init();
  void redraw();
  void setBitmapByte(int index, uint8_t value);
private:
  uint8_t bitmap[504];
  pcd8544 lcd;
};
