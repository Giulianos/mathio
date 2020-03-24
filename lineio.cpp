#include "lineio.h"

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 9
#define CHAR_COMPACT_HEIGHT 5

LineIO::LineIO(const std::string text) : _text(text), _compact(false) {}

int LineIO::getWidth() {
    size_t len = _text.length();

    return !len ? 0 : _text.length() * (CHAR_WIDTH + 1)  - 1;
}

int LineIO::getHeight() {
    return _compact ? CHAR_COMPACT_HEIGHT : CHAR_HEIGHT;
}

void LineIO::renderRect(int x0, int y0, int width, int height) {
    int x1 = width + x0 - 1;
    int y1 = height + y0 - 1;
    int buffWidth = getWidth();
    for (int x = x0; x <= x1; x++) {
        for (int y = y0; y <= y1; y++) {
            if (x == x0 || x == x1 || y == y0 || y == y1) {
                _renderBuff[x + y*buffWidth] = true;
            }
        }
    }
}

std::vector<bool> LineIO::getRender() {
    // Resize renderBuffer to fit content
    _renderBuff.resize(getHeight() * getWidth(), false);

    // For now, just render squares
    for (int i = 0; i < _text.length(); i++) {
        int xPos = (CHAR_WIDTH + 1) * i;
        if (_compact) {
           renderRect(xPos, 0, CHAR_WIDTH, CHAR_COMPACT_HEIGHT);
        } else {
           renderRect(xPos, 0, CHAR_WIDTH, CHAR_HEIGHT);
        }
    } 

    return _renderBuff;
}

void LineIO::setCompactMode(bool compact) {
    _compact = compact;
}
