#include "Color.h"

ColorPair Color::_color_pairs[256];
void Color::InitColorPair(short pair, short fg, short bg) {
  if (pair < 0 || pair >= 256) return; // Out of range
  if (fg < 0 || fg > 7) fg = 7; // Default to white if out of range
  if (bg < 0 || bg > 7) bg = 0; // Default to black if out of range

  _color_pairs[pair].pairNumber = pair;
  _color_pairs[pair].fg = Indexed{ fg };
  _color_pairs[pair].bg = Indexed{ bg };
}

void Color::InitColorPairRGB(short pair, RGB fg, RGB bg) {
  if (pair < 0 || pair >= 256) return; // Out of range
  

  _color_pairs[pair].pairNumber = pair;
  _color_pairs[pair].fg = RGB{ fg };
  _color_pairs[pair].bg = RGB{ bg };
}

void Color::EnableAttribute(short pair) {
  const auto& fg = _color_pairs[pair].fg;
  const auto& bg = _color_pairs[pair].bg;

  // Forground color
  std::visit([](auto&& color) {
    using T = std::decay_t<decltype(color)>;

    if constexpr (std::is_same_v<T, Indexed>) {
      std::cout << "\033[" << (30 + color.index) << "m";
    }
    else if constexpr (std::is_same_v<T, RGB>) {
      std::cout << "\033[38;2;"
        << static_cast<short>(color.r) << ";"
        << static_cast<short>(color.g) << ";"
        << static_cast<short>(color.b) << "m";
    }
    else if constexpr (std::is_same_v<T, Default>) {
      std::cout << "\033[39m";
    }
  }, fg);

  // Background color
  std::visit([](auto&& color) {
    using T = std::decay_t<decltype(color)>;
    if constexpr (std::is_same_v<T, Indexed>) {
      std::cout << "\033[" << (40 + color.index) << "m";
    }
    else if constexpr (std::is_same_v<T, RGB>) {
      std::cout << "\033[48;2;"
        << static_cast<short>(color.r) << ";"
        << static_cast<short>(color.g) << ";"
        << static_cast<short>(color.b) << "m";
    }
    else if constexpr (std::is_same_v<T, Default>) {
      std::cout << "\033[39m";
    }
  }, bg);
}

void Color::DisableAttribute(short pair) {
  // Reset all attributes
  std::cout << "\033[0m";
}

void Color::SetColor(short fg, short bg) {
  SetForegroundColor(fg);
  SetBackgroundColor(bg);
}

void Color::SetForegroundColor(short fg) {
  // Default to white if out of range
  if (fg < 0 || fg > 7) fg = 7;

  // ANSI escape code to set text color (30-37 for foreground)
  std::cout << "\033[" << (30 + fg) << "m";
}

void Color::SetBackgroundColor(short bg) {
  // Default to black if out of range
  if (bg < 0 || bg > 7) bg = 0;

  // ANSI escape code to set background color (40-47 for background)
  std::cout << "\033[" << (40 + bg) << "m";
}
