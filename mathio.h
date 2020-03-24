#ifndef MATHIO_H
#define MATHIO_H

#include <vector>

class MathIO {
    public:
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;
        virtual std::vector<bool> getRender() = 0;
};

#endif
