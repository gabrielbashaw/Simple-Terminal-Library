#pragma once
//#include <iostream>
#include <vector>
#include "Color.h"
#include "Cursor.h"

// A cell in the window frontBuffer
struct Cell {
  char glyph = ' ';         // Character to display in the cell
  uint32_t fg = 0xFFFFFF;
  uint32_t bg = 0x0000FF;
  bool isDirty = true;  // Has cell changed since last refresh
};
// A window in the terminal
// Buffer[][] is indexed as [row][column] or [y][x]
struct Window {
  short startX = 0;
  short startY = 0;
  short width = 0;
  short height = 0;

  std::vector<std::vector<Cell>> frontBuffer;     // Current state of the windows content
  std::vector<std::vector<Cell>> backBuffer;      // Desired state of window content after refresh

  void UpdateGlyph(Cell& cell, char newGlyph) {
    if (cell.glyph != newGlyph) {
      cell.glyph = newGlyph;
      cell.isDirty = true;
    }
  }

  void Clean(Cell& cell) { cell.isDirty = false; }
};
// Border characters for the window
struct BorderStyle {
  char left = '|';
  char right = '|';
  char top = '-';    // ─
  char bottom = '-'; // ─
  char topLeft = '+';
  char topRight = '+';
  char bottomLeft = '+';
  char bottomRight = '+';
};

/// <summary>
/// Provides functionality for creating and managing windows in the terminal, 
/// including drawing borders, printing text, and refreshing the display. 
/// It also includes methods for manipulating the console screen and cursor.
/// </summary>
class WindowManager {
public:
  /* Window Management */
  // Create a new window with specified dimensions and position
  static Window CreateWin(int width, int height, int startX = 0, int startY = 0);
  // Refresh the content of the window on the console
  void RefreshWin(Window& win);
  // Draw a border around the window using specified characters for sides and corners
  void Border(Window& win, const BorderStyle& style = {});
  // Print a string at (x, y)
  void WPrint(Window& win, short x, short y, std::string text);
  // Print random garbage in window for testing
  void WPrintRandomGarbage(Window& win);
  /* End Window Management */
  
  /* Screen Manipulation */
  // Clear the screen and move cursor to top-left
  void ClrScr();
  // Clear the screen and move cursor to (x, y)
  void MvClrScr(int x, int y);
  /* End Screen Manipulation */

private:
  // Draw the window content to the console
  void Draw(std::ostream& os, Window& win);
};

inline std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  os << cell.glyph;
  return os;
}
