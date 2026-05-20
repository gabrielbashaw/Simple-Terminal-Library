#pragma once
#include <iostream>
#include <vector>

struct IWindow {
  short startX;
  short startY;
  short width;
  short height;

  std::vector<std::vector<char>> buffer; // 2D vector to hold the window buffer
};

class Window {
public:
  /* Window Management */
  // Create a new window with specified dimensions and position
  IWindow CreateWin(int width, int height, int startX, int startY);
  // Refresh the content of the window on the console
  // TODO: Optimize by only redrawing changed parts of the window
  void RefreshWin(IWindow& win);
  // Draw a border around the window using specified characters for sides and corners
  // l: left, r: right, t: top, b: bottom
  // tl: top-left corner, tr: top-right corner, bl: bottom-left corner, br: bottom-right corner
  void Border(IWindow& win, char l, char r, char t, char b, char tl, char tr, char bl, char br);
  // Print a string at (x, y) within the window's buffer
  // TODO: Fix: Text overlaps borders if (x, y) is too close to edges. Add bounds checking and clipping.
  void WPrintLn(IWindow& win, short x, short y, std::string text);
  /* End Window Management */

  /* Terminal Manipulation */
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
  /* End Terminal Manipulation */

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
  // Reset text and background colors to default
  void ResetColors();
  /* End Color Management*/
};
