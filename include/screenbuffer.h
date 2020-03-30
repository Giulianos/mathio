#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <stdint.h>
#include <stdlib.h>

class ScreenBuffer
{
  uint8_t* _b;
  size_t _w{}, _h{}, _bSize{};

protected:
  ScreenBuffer();

public:
  ScreenBuffer(size_t width, size_t height);
  ~ScreenBuffer();

  virtual void setPixel(size_t x, size_t y, bool value);
  virtual bool getPixel(size_t x, size_t y);
  virtual void setAll(bool value);
};

#endif
