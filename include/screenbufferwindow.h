#ifndef BUFFER_WINDOW_H
#define BUFFER_WINDOW_H

#include "screenbuffer.h"

class ScreenBufferWindow : public ScreenBuffer
{
  ScreenBuffer* _sbRef;
  int _offsetX, _offsetY;

public:
  ScreenBufferWindow(ScreenBuffer* b, int offsetX, int offsetY);

  void setPixel(int x, int y, bool value);
  bool getPixel(int x, int y);
};

#endif
