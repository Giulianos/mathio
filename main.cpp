#include "fractionio.h"
#include "lineio.h"
#include "powerio.h"
#include "screenbuffer.h"
#include "screenbufferwindow.h"
#include <stdio.h>

void
printFormula(MathIO* m)
{
  int width  = m->getWidth();
  int height = m->getHeight();
  ScreenBuffer buffer(width, height);
  m->render(&buffer);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (buffer.getPixel(x, y)) {
        printf("██");
      } else {
        printf("  ");
      }
    }
    putchar('\n');
  }
}

int
main()
{
  LineIO den("12");
  LineIO num("1");
  LineIO exp("23");

  FractionIO base(&den, &num);
  PowerIO pow(&base, &exp);
  printFormula(&pow);

  return 0;
}
