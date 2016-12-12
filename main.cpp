#include <wirish/wirish.h>
#include "screen.h"

screen gameScreen;

void setup() {
  gameScreen.init();
}

void loop() {
  //for(int i = 0; i < 84 * 6; i++) {
  //  gameScreen.setBitmapByte(i, random(0xff));
  //}
  for (int x = 0; x < 84; x++) {
    for (int y = 0; y < 48; y++) {
      gameScreen.putPixel(x, y);
      gameScreen.redraw();
      delay(100);
    }
  }
  gameScreen.clear();
}

__attribute__((constructor)) void premain() {
    init();
}

int main() {
  setup();
  while (true) {
    loop();
  }

  return 0;
}
