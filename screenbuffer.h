#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H

#include <stdint.h>
#include <stdlib.h>

class ScreenBuffer {
	uint8_t * _b = NULL;
	size_t _w, _h;
	
	public:
		ScreenBuffer(size_t width, size_t height);
		~ScreenBuffer();

		void setPixel(int x, int y, bool value);
		bool getPixel(int x, int y);
};

#endif
