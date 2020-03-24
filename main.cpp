#include <stdio.h>
#include "lineio.h"

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
    printFormula(&line1);
    LineIO line2("1234");
    line2.setCompactMode(true);
    printFormula(&line2);

    return 0;
}
