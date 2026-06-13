#pragma once
#include <string>

namespace stl {
  /// <summary>
  /// Currently does nothing!
  /// Use 'stl::cursor...' functions
  /// </summary>
  class Cursor {
  public:
    Cursor();
    ~Cursor();
  };

  // Move cursor to (x, y)
  std::string cursor_move(const size_t x, const size_t y);
  // Move cursor forward 'x' cells
  std::string cursor_forward(const size_t& x);
  // Move cursor back 'x' cells
  std::string cursor_back(const size_t& x);
  // Move cursor up 'y' cells
  std::string cursor_up(const size_t& y);
  // Move cursor down  'y' cells
  std::string cursor_down(const size_t& y);
  // Turn cursor on
  std::string cursor_on();
  // Turn cursor off
  std::string cursor_off();
}
