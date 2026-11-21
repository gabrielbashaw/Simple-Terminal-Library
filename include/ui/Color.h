#pragma once
#include <array>
#include <string>
#include "core/types.h"

namespace stl {
  using ANSI = u8;
  using Hex = u32;
  using RGB = std::array<u8, 3>;
  
  enum class Attribute : u8 {
    NONE      = 0,       // No text attributes applied
    BOLD      = 1 << 0,  // Bold or increased text intensity
    DIM       = 1 << 1,  // Dimmed or reduced text intensity
    ITALIC    = 1 << 2,  // Italic text
    UNDERLINE = 1 << 3,  // Underlined text
    BLINK     = 1 << 4,  // Blinking text
    REVERSE   = 1 << 5,  // Swap foreground and background colors
    HIDDEN    = 1 << 6,  // Hidden or invisible text
    STRIKE    = 1 << 7   // Strikethrough text
  };
  enum class ColorFormat : u8 {
    HEX,
    RGB,
    ANSI16,
    ANSI256
  };
  enum class ANSI16 : u8 {
    BLACK   = 0, RED     = 1, GREEN   = 2,
    YELLOW  = 3, BLUE    = 4, MAGENTA = 5,
    CYAN    = 6, WHITE   = 7
  };
  
  struct ColorValue {
    ColorFormat format;
    uint32_t value;

    static constexpr ColorValue hex(uint32_t value) {
      return { ColorFormat::HEX, value };
    }
    static constexpr ColorValue rgb(u8 r, u8 g, u8 b) {
      return { ColorFormat::RGB,
        (static_cast<u32>(r) << 16) |
        (static_cast<u32>(g) << 8) |
        static_cast<u32>(b)
      };
    }
    static constexpr ColorValue ansi16(ANSI16 value) {
      return { ColorFormat::ANSI16, static_cast<u8>(value) };
    }
    static constexpr ColorValue ansi256(uint8_t value) {
      return { ColorFormat::ANSI256, value };
    }
  };
  struct Style {
    ColorValue fg;
    ColorValue bg;
    Attribute attr;
  };

  /// <summary>
  /// Provides functionality for managing colors in the terminal
  /// </summary>
  class Color {
  public:
    Color() = default;
    
    static Style style(ColorValue fg, ColorValue bg, Attribute attr = Attribute::NONE);
    // Set color style using Hex color codes
    static Style style_hex(Hex fg, Hex bg, Attribute attr = Attribute::NONE);
    // Set a solid color style using Hex color codes
    static Style style_hex(Hex color, Attribute attr = Attribute::NONE);
    // Set style using RGB color codes
    static Style style_rgb(RGB fg, RGB bg, Attribute attr = Attribute::NONE);
    // Set a solid color style using RGB color codes
    static Style style_rgb(RGB color, Attribute attr = Attribute::NONE);
    // Set style using ANSI-256 colors
    static Style style_ansi256(ANSI fg, ANSI bg, Attribute attr = Attribute::NONE);
    // Set a solid color style using ANSI-256 colors
    static Style style_ansi256(ANSI color, Attribute attr = Attribute::NONE);
    // Set style using ANSI-16 colors
    static Style style_ansi16(ANSI16 fg, ANSI16 bg, Attribute attr = Attribute::NONE);
    // Set a solid color style using ANSI-16 colors
    static Style style_ansi16(ANSI16 color, Attribute attr = Attribute::NONE);

    // Set foreground and background using Hex format
    static std::string color_hex(const Hex fg, const Hex bg);
    // Set a solid color using Hex format
    static std::string color_hex(const Hex color);
    // Set foreground and background using RGB format
    static std::string color_rgb(const RGB fg, const RGB bg);
    // Set a solid color using RGB format
    static std::string color_rgb(const RGB color);
    // Set foreground and background colors (ANSI-256 color)
    static std::string color_ansi256(const ANSI fg, const ANSI bg);
    // Set a solid color using ANSI256 colors
    static std::string color_ansi256(const ANSI color);
    // Set foreground and background colors (ANSI-16 color)
    static std::string color_ansi16(ANSI16 fg, ANSI16 bg, bool isBright = false);
    // Set a solid color using ANSI16 colors
    static std::string color_ansi16(ANSI16 color, bool isBright = false);

    // Set text color, with optional bright varient (bold)
    static std::string color_fg(ANSI16 fg, bool isBright = false);
    // Set background color, with optional bright varient (bold)
    static std::string color_bg(ANSI16 bg, bool isBright = false);
  };
  
  class Ansi {
  public:
    // Apply color style
    static std::string apply(Style &style);
    // Reset ALL color attributes
    static std::string reset();
  
  private:
    static void append_color(std::string& result, const ColorValue& original, bool fg);
    static void append_attr(std::string& result, const Attribute& attr);
  };

  inline constexpr Attribute operator|(Attribute a, Attribute b) {
    return static_cast<Attribute>(
      static_cast<u8>(a) | static_cast<u8>(b)
    );
  }
  inline constexpr Attribute operator&(Attribute a, Attribute b) {
    return static_cast<Attribute>(
      static_cast<u8>(a) & static_cast<u8>(b)
    );
  }
  inline constexpr Attribute operator~(Attribute a){
    return static_cast<Attribute>(static_cast<u8>(~a));
  }

  inline constexpr Attribute operator|=(Attribute& a, Attribute& b) {
    return a = a | b;
  }
  inline constexpr Attribute operator&=(Attribute& a, Attribute& b) {
    return a = a & b;
  }

  bool has_attr(const Attribute& attr, Attribute flag);
}
