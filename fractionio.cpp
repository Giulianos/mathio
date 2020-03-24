#include "fractionio.h"

FractionIO::FractionIO(MathIO* numerator, MathIO* denominator)
    : _num(numerator), _den(denominator), _compact(false) {}

int FractionIO::getWidth() {
    _den->setCompactMode(_compact);
    _num->setCompactMode(_compact);

    int denWidth = _den->getWidth();
    int numWidth = _num->getWidth();

    return denWidth > numWidth ? denWidth : numWidth;
}

void FractionIO::setCompactMode(bool compact) {
    _compact = compact;
}

int FractionIO::getHeight() {
    _den->setCompactMode(_compact);
    _num->setCompactMode(_compact);

    int denHeight = _den->getHeight();
    int numHeight = _num->getHeight();

    // numerator + denominator + 2 spaces + fraction line
    return denHeight + numHeight + 3;
}

std::vector<bool> FractionIO::getRender() {
    int width = getWidth();
    int height = getHeight();

    _renderBuff.resize(width*height, false);

    std::vector<bool> numBuff = _num->getRender();
    std::vector<bool> denBuff = _den->getRender();

    int numHeight = _num->getHeight();
    int numWidth = _num->getWidth();
    int denHeight = _den->getHeight();
    int denWidth = _den->getWidth();

    int numOffset = denWidth > numWidth ? (denWidth-numWidth)/2 : 0;
    int denOffset = denWidth < numWidth ? (numWidth-denWidth)/2 : 0;

    // Dump numBuffer in fraction buffer
    for (int x = 0; x < numWidth; x++) {
        for (int y = 0; y < numHeight; y++) {
            _renderBuff[x + numOffset + y*width] = numBuff[x + y*numWidth];
        }
    }

    // Draw fraction line
    for (int x = 0, y = numHeight + 1; x < width; x++) {
        _renderBuff[x + y*width] = true;
    }

    // Dump denBuffer in fraction buffer
    for (int x = 0; x < denWidth; x++) {
        for (int y = 0; y < denHeight; y++) {
            _renderBuff[x + denOffset + (y+numHeight+3)*width] = denBuff[x + y*denWidth];
        }
    }

    return _renderBuff;
}
