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
  lcd.bitmap(bitmap, 6, 84);
}

void screen::setBitmapByte(int index, uint8_t value) {
  bitmap[index] = value;
}
