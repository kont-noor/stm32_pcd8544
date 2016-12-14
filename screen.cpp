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
  for (uint8_t i = 0; i < 84; i++)
    for (uint8_t j = 0; j < 48; j++)
      buffMap[i][j] = map[i][j];

  uint8_t digit;
  uint8_t byte;

  for (uint8_t row = 0; row < 6; row++) {
    for (uint8_t col = 0; col < 84; col++) {
      byte = 0;
      for (uint8_t bit = 0; bit < 8; bit++) {
        digit = buffMap[col][row * 8 + bit] ? 1 : 0;
        byte |= digit << bit;
      }
      lcd.gotoRc(row, col);
      lcd.data(byte);
    }
  }
}

bool screen::anyPixelDeleted() {
  for (uint8_t i = 0; i < 84; i++) {
    for (uint8_t j = 0; j < 48; j++) {
      if (map[i][j] == false && buffMap[i][j] == true)
        return true;
    }
  }
  return false;
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

