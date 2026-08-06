#include "widgets/Window.h"

stl::Window::Window(WindowConfig& cfg) 
  : _cfg(cfg), _buffer(cfg.bounds.size) {
  fill();
}

void stl::Window::border() {
  unsigned short x   = columns() - 1;
  unsigned short y   = rows() - 1;
  BorderChars border = _cfg.border;

  // Window Corners
  _buffer.update_cell({ 0, 0 }, border.topLeft);
  _buffer.update_cell({ x, 0 }, border.topRight);
  _buffer.update_cell({ 0, y }, border.bottomLeft);
  _buffer.update_cell({ x, y }, border.bottomRight);

  // Draw top and bottom borders
  for (unsigned short i = 1; i < x; ++i) {
    _buffer.update_cell({ i, 0 }, border.top);
    _buffer.update_cell({ i, y }, border.bottom);
  }

  // Draw left and right borders
  for (unsigned short i = 1; i < y; ++i) {
    _buffer.update_cell({ 0, i }, border.left);
    _buffer.update_cell({ x, i }, border.right);
  }
}

void stl::Window::fill() {
  for (unsigned short c = 0; c < columns(); c++) {
    for (unsigned short r = 0; r < rows(); r++) {
      Point pos = { c, r };
      if ((c == 0 || c == columns() - 1) || (r == 0 || r == rows() - 1))
        _buffer.cell_style(pos, _cfg.styleBorder);
      else
        _buffer.cell_style(pos, _cfg.styleBody);
    }
  }
}

void stl::Window::print_random_garbage() {
  for (unsigned short y = 0; y < rows(); y++) {
    for (unsigned short x = 0; x < columns(); x++) {
      char randChar = ' ' + (rand() % 95); // Random ASCII char
      _buffer.update_cell({ x, y }, randChar);
    }
  }
}

void stl::Window::print(Point pos, const std::string_view text) {
  unsigned short length = text.size();

  if (pos.x >= columns() || pos.y >= rows()) return;

  for (unsigned short i = 0; i < length && (pos.x + i) < columns(); ++i) {
    _buffer.update_cell({ pos.x + i, pos.y }, text[i]);
  }
}

void stl::Window::refresh() {
  render(*this);
}

void stl::Window::render(Window& win, std::ostream& os) {
  for (size_t y = 0; y < rows(); y++) {
    bool cursorMoved = false;
    for (size_t x = 0; x < columns(); x++) {
      Point pos = { x, y };

      if (!_buffer.get_cell(pos).isDirty) {
        cursorMoved = false;
        continue;
      }

      if (!cursorMoved) {
        Point pos_c = { _cfg.bounds.pos.x + x + 1, _cfg.bounds.pos.y + y + 1 };
        os << stl::cursor_move(pos_c);
        cursorMoved = true;
      }

      _buffer.put(pos);
    }
  }
}
