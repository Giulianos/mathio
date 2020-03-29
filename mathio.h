#ifndef MATHIO_H
#define MATHIO_H

#include "screenbuffer.h"

class MathIO
{
public:
  enum class CursorDir {
	  Up,
	  Down,
	  Left,
	  Right,
  };

  virtual int getWidth()                    = 0;
  virtual int getHeight()                   = 0;
  virtual void render(ScreenBuffer* buffer) = 0;
  virtual void setCompactMode(bool compact) = 0;
  virtual void enableCursor(bool enable) = 0;
  // Returns whether wrapped around or not
  virtual bool moveCursor(CursorDir direction) = 0;
  virtual void toggleCursorVisibility() = 0; 
  virtual void forceCursorShow() = 0;
};

#endif
