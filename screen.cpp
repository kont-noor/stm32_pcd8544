#include "screen.h"

/*
  Display, top row left to right - Maple/Arduino  Mega

  Vcc                            - 3.3V
  GND                            - GND
  SCE - chip enable/select       - 7
  RST                            - 6
  D/C                            - 5
  DN - MOSI                      - 11             51
  SCLK                           - 13             52
  LED                            - GND
 */
#define DC_PIN 5
#define RST_PIN 6
#define CS_PIN 7

screen::screen(): lcd(pcd8544(DC_PIN, RST_PIN, CS_PIN)) {
}

void screen::init() {
  lcd.begin();
  lcd.clear();
}

void screen::redraw() {
  lcd.clear();
  mapToBitmap();
  lcd.gotoRc(0, 0);
  lcd.bitmap(bitmap, 6, 84);
}

void screen::clear() {
  for (int i = 0; i < 504; i++)
    bitmap[i] = 0;
  redraw();
}

void screen::setBitmapByte(int index, uint8_t value) {
  bitmap[index] = value;
}

void screen::mapToBitmap() {
  uint8_t byte = 0;

  for (uint8_t col = 0; col < 84; col++) {
    for (uint8_t row = 0; row < 6; row++) {
      byte = 0;
      for (uint8_t bit = 0; bit < 8; bit++) {
        byte |= (uint8_t)map[col][row * 6 + bit] << bit;
        bitmap[row * 84 + col] = byte;
      }
    }
  }
}

void screen::putPixel(int x, int y) {
  ////bytes row starting from 0
  //int row = y / 8;
  //int bit = y % 8;
  //if (bit == 0)
  //  row--;

  //int byte_position = 84 * row + x;

  //uint8_t byte = bitmap[byte_position] | 1 << bit;
  ////uint8_t byte = 1 << bit;
  ////clear();

  //setBitmapByte(byte_position, byte);
  map[x][y] = true;
}

