#ifndef BUFFER_WINDOW_H
#define BUFFER_WINDOW_H

#include <screenbuffer.h>

class ScreenBufferWindow : public ScreenBuffer
{
  ScreenBuffer* _sbRef;
  int _offsetX, _offsetY;

public:
  ScreenBufferWindow(ScreenBuffer* b, int offsetX, int offsetY);

  void setPixel(size_t x, size_t y, bool value) override;
  bool getPixel(size_t x, size_t y) override;
};

#endif
