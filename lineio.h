#ifndef LINEIO_H
#define LINEIO_H

#include "mathio.h"

class LineIO : public MathIO
{
  uint8_t* _text;
  int _len;
  bool _compact;

  void renderRect(ScreenBuffer* buffer, int x0, int y0, int width, int height);
  void renderCompactChar(ScreenBuffer* buffer, const uint8_t c, int x0, int y0);

public:
  LineIO(const uint8_t* text);
  ~LineIO();

  int getWidth();
  int getHeight();
  void render(ScreenBuffer* buffer);

  // This makes the renderer
  // output a compact form
  // (used in exponents, fractions, etc.)
  void setCompactMode(bool compact);
};

#endif
