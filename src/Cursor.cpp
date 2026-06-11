#include "Cursor.h"

STL::Cursor::Cursor() {
}

STL::Cursor::~Cursor() {
}

std::string STL::cursor_move(const size_t x, const size_t y) {
  return "\033[" + std::to_string(y) + ";" + std::to_string(x) + "H"; }

std::string STL::cursor_forward(const size_t& x) {
  return "\033[" + std::to_string(x) + "C"; }

std::string STL::cursor_back(const size_t& x) {
  return "\033[" + std::to_string(x) + "D"; }

std::string STL::cursor_up(const size_t& y) {
  return "\033[" + std::to_string(y) + "A"; }

std::string STL::cursor_down(const size_t& y) {
  return "\033[" + std::to_string(y) + "B"; }

std::string STL::cursor_on() {
  return "\033[?25h"; }

std::string STL::cursor_off() {
  return "\033[?25l"; }
