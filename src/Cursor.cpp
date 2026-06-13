#include "Cursor.h"

stl::Cursor::Cursor() {
}

stl::Cursor::~Cursor() {
}

std::string stl::cursor_move(const size_t x, const size_t y) {
  return "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H"; }

std::string stl::cursor_forward(const size_t& x) {
  return "\033[" + std::to_string(x) + "C"; }

std::string stl::cursor_back(const size_t& x) {
  return "\033[" + std::to_string(x) + "D"; }

std::string stl::cursor_up(const size_t& y) {
  return "\033[" + std::to_string(y) + "A"; }

std::string stl::cursor_down(const size_t& y) {
  return "\033[" + std::to_string(y) + "B"; }

std::string stl::cursor_on() {
  return "\033[?25h"; }

std::string stl::cursor_off() {
  return "\033[?25l"; }
