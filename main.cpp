#include "fractionio.h"
#include "lineio.h"
#include "powerio.h"
#include <stdio.h>

void
printFormula(MathIO* m)
{
  std::vector<bool> renderBuff = m->getRender();
  for (int y = 0; y < m->getHeight(); y++) {
    for (int x = 0; x < m->getWidth(); x++) {
      if (renderBuff[x + y * m->getWidth()]) {
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
