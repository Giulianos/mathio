#include "screenbuffer.h"

#include <cstdlib>
#include <cstring>

// TODO: refactor pixel indexing to
// make interfacing with SSD1306 easier
#define PIXEL_BYTE(x, y, w) (((x) + (y) * (w)) / 8)
#define PIXEL_BIT(x, y, w) (((x) + (y) * (w)) % 8)

ScreenBuffer::ScreenBuffer()
  : _b(nullptr)
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
  if (_b != nullptr) {
    free(_b);
  }
}

void
ScreenBuffer::setPixel(size_t x, size_t y, bool value)
{
  uint32_t mask = 1U << PIXEL_BIT(x, y, _w);
  if (value) {
    _b[PIXEL_BYTE(x, y, _w)] |= mask;
  } else {
    _b[PIXEL_BYTE(x, y, _w)] &= ~mask;
  }
}

bool
ScreenBuffer::getPixel(size_t x, size_t y)
{
  uint32_t mask = 1U << PIXEL_BIT(x, y, _w);
  return _b[PIXEL_BYTE(x, y, _w)] & mask;
}

void
ScreenBuffer::setAll(bool value)
{
  memset(_b, value ? 0xFF : 0x00, _bSize);
}
