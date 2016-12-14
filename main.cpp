#include <wirish/wirish.h>
#include "screen.h"

screen gameScreen;

void fillScreen() {
  for (int x = 0; x < 84; x++) {
    for (int y = 0; y < 48; y++) {
      gameScreen.putPixel(x, y);
    }
  }

  gameScreen.redraw();
}

void setup() {
  gameScreen.init();
}

void loop() {
  for (int y = 0; y < 48; y++) {
    for (int x = 0; x < 84; x++) {
      gameScreen.putPixel(x, y);
      gameScreen.redraw();
    }
  }

  delay(1000);

  gameScreen.clear();
  delay(1000);
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
