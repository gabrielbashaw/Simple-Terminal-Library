#pragma once
#include <string>
#include "geometry/Point.h"

namespace stl {
  // Move cursor to (x, y)
  std::string cursor_move(Point pos);
  // Move cursor forward 'x' cells
  std::string cursor_forward(size_t x);
  // Move cursor back 'x' cells
  std::string cursor_back(size_t x);
  // Move cursor up 'y' cells
  std::string cursor_up(size_t y);
  // Move cursor down  'y' cells
  std::string cursor_down(size_t y);
  // Turn cursor on
  std::string cursor_on();
  // Turn cursor off
  std::string cursor_off();
}
