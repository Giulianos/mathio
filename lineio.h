#ifndef LINEIO_H
#define LINEIO_H

#include "mathio.h"
#include <string>

class LineIO : public MathIO {
    std::string _text;
    bool _compact;

    void renderRect(int x0, int y0, int width, int height);

    public:
        LineIO(const std::string text);

        int getWidth();
        int getHeight();
	void render(ScreenBuffer* buffer);

        // This makes the renderer
        // output a compact form
        // (used in exponents, fractions, etc.)
        void setCompactMode(bool compact);
};

#endif
