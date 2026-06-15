#pragma once
#include <vector>
#include <ostream>
#include "Cursor.h"
#include "Color.h"

namespace stl {
  // A cell in the window buffer
  struct Cell {
    char glyph = ' ';         // Character to display
    bool isDirty = true;      // Has cell changed since last refresh
    Style style;
  };
  // Border characters for the window
  struct WindowBorder {
    char left = '|';
    char right = '|';
    char top = '-';    // ─
    char bottom = '-'; // ─
    char topLeft = '+';
    char topRight = '+';
    char bottomLeft = '+';
    char bottomRight = '+';
  };
  // Window configuration
  struct WindowConfig {
    uint16_t startX = 0;
    uint16_t startY = 0;
    uint16_t width = 25;
    uint16_t height = 10;
    WindowBorder border;
    Style style;
  };
  // Current state of the window
  struct WindowState {
    // Buffer[][] is indexed as [row][column] or [y][x]
    std::vector<std::vector<Cell>> buffer;

    Cell& get_cell(short x, short y) {
      return buffer[y][x];
    }

    void update_glyph(short x, short y, char newGlyph) {
      Cell& cell = buffer[y][x];
      if (cell.glyph != newGlyph) {
        cell.glyph = newGlyph;
        cell.isDirty = true;
      }
    }

    void clean(short x, short y) {
      Cell& cell = buffer[y][x];
      cell.isDirty = false;
    }
  };

  /// <summary>
  /// Provides functionality for creating and managing windows in the terminal,
  /// including drawing borders, printing text, and refreshing the display.
  /// </summary>
  class Window {
  public:
    Window() = default;
    Window(const WindowConfig& config);

    // Draw a mBorder around the window
    void border();
    // Print random garbage in window for testing
    void print_random_garbage();
    // Print a string at (x, y)
    void print(short x, short y, const std::string& text);
    // Refresh the content of the window
    void refresh(std::ostream& os);

  private:
    WindowConfig mCfg;
    WindowState mState;

    uint16_t mOuterWidth;
    uint16_t mOuterHeight;
  };

  inline std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    os << cell.style.ansi() << cell.glyph;
    return os;
  }
}

