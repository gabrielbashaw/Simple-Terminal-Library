#pragma once
#include <vector>
#include "geometry/Point.h"
#include "geometry/Size.h"
#include "ui/Color.h"

namespace stl {
	// A cell in the window buffer
	struct Cell {
		char  glyph = ' ';
		bool  isDirty = true;
		stl::Style style;
	};

	class Buffer {
	public:
		Buffer(Size size);

		// Gets cell at position
		Cell& get_cell(Point pos);
		// Put cell at position
		std::ostream& put(Point pos, std::ostream& os = std::cout);
		// Update cell at position with new glyph
		void update_cell(Point pos, char glyph);
		// Apply cell style at position
		void cell_style(Point pos, Style style);
		// Cleans dirty cells
		void clean(Point pos);

	private:
		Size _size;
		std::vector<std::vector<Cell>> _cells;
	};
}