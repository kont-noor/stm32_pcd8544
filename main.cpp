#include <wirish/wirish.h>
#include "screen.h"

screen gameScreen;

void setup() {
  gameScreen.init();
}

void loop() {
  for (int x = 0; x < 84; x++) {
    for (int y = 0; y < 48; y++) {
      gameScreen.putPixel(x, y);
      gameScreen.redraw();
    }
  }
  for (int x = 0; x < 84; x++) {
    for (int y = 0; y < 48; y++) {
      gameScreen.clearPixel(x, y);
      gameScreen.redraw();
    }
  }
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
