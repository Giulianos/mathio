#include "powerio.h"

#define EXP_BASE_OVERLAP 2

PowerIO::PowerIO(MathIO* base, MathIO* exp) : _base(base), _exp(exp), _compact(true) {}

int PowerIO::getWidth() {
    return _base->getWidth() + _exp->getWidth() + 1;
}

int PowerIO::getHeight() {
    return _base->getHeight() + _expHeigh() - EXP_BASE_OVERLAP;
}

std::vector<bool> PowerIO::getRender() {
    int width = getWidth();
    int height = getHeight();

    // Resize buffer to fit power
    _renderBuff.resize(width * height, false);

    int bWidth = _base->getWidth();
    int bHeight = _base->getHeight();

    int eWidth = _exp->getWidth();
    int eHeight = _exp->getHeight();

    int bOffsetY = height - bHeight;
    int eOffsetX = bWidth + 1;

    std::vector<bool> bBuffer = _base->getRender();
    std::vector<bool> eBuffer = _exp->getRender();

    // Dump k
    for (int x = 0; x < bWidth; x++) {
        for (int y = 0; y < bHeight; y++) {

        }
    }


    
}
