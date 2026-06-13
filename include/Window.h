#pragma once
#include <vector>
#include <ostream>
#include "Cursor.h"

namespace stl {
  // A cell in the window buffer
  struct Cell {
    char glyph = ' ';         // Character to display
    bool isDirty = true;      // Has cell changed since last refresh
    uint32_t fg = 0xFFFFFF;
    uint32_t bg = 0x0000FF;
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
  };
  // Current state of the window
  // Buffer[][] is indexed as [row][column] or [y][x]
  struct WindowState {
    std::vector<std::vector<Cell>> buffer;

    const Cell& GetCell(short x, short y) {
      return buffer[y][x];
    }

    void UpdateGlyph(short x, short y, char newGlyph) {
      Cell& cell = buffer[y][x];
      if (cell.glyph != newGlyph) {
        cell.glyph = newGlyph;
        cell.isDirty = true;
      }
    }

    void Clean(short x, short y) {
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
    const void border();
    // Print random garbage in window for testing
    const void print_random_garbage();
    // Print a string at (x, y)
    const void print(short x, short y, std::string text);
    // Refresh the content of the window
    const void refresh(std::ostream& os);

  private:
    WindowConfig mCfg;
    WindowState mState;

    uint16_t mOuterWidth;
    uint16_t mOuterHeight;
  };

  inline std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    os << cell.glyph;
    return os;
  }
}

