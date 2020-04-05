//
// Created by Giulianos on 4/1/20.
//

#include <LineIO.h>
#include <font.h>

const size_t LineIO::CharacterWidth  = 5;
const size_t LineIO::CharacterHeight = 6;

LineIO::LineIO()
  : mText(nullptr)
  , mTextCap(5)
  , mTextLen(0)
  , mCursorPos(0)
  , mCursorAttached(false)
{
  mText = (uint8_t*)calloc(mTextCap, sizeof(*mText));
}

LineIO::~LineIO()
{
  if (mText != nullptr) {
    free(mText);
  }
}

size_t
LineIO::GetWidth()
{
  return mTextLen * (CharacterWidth + 1) - 1;
}

size_t
LineIO::GetHeight()
{
  return CharacterHeight;
}

void
LineIO::RenderCharacter(ScreenBuffer* buffer, uint8_t c, size_t x0, size_t y0)
{
  // Render unknown character
  if (c > 9) {
    c = 10;
  }
  uint8_t* m = font[c];

  for (int x = 0; x < CharacterWidth; x++) {
    for (int y = 0; y < CharacterHeight; y++) {
      size_t bit = x + y * CharacterWidth;
      buffer->setPixel(x + x0, y + y0, m[bit / 8] & (1UL << (bit % 8)));
    }
  }
}

void
LineIO::Render(ScreenBuffer* sb)
{
  for (size_t i = 0; i < mTextLen; i++) {
    size_t xPos  = (CharacterWidth + 1) * i;
    uint8_t cIdx = mText[i] - '0';
    RenderCharacter(sb, cIdx, xPos, 0);
  }

  // Check if we have to render the cursor
  if (mCursorAttached) {
    size_t cursorX = (CharacterWidth + 1) * mCursorPos;
    for (int y = 0; y < GetHeight(); y++) {
      sb->setPixel(cursorX - 1, y, true);
      sb->setPixel(cursorX, y, true);
    }
  }
}
bool
LineIO::MoveCursor(MathIO::CursorDirection direction)
{
  switch (direction) {
    case CursorDirection ::Left:
      if (mCursorPos == 0) {
        mCursorPos = mTextLen;
        return true;
      }
      mCursorPos--;
      break;
    case CursorDirection ::Right:
      if (mCursorPos == mTextLen) {
        mCursorPos = 0;
        return true;
      }
      mCursorPos++;
      break;
    case CursorDirection ::Up:
    case CursorDirection ::Down:
      return true;
  }

  return false;
}

void
LineIO::DetachCursor()
{
  mCursorAttached = false;
}

void
LineIO::AttachCursor()
{
  mCursorPos      = 0;
  mCursorAttached = true;
}

void
LineIO::InsertCharacter(uint8_t character)
{
  // Reserve more space if necessary
  if (mTextLen == mTextCap) {
    mTextCap *= 2;
    mText = (uint8_t*)realloc(mText, mTextCap * sizeof(*mText));
  }

  // Shift current text
  for (size_t txtIdx = mTextLen; txtIdx > mCursorPos; txtIdx--) {
    mText[txtIdx] = mText[txtIdx - 1];
  }

  mText[mCursorPos] = character;
  mTextLen++;
  mCursorPos++;
}

void
LineIO::AddContainer(MathIO::ContainerType containerType)
{}

MathIO::ContainerType
LineIO::GetContainerType()
{
  return MathIO::ContainerType::Line;
}
