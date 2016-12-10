#include <wirish/wirish.h>
#include "pcd8544.h"

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

uint8_t dc_pin = 5;    // Data/Command
uint8_t reset_pin = 6;
uint8_t cs_pin = 7;    // Chip select (SCE)
//byte sdin_pin = 4;
//byte sclk_pin = 3;

// Create a pcd8544 object.
// Hardware SPI will be used.
// (SPI1 on the Maple, add 2 as last argument for SPI2 (untested)).
// sdin (MOSI) is on pin 11 and sclk on pin 13.
pcd8544 lcd(dc_pin, reset_pin, cs_pin);

// Use 5 arguments for soft SPI. Any pins can be choosen.
// byte sdin_pin = 11, sclk_pin = 13;
// pcd8544 lcd(dc_pin, reset_pin, cs_pin, sdin_pin, sclk_pin);


// 2 rows by 16 cols smiley. First 16 bytes is first row,
// next 16 is second.
byte smile[] = {
	0xE0,0x18,0x04,0x04,0x02,0x32,0x32,0x02,0x02,0x22,0x22,
	0x02,0x04,0x04,0x18,0xE0,0x07,0x18,0x20,0x22,0x44,0x48,
	0x48,0x48,0x48,0x48,0x48,0x44,0x22,0x20,0x18,0x07};

byte hedgehog[] = {
  0x00,0x00,0x00,0x80,0xE0,0xF0,0xBE,0xF8,0xF0,0xF8,0xE4,0x60,0x30,0x10,0x00,0x00,
  //0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
  0x00,0x00,0x3C,0x7E,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x5B,0x49,0x00,0x00
};

byte accum[84 * 6];

__attribute__((constructor)) void premain() {
    init();
}

int main() {

  lcd.begin();  // Always call lcd.begin() first.
  lcd.clear();
  // Set cursor to (character) column zero and row 0
  lcd.setCursor(0,0);

  lcd.gotoRc(0, 0);

  //lcd.bitmap(hedgehog, 2, 16);
  for(int i = 0; i < 84 * 6; i++) {
    accum[i] = 0xff;
  }

  lcd.bitmap(hedgehog, 2, 16);
  delay(2000);

  while (true) {
    lcd.clear();

    for(int i = 0; i < 84 * 6; i++) {
      accum[i] = random(0xff);
    }

    lcd.bitmap(accum, 6, 84);
    delay(100);
  }

  return 0;
}
