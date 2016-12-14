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

  float result;

  for (int x = 0; x < 84; x++) {
    result = 24 + 20 * sin((float)x/12);
    if (result < 48)
      gameScreen.putPixel(x, int(result));
  }
  gameScreen.redraw();

  delay(1000);
}

void loop() {
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
