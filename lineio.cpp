#include "lineio.h"
#include <stdlib.h>
#include <string.h>

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 9
#define CHAR_COMPACT_HEIGHT 5

LineIO::LineIO(const char * text)
  : _compact(false)
{
	_text = (char *)calloc(strlen(text)+1, sizeof(*_text));
	strcpy(_text, text);
}

int
LineIO::getWidth()
{
  size_t len = strlen(_text);

  return !len ? 0 : len * (CHAR_WIDTH + 1) - 1;
}

int
LineIO::getHeight()
{
  return _compact ? CHAR_COMPACT_HEIGHT : CHAR_HEIGHT;
}

void
LineIO::renderRect(ScreenBuffer* buffer, int x0, int y0, int width, int height)
{
  int x1 = width + x0 - 1;
  int y1 = height + y0 - 1;

  for (int x = x0; x <= x1; x++) {
    for (int y = y0; y <= y1; y++) {
      if (x == x0 || x == x1 || y == y0 || y == y1) {
        buffer->setPixel(x, y, true);
      }
    }
  }
}

void
LineIO::render(ScreenBuffer* buffer)
{
  int textLen = strlen(_text);
  // For now, just render squares
  for (int i = 0; i < textLen; i++) {
    int xPos = (CHAR_WIDTH + 1) * i;
    if (_compact) {
      renderRect(buffer, xPos, 0, CHAR_WIDTH, CHAR_COMPACT_HEIGHT);
    } else {
      renderRect(buffer, xPos, 0, CHAR_WIDTH, CHAR_HEIGHT);
    }
  }
}

void
LineIO::setCompactMode(bool compact)
{
  _compact = compact;
}
