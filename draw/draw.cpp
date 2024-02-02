
#include "draw.hpp"

#ifndef DRAW_CPP
#define DRAW_CPP

namespace draw {
	
	buffer<rgb8> * frame_buffer = nullptr;

	bool init(buffer<rgb8>* frame_buffer_) {

		if (frame_buffer_ == nullptr) return false;

		draw::frame_buffer = frame_buffer_;
		return true;
	}

	bool destroy() {
		draw::frame_buffer = nullptr;

		return true;
	}

	void set_pixle(uint16_t x, uint16_t y, rgb8& color) {
		frame_buffer->memory[ frame_buffer->width * x + y] = color;
	}

}
// end : namespace draw

#endif
