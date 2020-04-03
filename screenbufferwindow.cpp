#include "screenbufferwindow.h"

ScreenBufferWindow::ScreenBufferWindow(ScreenBuffer* b,
                                       int offsetX,
                                       int offsetY)
  : _sbRef(b)
  , _offsetX(offsetX)
  , _offsetY(offsetY)
{}

void
ScreenBufferWindow::setPixel(size_t x, size_t y, bool value)
{
  _sbRef->setPixel(x + _offsetX, y + _offsetY, value);
}

bool
ScreenBufferWindow::getPixel(size_t x, size_t y)
{
  return _sbRef->getPixel(x + _offsetX, y + _offsetY);
}
