#ifndef MATHIO_H
#define MATHIO_H

class MathIO
{
public:
  virtual int getWidth()                    = 0;
  virtual int getHeight()                   = 0;
  virtual void render(ScreenBuffer* buffer) = 0;
  virtual void setCompactMode(bool compact) = 0;
};

#endif
