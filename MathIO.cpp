//
// Created by Giulianos on 3/30/20.
//

#include <MathIO.h>
#include <screenbufferwindow.h>

MathIO::MathIO() : mChildrenCount(0), mCursorAttached(true), mCursorPos(0) {
  mChildrenCap = 5;
  mChildren = (MathIO **)calloc(mChildrenCap, sizeof(*mChildren));
}

MathIO::~MathIO() {
  // Free created children
  for (size_t childIdx = 0; childIdx < mChildrenCount; childIdx++) {
    free(mChildren[childIdx]);
  }

  // Free array
  free(mChildren);
}

size_t MathIO::GetWidth() {
  // TODO: cache result
  size_t width = 0;
  for(size_t childIdx = 0; childIdx < mChildrenCount; childIdx++) {
    width += mChildren[childIdx]->GetWidth();
    if (childIdx != mChildrenCount - 1) {
      width++;
    }
  }

  return width;
}

size_t MathIO::GetHeight() {
  // TODO: cache result
  size_t height = 0;
  for(size_t childIdx = 0; childIdx < mChildrenCount; childIdx++) {
    int childHeight = mChildren[childIdx]->GetHeight();
    if (childHeight > height) {
      height = childHeight;
    }
  }

  return height;
}

void MathIO::Render(ScreenBuffer *sb) {
  size_t height = GetHeight();
  size_t xPos = 0;
  for (int childIdx = 0; childIdx < mChildrenCount; childIdx++) {
    // Get child reference
    MathIO* child = mChildren[childIdx];

    // Calculate child's dimensions
    size_t childHeight = child->GetHeight();
    size_t childWidth = child->GetWidth();
    size_t yPos = (height - childHeight)/2;

    // Render child in windowed buffer
    ScreenBufferWindow childBuff(sb, xPos, yPos);
    child->Render(&childBuff);

    // Update xPos for next child (adding a 1px margin)
    xPos += childWidth + 1;
  }
}

bool MathIO::MoveCursor(CursorDirection direction) {
  // TODO: implement method
  return false;
}

void MathIO::DetachCursor() {
  // TODO: implement method
}

void MathIO::AttachCursor() {
  // TODO: implement method
}

void MathIO::InsertCharacter(uint8_t character) {
  // TODO: implement method
}

void MathIO::AddContainer(ContainerType containerType) {
  // Check if we have to resize array
  if (mChildrenCap == mChildrenCount) {
    mChildrenCap *= 2;
    mChildren = (MathIO**)realloc((void*)mChildren, mChildrenCap*sizeof(*mChildren));
  }

  switch(containerType) {
    case ContainerType ::Fraction:
    case ContainerType::Power:
    case ContainerType ::Root:
      ;
  }
}