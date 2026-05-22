#pragma once
#include <iostream>
#include <vector>

// A cell in the window buffer
struct Cells {
  // short r, c;        // Row and column position in the window
  char ch = ' ';        // Character to display in the cell
  short colorPair = -1; // -1 means no color pair applied
};
// A window in the terminal
// Buffer[][] is indexed as [row][column] or [y][x]
struct Window {
  short startX = 0;
  short startY = 0;
  short width = 0;
  short height = 0;

  std::vector<std::vector<Cells>> buffer;
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
  Window CreateWin(int width, int height, int startX, int startY);
  // Refresh the content of the window on the console
  // TODO: Optimize by only redrawing changed parts of the window
  void RefreshWin(Window& win);
  // Draw a border around the window using specified characters for sides and corners
  void Border(Window& win, const BorderStyle& style = {});
  // Print a string at (x, y) within the window's buffer
  // TODO: Fix: Add bounds checking and clipping.
  void WPrintLn(Window& win, short x, short y, std::string text, ...);
  /* End Window Management */
  
  /* Screen Manipulation */
  // Clear the screen and move cursor to top-left
  void ClrScr();
  // Clear the screen and move cursor to (x, y)
  void MvClrScr(int x, int y);
  // Move the cursor to (x, y)
  void MoveCursor(int x, int y);
  // Hide the cursor
  void HideCursor();
  // Show the cursor
  void ShowCursor();
  /* End Screen Manipulation */
};
