#include <wirish/wirish.h>
#include "screen.h"

screen gameScreen;

void setup() {
  gameScreen.init();
}

void loop() {
  for(int i = 0; i < 84 * 6; i++) {
    gameScreen.setBitmapByte(i, random(0xff));
  }

  gameScreen.redraw();
  delay(100);
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
