#include "ui/Color.h"

/* ====================================================== */
/*                  Color Class Functions                 */
/* ====================================================== */

stl::Style stl::Color::style(ColorValue fg, ColorValue bg, Attribute attr) {
  return { fg, bg, attr };
}

stl::Style stl::Color::style_hex(Hex fg, Hex bg, Attribute attr) {
  return style(
    ColorValue::hex(fg),
    ColorValue::hex(bg),
    attr
  );
}

stl::Style stl::Color::style_hex(Hex color, Attribute attr) {
  return style(
    ColorValue::hex(color),
    ColorValue::hex(color),
    attr
  );
}

stl::Style stl::Color::style_rgb(RGB fg, RGB bg, Attribute attr) {
  return style(
    ColorValue::rgb(fg[0], fg[1], fg[2]),
    ColorValue::rgb(bg[0], bg[1], bg[2]),
    attr
  );
}

stl::Style stl::Color::style_rgb(RGB color, Attribute attr) {
  return style(
    ColorValue::rgb(color[0], color[1], color[2]),
    ColorValue::rgb(color[0], color[1], color[2]),
    attr
  );
}

stl::Style stl::Color::style_ansi256(ANSI fg, ANSI bg, Attribute attr) {
  return style(
    ColorValue::ansi256(fg),
    ColorValue::ansi256(bg),
    attr
  );
}

stl::Style stl::Color::style_ansi256(ANSI color, Attribute attr) {
  return style(
    ColorValue::ansi256(color),
    ColorValue::ansi256(color),
    attr
  );
}

stl::Style stl::Color::style_ansi16(ANSI fg, ANSI bg, Attribute attr) {
  return style(
    ColorValue::ansi16(fg),
    ColorValue::ansi16(bg),
    attr
  );
}

stl::Style stl::Color::style_ansi16(ANSI color, Attribute attr) {
  return style(
    ColorValue::ansi16(color),
    ColorValue::ansi16(color),
    attr
  );
}


std::string stl::Color::color_hex(const Hex fg, const Hex bg) {
  return "\033[38;2;"
    + std::to_string((fg >> 16) & 0xFF) + ";"
    + std::to_string((fg >> 8)  & 0xFF) + ";"
    + std::to_string( fg        & 0xFF) + ";48;2;"
    + std::to_string((bg >> 16) & 0xFF) + ";"
    + std::to_string((bg >> 8)  & 0xFF) + ";"
    + std::to_string( bg        & 0xFF) + "m";
}

std::string stl::Color::color_hex(const Hex color) {
  return "\033[38;2;"
    + std::to_string((color >> 16) & 0xFF) + ";"
    + std::to_string((color >> 8)  & 0xFF) + ";"
    + std::to_string( color        & 0xFF) + ";48;2;"
    + std::to_string((color >> 16) & 0xFF) + ";"
    + std::to_string((color >> 8)  & 0xFF) + ";"
    + std::to_string( color        & 0xFF) + "m";
}

std::string stl::Color::color_rgb(const RGB fg, const RGB bg) {
  return "\033[38;2;"
    + std::to_string(fg[0]) + ";"
    + std::to_string(fg[1]) + ";"
    + std::to_string(fg[2]) + ";48;2;"
    + std::to_string(bg[0]) + ";"
    + std::to_string(bg[1]) + ";"
    + std::to_string(bg[2]) + "m";
}

std::string stl::Color::color_rgb(const RGB color) {
  return "\033[38;2;"
    + std::to_string(color[0]) + ";"
    + std::to_string(color[1]) + ";"
    + std::to_string(color[2]) + ";48;2;"
    + std::to_string(color[0]) + ";"
    + std::to_string(color[1]) + ";"
    + std::to_string(color[2]) + "m";
}

std::string stl::Color::color_ansi256(const ANSI fg, const ANSI bg) {
  return 
    "\033[38;5;" + std::to_string(fg) +
    ";48;5;" + std::to_string(bg) + "m";
}

std::string stl::Color::color_ansi256(const ANSI color) {
  return 
    "\033[38;5;" + std::to_string(color) +
    ";48;5;" + std::to_string(color) + "m";
}

std::string stl::Color::color_ansi16(AnsiColor fg, AnsiColor bg, bool isBright) {
  std::string sequence = (isBright) ?
    color_bg(bg, true) + color_fg(fg, true) :
    color_bg(bg) + color_fg(fg);
  return sequence;
}

std::string stl::Color::color_ansi16(AnsiColor color, bool isBright) {
  std::string sequence = (isBright) ?
    color_bg(color, true) + color_fg(color, true) :
    color_bg(color) + color_fg(color);
  return sequence;
}


std::string stl::Color::color_fg(AnsiColor fg, bool isBright) {
  short value = static_cast<short>(fg);
  if (value > 7 || value < 0) return "\033[37m";
  std::string sequence = (isBright)
    ? "\033[1;3" + std::to_string(value) + "m"
    : "\033[3" + std::to_string(value) + "m";
  return sequence;
}

std::string stl::Color::color_bg(AnsiColor bg, bool isBright) {
  short value = static_cast<short>(bg);
  if (value > 7 || value < 0) return "\033[40m";
  std::string sequence = (isBright)
    ? "\033[10" + std::to_string(value) + "m"
    : "\033[4" + std::to_string(value) + "m";
  return sequence;
}


/* ====================================================== */
/*                  ANSI Class Functions                  */
/* ====================================================== */

std::string stl::Ansi::apply(Style &style) {
  std::string code;
  append_color(code, style.fg, true);
  code += ";";
  append_color(code, style.bg, false);
  return "\033[" + code + "m";
}

std::string stl::Ansi::reset() { return "\033[0m"; }

void stl::Ansi::append_color(std::string &result, const ColorValue &original, bool fg) {
  const int channel = fg ? 38 : 48;
  
  switch (original.format) {
    case ColorFormat::HEX:
    case ColorFormat::RGB:
      result += std::to_string(channel) + ";2;";
      result += std::to_string((original.value >> 16) & 0xFF) + ";";
      result += std::to_string((original.value >> 8) & 0xFF) + ";";
      result += std::to_string(original.value & 0xFF);
    break;
    case ColorFormat::ANSI16:
      // TODO: Finish this at some point
    break;
    case ColorFormat::ANSI256:
      result += std::to_string(channel) + ";5;";
      result += std::to_string(original.value);
    break;
  }
}
