#pragma once
#include <iostream>
#include <format>
#include <regex>
#include <variant>

enum class DefaultColors {
  COLOR_BLACK,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_YELLOW,
  COLOR_BLUE,
  COLOR_MAGENTA,
  COLOR_CYAN,
  COLOR_WHITE
};

struct Default {};
struct Indexed { short index; };
struct RGB { uint8_t r, g, b; };
using ColorType = std::variant<Default, RGB, Indexed>;

// Represent a color pair (foreground and background)
struct ColorPair {
  short pairNumber; // Pair number (0-255)
  ColorType fg;     // Foreground color
  ColorType bg;     // Background color
};

// Represent a color in hexadecimal format (0xRRGGBB)
struct HexColor {
  uint32_t fg = 0xFFFFFF;
  uint32_t bg = 0x000000;
};
struct Style {
  uint32_t fgStyle;
  uint32_t bgStyle;
  uint16_t flags;
};

/// <summary>
/// Provides functionality for managing colors in the terminal, 
/// including defining color pairs and applying them to text.
/// </summary>
class Color {
public:
  Color();
  Color(uint32_t fg = 0xCCCCCC, uint32_t bg = 0x0C0C0C);
  Color(RGB fg, RGB bg);
  /*   New Color Functions   */
  // Optionally set foreground and background colors (e.g. fg = 0xCCCCCC, bg = 0x0C0C0C)
  static Style ColorHex(uint32_t fg = 0xCCCCCC, uint32_t bg = 0x0C0C0C);
  // Optionally set foreground and background colors (e.g. fg = {255, 255, 255}, bg = {0, 0, 0})
  static Style ColorRGB(RGB fg, RGB bg);
  // Optionally set foreground and background colors (e.g. fg = {255, 255, 255}, bg = {0, 0, 0})
  //static Style Color(uint8_t fg, uint8_t bg);
  /* End New Color Functions */

  /* Color Pair Management */
  // Initialize color pairs
  static void InitColorPair(short pair, short fg, short bg);
  // Set RGB color (0-255 for each component)
  static void InitColorPairRGB(short pair, RGB fg, RGB bg);
  // Enable attribute pair
  static void EnableAttribute(short pair);
  // Disable attribute pair
  static void DisableAttribute(short pair);
  /* End Color Pair Management */

  /* Color Management */
  // Set both foreground and background colors
  // 0: Black, 1: Red, 2: Green, 3: Yellow, 4: Blue, 5: Magenta, 6: Cyan, 7: White
  void SetColor(short fg, short bg);
  // Set text color (0-7)
  // 0: Black, 1: Red, 2: Green, 3: Yellow, 4: Blue, 5: Magenta, 6: Cyan, 7: White
  void SetForegroundColor(short fg);
  // Set background color (0-7)
  // 0: Black, 1: Red, 2: Green, 3: Yellow, 4: Blue, 5: Magenta, 6: Cyan, 7: White
  void SetBackgroundColor(short bg);
  /* End Color Management*/

private:
  static ColorPair _color_pairs[256]; // Store up to 256 color pairs (fg, bg)
};
