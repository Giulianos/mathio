#include "screenbuffer.h"

#include <stdlib.h>
#include <iostream>

// TODO: refactor pixel indexing to
// make interfacing with SSD1306 easier
#define PIXEL_BYTE(x, y, w) (((x) + (y)*(w))/8)
#define PIXEL_BIT(x, y, w) (((x) + (y)*(w))%8)

ScreenBuffer::ScreenBuffer(size_t width, size_t height) : _w(width), _h(height) {
	size_t bufferSize = width*height/8;
	bufferSize += width*height%8 ? 1 : 0;

	_b = (uint8_t*)calloc(bufferSize, sizeof(*_b));
}

ScreenBuffer::~ScreenBuffer() {
	if (_b != NULL) {
		free(_b);
	}
}

void ScreenBuffer::setPixel(int x, int y, bool value) {
	int pixelByte = PIXEL_BYTE(x,y,_w);
	int pixelBit = PIXEL_BIT(x,y,_w);
	std::cout << "Setting pixel in byte " << pixelByte << " bit " << pixelBit << std::endl;
	if (value) {	
		_b[PIXEL_BYTE(x,y,_w)] |= 1<<(PIXEL_BIT(x,y,_w));	
	} else {
		_b[PIXEL_BYTE(x,y,_w)] &= ~(1<<(PIXEL_BIT(x,y,_w)));	
	}
}

bool ScreenBuffer::getPixel(int x, int y) {
	return _b[PIXEL_BYTE(x,y,_w)] & 1<<(PIXEL_BIT(x,y,_w));	
}

