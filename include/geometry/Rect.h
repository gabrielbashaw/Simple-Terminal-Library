#pragma once
#include "geometry/point.h"
#include "geometry/size.h"

namespace stl {
	/// @brief Represents a rectangle defined by a position and its dimensions
	struct Rect {
		Point pos;		// Start position
		Size  size;		// Width and Height
	};
}