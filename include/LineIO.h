//
// Created by Giulianos on 3/30/20.
//

#ifndef LINEIO_H
#define LINEIO_H

#include "MathIO.h"

class LineIO : public MathIO
{
public:
  LineIO();
  ~LineIO();

  size_t GetWidth();
  size_t GetHeight();

  void Render(ScreenBuffer* sb);

  bool MoveCursor(CursorDirection direction);
  void DetachCursor();
  void AttachCursor();

};

#endif // LINEIO_H
