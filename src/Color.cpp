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

stl::Style stl::Color::style_ansi256(const short fg, const short bg) const {
  return Style(fg, bg, ColorMode::ANSI256);
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
