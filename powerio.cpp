#include "powerio.h"
#include "screenbufferwindow.h"

#define EXP_BASE_OVERLAP 2

PowerIO::PowerIO(MathIO* base, MathIO* exp)
  : _base(base)
  , _exp(exp)
  , _compact(false)
{
  // Exponent is always compact
  _exp->setCompactMode(true);
}

int
PowerIO::getWidth()
{
  return _base->getWidth() + _exp->getWidth() + 1;
}

int
PowerIO::getHeight()
{
  return _base->getHeight() + _exp->getHeight() - EXP_BASE_OVERLAP;
}

void
PowerIO::render(ScreenBuffer* buffer)
{
  int height = getHeight();

  int bWidth  = _base->getWidth();
  int bHeight = _base->getHeight();

  int bOffsetY = height - bHeight;
  int eOffsetX = bWidth + 1;

  ScreenBufferWindow bBufferWin(buffer, 0, bOffsetY);
  ScreenBufferWindow eBufferWin(buffer, eOffsetX, 0);
  _base->render(&bBufferWin);
  _exp->render(&eBufferWin);
}

void
PowerIO::setCompactMode(bool compact)
{
  _compact = compact;
}
