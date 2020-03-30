#ifndef POWERIO_H
#define POWERIO_H

#include "mathio.h"

class PowerIO : public MathIO
{
  MathIO* _base;
  MathIO* _exp;
  bool _compact;

public:
  PowerIO(MathIO* base, MathIO* exp);

  int getWidth();
  int getHeight();
  void render(ScreenBuffer* buffer);
  void setCompactMode(bool compact);
};

#endif
