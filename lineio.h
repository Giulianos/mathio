#ifndef LINEIO_H
#define LINEIO_H

#include "mathio.h"

class LineIO : public MathIO
{
  char * _text;
  bool _compact;

  void renderRect(ScreenBuffer* buffer, int x0, int y0, int width, int height);

public:
  LineIO(const char * text);

  int getWidth();
  int getHeight();
  void render(ScreenBuffer* buffer);

  // This makes the renderer
  // output a compact form
  // (used in exponents, fractions, etc.)
  void setCompactMode(bool compact);
};

#endif
