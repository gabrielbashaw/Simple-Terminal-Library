#pragma once
#include <iostream>
#include <vector>
#include "geometry/point.h"
#include "geometry/size.h"
#include "ui/color.h"

namespace stl {
	// A cell in the window buffer
	struct Cell {
		char glyph = ' ';
		bool isDirty = true;
		stl::Style style;
	};

	class Buffer {
	public:
		Buffer(Size size);

		// Get a cell at position
		Cell& get_cell(Point pos);
		// Put a cell at position
		std::ostream& put(Point pos, std::ostream& os = std::cout);
		// Update cell at position with new glyph
		void update_cell(Point pos, char newGlyph);
		// Apply cell at position with new style
		void update_cell_style(Point pos, Style style);
		// Cleans dirty cells
		void clean(Point pos);

	private:
		Size _size;
		std::vector<std::vector<Cell>> _cells;
	};
}