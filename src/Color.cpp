#include "Color.h"

stl::Style stl::Color::style_hex(const Hex& style) const {
  return Style(style.fg, style.bg, ColorMode::TRUECOLOR);
}

stl::Style stl::Color::style_rgb(const RGB& fg, const RGB& bg) const {
  return Style(
    (fg.r << 16) | (fg.g << 8) | fg.b,
    (bg.r << 16) | (bg.g << 8) | bg.b,
    ColorMode::TRUECOLOR
  );
}

stl::Style stl::Color::style_ansi256(const ANSI256& fg, const ANSI256& bg) const {
  return Style(fg.value, bg.value, ColorMode::ANSI256);
}

stl::Style stl::Color::style_ansi16(const COLOR fg, const COLOR bg, BOLD_MODE mode) const {
  short fgValue = static_cast<short>(fg);
  short bgValue = static_cast<short>(bg);
  switch (mode) {
    case BOLD_MODE::BOTH:
      fgValue += 90;
      bgValue += 100;
      break;
    case BOLD_MODE::FG:
      fgValue += 90;
      bgValue += 40;
      break;
    case BOLD_MODE::BG:
      fgValue += 30;
      bgValue += 100;
      break;
    default:
      fgValue += 30;
      bgValue += 40;
      break;
  }
  return Style(fgValue, bgValue, ColorMode::ANSI16);
}

std::string stl::Color::color(const Hex& hex) {
  return "\033[38;2;"
    + std::to_string((hex.fg >> 16) & 0xFF) + ";"
    + std::to_string((hex.fg >> 8)  & 0xFF) + ";"
    + std::to_string( hex.fg        & 0xFF) + "m"
    + "\033[48;2;"
    + std::to_string((hex.bg >> 16) & 0xFF) + ";"
    + std::to_string((hex.bg >> 8)  & 0xFF) + ";"
    + std::to_string( hex.bg        & 0xFF) + "m";
}

std::string stl::Color::color(const RGB& fg, const RGB& bg) {
  return "\033[38;2;"
    + std::to_string(fg.r) + ";"
    + std::to_string(fg.g) + ";"
    + std::to_string(fg.b) + "m"
    + "\033[48;2;"
    + std::to_string(bg.r) + ";"
    + std::to_string(bg.g) + ";"
    + std::to_string(bg.b) + "m";;
}

std::string stl::Color::color(const ANSI256& fg, const ANSI256& bg) {
  return 
    "\033[38;5;" + std::to_string(fg.value) + "m"
    "\033[48;5;" + std::to_string(bg.value) + "m";
}

std::string stl::Color::color(COLOR fg, COLOR bg, bool isBold) {
  std::string sequence = (isBold) ?
    color_bg(bg, true) + color_fg(fg, true) :
    color_bg(bg) + color_fg(fg);
  return sequence;
}


std::string stl::Color::color_fg(COLOR fg, bool isBold) {
  short value = static_cast<short>(fg);
  if (value > 7 || value < 0) return "\033[37m";
  std::string sequence = (isBold)
    ? "\033[1;3" + std::to_string(value) + "m"
    : "\033[3" + std::to_string(value) + "m";
  return sequence;
}

std::string stl::Color::color_bg(COLOR bg, bool isBold) {
  short value = static_cast<short>(bg);
  if (value > 7 || value < 0) return "\033[40m";
  std::string sequence = (isBold)
    ? "\033[10" + std::to_string(value) + "m"
    : "\033[4" + std::to_string(value) + "m";
  return sequence;
}


std::string stl::Color::color_reset() { return "\033[0m"; }
