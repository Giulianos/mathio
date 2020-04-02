//
// Created by Giulianos on 3/30/20.
//

#ifndef MATHIO_LINEIO_H
#define MATHIO_LINEIO_H

#include "MathIO.h"

class LineIO : public MathIO
{
  uint8_t* mText;
  size_t mTextLen;
  size_t mTextCap;

  size_t mCursorPos;
  bool mCursorAttached;

  static const size_t CharacterWidth;
  static const size_t CharacterHeight;

  static void RenderCharacter(ScreenBuffer* buffer, uint8_t c, size_t x0, size_t y0);

public:
  LineIO();
  ~LineIO();

  size_t GetWidth() override;
  size_t GetHeight() override;

  void Render(ScreenBuffer* sb) override;

  bool MoveCursor(CursorDirection direction) override;
  void DetachCursor() override;
  void AttachCursor() override;

  void InsertCharacter(uint8_t character) override;
  void AddContainer(ContainerType containerType) override;
};

#endif // MATHIO_LINEIO_H
