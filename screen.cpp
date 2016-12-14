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
  for (uint8_t row = 0; row < 6; row++) {
    for (uint8_t col = 0; col < 84; col++) {
      redrawByte(col, row);
    }
  }
}

void screen::redrawByte(uint8_t col, uint8_t row) {
  uint8_t byte = 0;
  //TODO: probably add flag array and set it on change pixel
  bool needRedraw = false;

  for (uint8_t bit = 0; bit < 8; bit++) {
    uint8_t index = row * 8 + bit;
    if (buffMap[col][index] != map[col][index]) {
      buffMap[col][index] = map[col][index];
      needRedraw = true;
    }
    byte |= buffMap[col][index] << bit;
  }

  if (needRedraw) {
    lcd.gotoRc(row, col);
    lcd.data(byte);
  }
}

void screen::clear() {
  for (uint8_t i = 0; i < 84; i++)
    for (uint8_t j = 0; j < 48; j++)
      map[i][j] = false;

  redraw();
}

void screen::clearPixel(uint8_t x, uint8_t y) {
  if (x < 84 &&  x >= 0 && y < 48 && y >= 0)
    map[x][y] = false;
}

void screen::putPixel(uint8_t x, uint8_t y) {
  if (x < 84 && x >= 0 && y < 48 && y >= 0)
    map[x][y] = true;
}

