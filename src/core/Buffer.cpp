#include "core/buffer.h"

stl::Buffer::Buffer(Size size) 
  : _size(size), _cells(size.rows().get(), std::vector<Cell>(size.columns().get())) {
}

stl::Cell& stl::Buffer::get_cell(Point pos) {
  return _cells[pos.y][pos.x];
}

std::ostream& stl::Buffer::put(Point pos, std::ostream& os) {
  Cell& cell = get_cell(pos);
  os << stl::Ansi::apply(cell.style) << cell.glyph << stl::Ansi::reset();
  clean(pos);
  return os;
}

void stl::Buffer::update_cell(Point pos, char newGlyph) {
  Cell& cell = get_cell(pos);
  if (cell.glyph == newGlyph) return;
  cell.glyph = newGlyph;
  cell.isDirty = true;
}

void stl::Buffer::update_cell_style(Point pos, Style style) {
  get_cell(pos).style = style;
}

void stl::Buffer::clean(Point pos) {
  get_cell(pos).isDirty = false;
}
