#include "Cursor.h"

std::string stl::cursor_move(Point pos) {
  return "\033[" + std::to_string(pos.y) + ";" + std::to_string(pos.x) + "H"; }

std::string stl::cursor_forward(size_t x) {
  return "\033[" + std::to_string(x) + "C"; }

std::string stl::cursor_back(size_t x) {
  return "\033[" + std::to_string(x) + "D"; }

std::string stl::cursor_up(size_t y) {
  return "\033[" + std::to_string(y) + "A"; }

std::string stl::cursor_down(size_t y) {
  return "\033[" + std::to_string(y) + "B"; }

std::string stl::cursor_on() {
  return "\033[?25h"; }

std::string stl::cursor_off() {
  return "\033[?25l"; }
