#pragma once
#include "geometry/Point.h"
#include "geometry/Size.h"

namespace stl {
	/// <summary>
	/// Represents a rectangle defined by a position and its dimensions.
	/// </summary>
	struct Rect {
		Point pos;		// Start position
		Size  size;		// Width and Height
	};
}