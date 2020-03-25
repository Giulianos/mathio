#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <stdint.h>
#include <stdlib.h>

class ScreenBuffer
{
  uint8_t* _b;
  size_t _w, _h;

protected:
  ScreenBuffer();

public:
  ScreenBuffer(size_t width, size_t height);
  ~ScreenBuffer();

  virtual void setPixel(int x, int y, bool value);
  virtual bool getPixel(int x, int y);
};

#endif
