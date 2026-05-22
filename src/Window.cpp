#include "Window.h"

Window WindowManager::CreateWin(int width, int height, int startX, int startY) {
  Cells cell{};
  Window win{};

  win.width = width += 2;
  win.height = height += 2;
  win.startX = startX;
  win.startY = startY;

  win.buffer.resize(height, std::vector<Cells>(width, cell)); // Initialize buffer with default cells

  return win;
}

void WindowManager::RefreshWin(Window& win) {
  for (short r = 0; r < win.height; ++r) {
    MoveCursor(win.startX + 1, win.startY + r + 1);
    for (short c = 0; c < win.width; ++c) {
      std::cout << win.buffer[r][c].ch;
    }
  }
}

void WindowManager::Border(Window& win, const BorderStyle& style) {
  // Window Corners
  win.buffer[0][0].ch = style.topLeft;
  win.buffer[0][win.width - 1].ch = style.topRight;
  win.buffer[win.height - 1][0].ch = style.bottomLeft;
  win.buffer[win.height - 1][win.width - 1].ch = style.bottomRight;

  // Draw top and bottom borders
  for (int i = 1; i < win.width - 1; ++i) {
    win.buffer[0][i].ch = style.top;
    win.buffer[win.height - 1][i].ch = style.bottom;
  }

  // Draw left and right borders
  for (int i = 1; i < win.height - 1; ++i) {
    win.buffer[i][0].ch = style.left;
    win.buffer[i][win.width - 1].ch = style.right;
  }

  RefreshWin(win);
}

void WindowManager::WPrintLn(Window& win, short x, short y, std::string text, ...) {
  // Bounds checking to prevent writing outside the window buffer
  if (y < 0 || y >= win.height) return;
  if (x < 0 || x >= win.width) return;

  for (size_t i = 0; i < text.size() && (x + i) < win.width - 1; ++i) {
    win.buffer[y][x + i].ch = text[i];
  }
}

void WindowManager::ClrScr() {
  // ANSI escape code to clear the screen and move cursor to top-left
  std::cout << "\033[2J\033[1;1H";
}

void WindowManager::MvClrScr(int x, int y) {
  // ANSI escape code to clear the screen and move cursor to (x, y)
  std::cout << "\033[2J\033[" << y << ";" << x << "H";
}

void WindowManager::MoveCursor(int x, int y) {
  // ANSI escape code to move cursor to (x, y)
  std::cout << "\033[" << y << ";" << x << "H";
}

void WindowManager::HideCursor() {
  // ANSI escape code to hide the cursor
  std::cout << "\033[?25l";
}

void WindowManager::ShowCursor() {
  // ANSI escape code to show the cursor
  std::cout << "\033[?25h";
}
