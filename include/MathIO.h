//
// Created by Giulianos on 3/30/20.
//

#ifndef MATHIO_H
#define MATHIO_H

#include "screenbuffer.h"

/**
 * MathIO is a container
 * that displays and allows editing
 * of mathematical formulas
 */
class MathIO {
  MathIO** mChildren;
  size_t mChildrenCount;
  size_t mChildrenCap;

  bool mCursorAttached;
  size_t mCursorPos;

public:
  /**
   * CursorDirection indicates
   * a cursor movement direction
   */
  enum class CursorDirection {
    Up,
    Down,
    Left,
    Right
  };

  /**
   * ContainerTypes defines the
   * different types of containers
   * that can be created
   */
  enum class ContainerType {
    Fraction,
    Power,
    Root,
  };

  MathIO();
  ~MathIO();

  /**
   * GetWidth
   * @return the width of the container in pixels
   */
  virtual size_t GetWidth();
  /**
   * GetHeight
   * @return the height of the container in pixels
   */
  virtual size_t GetHeight();

  /**
   * Render renders the container to the buffer
   * @param sb the screen buffer where the container
   * will be rendered to
   */
  virtual void Render(ScreenBuffer* sb);

  /**
   * MoveCursor moves the cursor
   * if an overflow occurs the cursor
   * wraps around the container
   * @param direction where to move the cursor to
   * @return if the movement results in an overflow
   */
  virtual bool MoveCursor(CursorDirection direction);

  /**
   * DetachCursor removes the cursor from the container
   */
  virtual void DetachCursor();

  /**
   * AttachCursor enables the cursor in the
   * container (or one of its children)
   */
  virtual void AttachCursor();

  /**
   * InsertCharacter inserts character
   * into cursor's current position
   * @param character
   */
  virtual void InsertCharacter(uint8_t character);

  /**
   * AddContainer adds a containerType
   * container into the current cursor
   * position
   * @param containerType
   */
  virtual void AddContainer(ContainerType containerType);

};

#endif // MATHIO_H
