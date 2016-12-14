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
  mapToBitmap();
  if (anyPixelDeleted())
    lcd.clear();

  for (uint8_t i = 0; i < 6; i++)
    for (uint8_t j = 0; j < 84; j++)
      buffBitmap[i][j] = bitmap[i][j];

  for (uint8_t i = 0; i < 6; i++) {
    lcd.gotoRc(i, 0);
    lcd.bitmap(buffBitmap[i], 1, 84);
  }
}

bool screen::anyPixelDeleted() {
  uint8_t changedMask;

  for (uint8_t i = 0; i < 6; i++) {
    for (uint8_t j = 0; j < 84; j++) {
      changedMask = bitmap[i][j] ^ buffBitmap[i][j];

      if (changedMask > 0 && (changedMask & bitmap[i][j]) == 0) {
        return true;
      }
    }
  }
  return false;
}

void screen::clear() {
  for (uint8_t i = 0; i < 84; i++)
    for (uint8_t j = 0; j < 48; j++)
      map[i][j] = false;

  lcd.clear();
  redraw();
}

void screen::setBitmapByte(uint8_t row, uint8_t col, uint8_t value) {
  bitmap[row][col] = value;
}

void screen::mapToBitmap() {
  uint8_t byte = 0;

  for (uint8_t row = 0; row < 6; row++) {
    for (uint8_t col = 0; col < 84; col++) {
      byte = 0;
      for (uint8_t bit = 0; bit < 8; bit++) {
        byte |= (uint8_t)map[col][row * 6 + bit] << bit;
      }
      bitmap[row][col] = byte;
    }
  }
}

void screen::clearPixel(uint8_t x, uint8_t y) {
  map[x][y] = false;
}

void screen::putPixel(uint8_t x, uint8_t y) {
  map[x][y] = true;
}

