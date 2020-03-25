#ifndef FRACTIONIO_H
#define FRACTIONIO_H

#include "mathio.h"

class FractionIO : public MathIO {
    MathIO* _num;
    MathIO* _den;
    bool _compact;
    
    public:
        FractionIO(MathIO* numerator, MathIO* denominator);

        int getWidth();
        int getHeight();
	void render(ScreenBuffer* buffer);
        void setCompactMode(bool compact);
};

#endif
