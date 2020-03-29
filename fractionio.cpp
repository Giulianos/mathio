#include "fractionio.h"
#include "screenbufferwindow.h"

FractionIO::FractionIO(MathIO* numerator, MathIO* denominator)
  : _num(numerator)
  , _den(denominator)
  , _compact(true)
  , _cursorPos(CursorPos::OutsideFraction)
{}

int
FractionIO::getWidth()
{
  _den->setCompactMode(_compact);
  _num->setCompactMode(_compact);

  int denWidth = _den->getWidth();
  int numWidth = _num->getWidth();

  // we add one pixel padding to each side
  return (denWidth > numWidth ? denWidth : numWidth) + 2;
}

void
FractionIO::setCompactMode(bool compact)
{
  _compact = true;
}

int
FractionIO::getHeight()
{
  _den->setCompactMode(_compact);
  _num->setCompactMode(_compact);

  int denHeight = _den->getHeight();
  int numHeight = _num->getHeight();

  // numerator + denominator + 2 spaces + fraction line
  return denHeight + numHeight + 3;
}

void
FractionIO::render(ScreenBuffer* buffer)
{
  int width = getWidth();

  int numHeight = _num->getHeight();
  int numWidth  = _num->getWidth();
  int denWidth  = _den->getWidth();

  int numOffsetX = (denWidth > numWidth ? (denWidth - numWidth) / 2 : 0) + 1;
  int denOffsetX = (denWidth < numWidth ? (numWidth - denWidth) / 2 : 0) + 1;
  int denOffsetY = numHeight + 3;

  ScreenBufferWindow numBufferWindow(buffer, numOffsetX, 0);
  ScreenBufferWindow denBufferWindow(buffer, denOffsetX, denOffsetY);

  _den->render(&denBufferWindow);
  _num->render(&numBufferWindow);

  // Draw fraction line
  for (int x = 0, y = numHeight + 1; x < width; x++) {
    buffer->setPixel(x, y, true);
  }
}

void FractionIO::enableCursor(bool enable) {
    _cursorPos = enable ? CursorPos::Numerator : CursorPos::OutsideFraction;
}

bool FractionIO::moveCursor(CursorDir direction) {
    bool wrappedAroundChild = false;
    switch(direction) {
        case CursorDir::Down:
            if(_cursorPos == CursorPos::Numerator) {
                _num->enableCursor(false);
                _den->enableCursor(true);
                _cursorPos = CursorPos::Denominator;
            }
            break;
        case CursorDir::Up:
            if(_cursorPos == CursorPos::Denominator) {
                _den->enableCursor(false);
                _num->enableCursor(true);
                _cursorPos = CursorPos::Numerator;
            }
            break;
        case CursorDir::Right:
        case CursorDir::Left:
            if (_cursorPos == CursorPos::Numerator) {
                wrappedAroundChild = _num->moveCursor(direction);
                if (wrappedAroundChild) {
                    _num->enableCursor(false);
                    _cursorPos = CursorPos::OutsideFraction;
                    return true;
                }
            } else if (_cursorPos == CursorPos::Denominator) {
                wrappedAroundChild = _den->moveCursor(direction);
                if (wrappedAroundChild) {
                    _den->enableCursor(false);
                    _cursorPos = CursorPos::OutsideFraction;
                    return true;
                }
            }
    }
    return false;
}

void FractionIO::toggleCursorVisibility() {
    if (_cursorPos == CursorPos::Denominator) {
        _den->toggleCursorVisibility();
    } else if (_cursorPos == CursorPos::Numerator) {
        _num->toggleCursorVisibility();
    }
}

void FractionIO::forceCursorShow() {
    if (_cursorPos == CursorPos::Denominator) {
        _den->forceCursorShow();
    } else if (_cursorPos == CursorPos::Numerator) {
        _num->forceCursorShow();
    }
}
