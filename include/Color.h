#pragma once
#include <iostream>
#include <string>

namespace stl {
  enum class BOLD_MODE {
    NONE = 0, BOTH = 1,
    FG = 90, BG = 100
  };
  enum class COLOR {
    BLACK   = 0, RED     = 1, GREEN   = 2,
    YELLOW  = 3, BLUE    = 4, MAGENTA = 5,
    CYAN    = 6, WHITE   = 7
  };
  enum class ColorMode {
    ANSI16,
    ANSI256,
    TRUECOLOR,
  };
  // TODO: Text attribute flags (e.g. bold, underline, reverse, blink, dim)
  enum class Flags {
    BOLD = 1 << 0,
    UNDERLINE = 1 << 1,
    REVERSE = 1 << 2,
    BLINK = 1 << 3,
    DIM = 1 << 4,
  };

  // Hexadecimal format (0xRRGGBB)
  struct Hex { uint32_t fg, bg; };
  // RGB format (Red, Green, Blue)
  struct RGB { uint8_t r, g, b; };
  // ANSI 256-color format (0-255 for foreground and background)
  struct ANSI256 { uint8_t value; };
  // ANSI 16-color format (0-7 for foreground, 40-47 for background)
  struct ASNI16 { uint8_t value; };
  // Style struct to hold color information and generate ANSI escape codes
  struct Style {
    uint16_t flags = 0;

    Style(uint32_t fg = 0xCCCCCC, uint32_t bg = 0x0C0C0C,
      ColorMode m = ColorMode::TRUECOLOR)
      : fg(fg), bg(bg), mode(m) {
    }

    std::string ansi() const { 
      if (mode == ColorMode::TRUECOLOR) {
        return 
          "\033[38;2;"
          + std::to_string((fg >> 16) & 0xFF) + ";"
          + std::to_string((fg >> 8)  & 0xFF) + ";"
          + std::to_string( fg        & 0xFF) + "m"
          + "\033[48;2;"
          + std::to_string((bg >> 16) & 0xFF) + ";"
          + std::to_string((bg >> 8)  & 0xFF) + ";"
          + std::to_string( bg        & 0xFF) + "m";
      }
      else if (mode == ColorMode::ANSI256) {
        return 
          "\033[38;5;" + std::to_string(fg) + "m"
          "\033[48;5;" + std::to_string(bg) + "m";
      }
      else {
        return
          "\033[" + std::to_string(fg) + "m"
          "\033[" + std::to_string(bg) + "m";
      }
    }

  private:
    ColorMode mode = ColorMode::TRUECOLOR;
    uint32_t fg = 0xCCCCCC;
    uint32_t bg = 0x0C0C0C;
  };

  /// <summary>
  /// Provides functionality for managing colors in the terminal
  /// </summary>
  class Color {
  public:
    Color() = default;

    /*     Direct Style Application     */
    // Hex color code
    Style style_hex(const Hex& style = { 0xCCCCCC, 0x0C0C0C }) const;
    // RGB color code
    Style style_rgb(const RGB& fg = { 204, 204, 204 }, const RGB& bg = { 12, 12, 12 }) const;
    // ANSI-256 color code (0-255 for foreground and background)
    Style style_ansi256(const ANSI256& fg, const ANSI256& bg) const;
    // ANSI-16 color codes
    Style style_ansi16(COLOR fg = COLOR::WHITE, COLOR bg = COLOR::BLACK, 
      BOLD_MODE mode = BOLD_MODE::NONE) const;
    /*   End Direct Style Application   */

    /* TODO: Color Pair Management */
    // Initialize color pairs
    //static void init_color_pair(short pair, short fg, short bg);
    //// Enable attribute pair
    //void enable_attr(short pair);
    //// Disable attribute pair
    //void disable_attr(short pair);
    /* End Color Pair Management */

    /*   Color Management   */
    // Set foreground and background using Hex format
    static std::string color(const Hex& hex = { 0xCCCCCC, 0x0C0C0C });
    // Set forground and background using RGB format
    static std::string color(const RGB& fg = { 204, 204, 204 }, const RGB& bg = { 12, 12, 12 });
    // Set both foreground and background colors (ANSI-256 color)
    static std::string color(const ANSI256& fg, const ANSI256& bg);
    // Set both foreground and background colors (ANSI-16 color)
    static std::string color(COLOR fg = COLOR::WHITE, COLOR bg = COLOR::BLACK, bool isBold = false);

    // Set text color, with optional bright varient (bold)
    static std::string color_fg(COLOR fg, bool isBold = false);
    // Set background color, with optional bright varient (bold)
    static std::string color_bg(COLOR bg, bool isBold = false);

    // Reset ALL color attributes
    static std::string color_reset();
    /* End Color Management */

  private:
    Style mStyle[256];
  };
}
