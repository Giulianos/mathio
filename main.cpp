#include <stdio.h>
#include "lineio.h"
#include "fractionio.h"

void printFormula(MathIO* m) {
    std::vector<bool> renderBuff = m->getRender();
    for (int y = 0; y < m->getHeight(); y++) {
        for (int x = 0; x < m->getWidth(); x++) {
            if (renderBuff[x + y*m->getWidth()]) {
                printf("██");
            } else {
                printf("  ");
            }
        }
        putchar('\n');
    }
}


int main() {
    LineIO line1("123");
    LineIO line2("12");
    FractionIO frac(&line1, &line2);
    frac.setCompactMode(true);
    printFormula(&frac);

    return 0;
}
