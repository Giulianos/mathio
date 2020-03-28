#include "screenbuffer.h"

#include <stdlib.h>
#include <string.h>

// TODO: refactor pixel indexing to
// make interfacing with SSD1306 easier
#define PIXEL_BYTE(x, y, w) (((x) + (y) * (w)) / 8)
#define PIXEL_BIT(x, y, w) (((x) + (y) * (w)) % 8)

ScreenBuffer::ScreenBuffer()
  : _b(NULL)
{}

ScreenBuffer::ScreenBuffer(size_t width, size_t height)
  : _w(width)
  , _h(height)
{
  _bSize = width * height / 8;
  _bSize += width * height % 8 ? 1 : 0;

  _b = (uint8_t*)calloc(_bSize, sizeof(*_b));
}

ScreenBuffer::~ScreenBuffer()
{
  if (_b != NULL) {
    free(_b);
  }
}

void
ScreenBuffer::setPixel(int x, int y, bool value)
{
  if (value) {
    _b[PIXEL_BYTE(x, y, _w)] |= 1 << (PIXEL_BIT(x, y, _w));
  } else {
    _b[PIXEL_BYTE(x, y, _w)] &= ~(1 << (PIXEL_BIT(x, y, _w)));
  }
}

bool
ScreenBuffer::getPixel(int x, int y)
{
  return _b[PIXEL_BYTE(x, y, _w)] & 1 << (PIXEL_BIT(x, y, _w));
}

void
ScreenBuffer::setAll(bool value)
{
  memset(_b, value ? 0xFF : 0x00, _bSize);
}
