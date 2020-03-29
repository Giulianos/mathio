#include "lineio.h"
#include "font.h"
#include <stdlib.h>
#include <string.h>

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 9
#define CHAR_COMPACT_HEIGHT 6

LineIO::LineIO(const uint8_t* text)
  : _compact(false),
    _cursorPos(-1),
    _cursorVisible(true)
{
  _len  = strlen((char*)text);
  _text = (uint8_t*)calloc(_len + 1, sizeof(*_text));
  strcpy((char*)_text, (char*)text);
}

LineIO::~LineIO()
{
	free(_text);
}

int
LineIO::getWidth()
{
  return !_len ? 0 : _len * (CHAR_WIDTH + 1) - 1;
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
LineIO::renderCompactChar(ScreenBuffer* buffer, uint8_t c, int x0, int y0)
{
  if (c > 9) {
    c = 10;
  }
  uint8_t* m = fontCompact[c];

  for (int x = 0; x < CHAR_WIDTH; x++) {
    for (int y = 0; y < CHAR_COMPACT_HEIGHT; y++) {
      int bit = x + y * CHAR_WIDTH;
      buffer->setPixel(x + x0, y + y0, m[bit / 8] & 1 << (bit % 8));
    }
  }
}

void
LineIO::render(ScreenBuffer* buffer)
{
  for (int i = 0; i < _len; i++) {
    int xPos = (CHAR_WIDTH + 1) * i;
    if (_compact) {
      uint8_t cIdx = _text[i] - '0';
      renderCompactChar(buffer, cIdx, xPos, 0);
    } else {
      renderRect(buffer, xPos, 0, CHAR_WIDTH, CHAR_HEIGHT);
    }
  }

  // Check if we have to render the cursor
  if (_cursorPos >= 0 && _cursorVisible) {
	  int cursorX = (CHAR_WIDTH + 1) * _cursorPos;
	  for (int y=0; y < getHeight(); y++) {
		buffer->setPixel(cursorX-1, y, true);
		buffer->setPixel(cursorX, y, true);
	  }
  }

}

void
LineIO::setCompactMode(bool compact)
{
  _compact = compact;
}


void LineIO::enableCursor(bool enable) {
  _cursorPos = enable ? 0 : -1;	
}

bool LineIO::moveCursor(CursorDir direction) {

  switch(direction) {
    case CursorDir::Left:
	    _cursorPos--;
	    break;
    case CursorDir::Right:
	    _cursorPos++;
	    break;
    case CursorDir::Up:
    case CursorDir::Down:
        break;
  }
  
  // Check wrapping around
  if (_cursorPos < 0) {
    _cursorPos = _len - 1;
    return true;
  }

  if (_cursorPos >= _len) {
    _cursorPos = 0;
    return true;
  }

  return false;
}

void LineIO::toggleCursorVisibility() {
	_cursorVisible = !_cursorVisible;
}

void LineIO::forceCursorShow() {
	_cursorVisible = true;
}
	
