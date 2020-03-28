#include "fractionio.h"
#include "screenbufferwindow.h"

FractionIO::FractionIO(MathIO* numerator, MathIO* denominator)
  : _num(numerator)
  , _den(denominator)
  , _compact(true)
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
