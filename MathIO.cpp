//
// Created by Giulianos on 3/30/20.
//

#include <LineIO.h>
#include <MathIO.h>
#include <screenbufferwindow.h>

MathIO::MathIO()
  : mChildrenCount(0)
  , mCursorAttached(true)
  , mCursorPos(0)
{
  mChildrenCap = 5;
  mChildren    = (MathIO**)calloc(mChildrenCap, sizeof(*mChildren));
}

MathIO::~MathIO()
{
  // Free created children
  for (size_t childIdx = 0; childIdx < mChildrenCount; childIdx++) {
    free(mChildren[childIdx]);
  }

  // Free array
  free(mChildren);
}

size_t
MathIO::GetWidth()
{
  // TODO: cache result
  size_t width = 0;
  for (size_t childIdx = 0; childIdx < mChildrenCount; childIdx++) {
    width += mChildren[childIdx]->GetWidth();
    if (childIdx != mChildrenCount - 1) {
      width++;
    }
  }

  return width;
}

size_t
MathIO::GetHeight()
{
  // TODO: cache result
  size_t height = 0;
  for (size_t childIdx = 0; childIdx < mChildrenCount; childIdx++) {
    int childHeight = mChildren[childIdx]->GetHeight();
    if (childHeight > height) {
      height = childHeight;
    }
  }

  return height;
}

void
MathIO::Render(ScreenBuffer* sb)
{
  size_t height = GetHeight();
  size_t xPos   = 0;
  for (int childIdx = 0; childIdx < mChildrenCount; childIdx++) {
    // Get child reference
    MathIO* child = mChildren[childIdx];

    // Calculate child's dimensions
    size_t childHeight = child->GetHeight();
    size_t childWidth  = child->GetWidth();
    size_t yPos        = (height - childHeight) / 2;

    // Render child in windowed buffer
    ScreenBufferWindow childBuff(sb, xPos, yPos);
    child->Render(&childBuff);

    // Update xPos for next child (adding a 1px margin)
    xPos += childWidth + 1;
  }
}

bool
MathIO::MoveCursor(CursorDirection direction)
{
  bool childWrappedAround = mChildren[mCursorPos]->MoveCursor(direction);
  return childWrappedAround;
}

void
MathIO::DetachCursor()
{
  mChildren[mCursorPos]->DetachCursor();
  mCursorAttached = false;
}

void
MathIO::AttachCursor()
{
  mCursorPos      = 0;
  mCursorAttached = true;
  if (mChildrenCount > 0) {
    mChildren[mCursorPos]->AttachCursor();
  }
}

void
MathIO::InsertCharacter(uint8_t character)
{
  // If we don't have a child container,
  // we add a line container
  if (mChildrenCount == 0) {
    AddContainer(ContainerType::Line);
    mChildren[mCursorPos]->AttachCursor();
  }

  mChildren[mCursorPos]->InsertCharacter(character);
}

void
MathIO::AddContainer(ContainerType containerType)
{
  // Check if we have to resize array
  if (mChildrenCap == mChildrenCount) {
    mChildrenCap *= 2;
    mChildren =
      (MathIO**)realloc((void*)mChildren, mChildrenCap * sizeof(*mChildren));
  }

  // TODO: Shift all containers if necessary
  switch (containerType) {
    case ContainerType::Line:
      mChildren[mCursorPos] = new LineIO();
      mChildrenCount++;
    case ContainerType::Fraction:
    case ContainerType::Power:
    case ContainerType::Root:
    case ContainerType::Math:
      break;
  }
}

MathIO::ContainerType
MathIO::GetContainerType()
{
  return ContainerType::Math;
}
