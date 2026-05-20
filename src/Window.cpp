#include "Window.h"

IWindow Window::CreateWin(int width, int height, int startX, int startY) {
  IWindow win{};
  win.width = width;
  win.height = height;
  win.startX = startX;
  win.startY = startY;

  win.buffer.resize(height, std::vector<char>(width, ' ')); // Initialize content with spaces

  return win;
}

void Window::RefreshWin(IWindow& win) {
  for (int i = 0; i < win.height; ++i) {
    MoveCursor(win.startX, win.startY + i);
    for (int j = 0; j < win.width; ++j) {
      std::cout << win.buffer[i][j];
    }
  }
}

void Window::Border(IWindow& win, char l, char r, char t, char b, char tl, char tr, char bl, char br) {
  // Draw top and bottom borders
  for (int i = 0; i < win.width; ++i) {
    win.buffer[0][i] = t; // Top border
    win.buffer[win.height - 1][i] = b; // Bottom border
  }

  // Draw left and right borders
  for (int i = 0; i < win.height; ++i) {
    win.buffer[i][0] = l; // Left border
    win.buffer[i][win.width - 1] = r; // Right border
  }

  // Window Corners
  win.buffer[0][0] = tl; // Top-left corner
  win.buffer[0][win.width - 1] = tr; // Top-right corner
  win.buffer[win.height - 1][0] = bl; // Bottom-left corner
  win.buffer[win.height - 1][win.width - 1] = br; // Bottom-right corner
}

void Window::WPrintLn(IWindow& win, short x, short y, std::string text) {
  if (y < 0 || y >= win.height) return; // Out of vertical bounds
  if (x < 0 || x >= win.width) return; // Out of horizontal bounds
  for (size_t i = 0; i < text.size() && (x + i) < win.width; ++i) {
    win.buffer[y][x + i] = text[i];
  }
}

void Window::ClrScr() {
  // ANSI escape code to clear the screen and move cursor to top-left
  std::cout << "\033[2J\033[1;1H";
}

void Window::MvClrScr(int x, int y) {
  // ANSI escape code to clear the screen and move cursor to (x, y)
  std::cout << "\033[2J\033[" << y << ";" << x << "H";
}

void Window::MoveCursor(int x, int y) {
  // ANSI escape code to move cursor to (x, y)
  std::cout << "\033[" << y << ";" << x << "H";
}

void Window::HideCursor() {
  // ANSI escape code to hide the cursor
  std::cout << "\033[?25l";
}

void Window::ShowCursor() {
  // ANSI escape code to show the cursor
  std::cout << "\033[?25h";
}
