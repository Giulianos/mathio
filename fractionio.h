#ifndef FRACTIONIO_H
#define FRACTIONIO_H

#include "mathio.h"

class FractionIO : public MathIO {
    MathIO* _num;
    MathIO* _den;
    bool _compact;
    std::vector<bool> _renderBuff;
    
    public:
        FractionIO(MathIO* numerator, MathIO* denominator);

        int getWidth();
        int getHeight();
        std::vector<bool> getRender();
        void setCompactMode(bool compact);
};

#endif
