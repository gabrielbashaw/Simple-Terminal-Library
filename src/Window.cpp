#include "Window.h"

Window WindowManager::CreateWin(int width, int height, int startX, int startY) {
  Cell cell{};
  Window win{};

  if (startX < 0) startX = 0;
  if (startY < 0) startY = 0;

  win.width = width += 2;
  win.height = height += 2;
  win.startX = startX;
  win.startY = startY;

  win.frontBuffer.resize(height, std::vector<Cell>(width, cell)); // Initialize frontBuffer with default cells
  win.backBuffer = win.frontBuffer; // Init backBuffer to match frontBuffer

  return win;
}

void WindowManager::RefreshWin(Window& win) {
  Draw(std::cout, win);
}

void WindowManager::Border(Window& win, const BorderStyle& glyph) {
  // Window Corners
  win.UpdateGlyph(win.frontBuffer[0][0], glyph.topLeft);
  win.UpdateGlyph(win.frontBuffer[0][win.width - 1], glyph.topRight);
  win.UpdateGlyph(win.frontBuffer[win.height - 1][0], glyph.bottomLeft);
  win.UpdateGlyph(win.frontBuffer[win.height - 1][win.width - 1], glyph.bottomRight);

  // Draw top and bottom borders
  for (int i = 1; i < win.width - 1; ++i) {
    win.UpdateGlyph(win.frontBuffer[0][i], glyph.top);
    win.UpdateGlyph(win.frontBuffer[win.height - 1][i], glyph.bottom);
  }

  // Draw left and right borders
  for (int i = 1; i < win.height - 1; ++i) {
    win.UpdateGlyph(win.frontBuffer[i][0], glyph.left);
    win.UpdateGlyph(win.frontBuffer[i][win.width - 1], glyph.right);
  }
}

void WindowManager::WPrint(Window& win, short x, short y, std::string text) {
  //TODO: Replace with an error msg
  // Bounds checking to prevent writing outside the window frontBuffer
  if (y <= 0 || y >= win.height) return;
  if (x <= 0 || x >= win.width) return;
  
  for (size_t i = 0; i < text.size() && (x + i) < win.width - 1; ++i) {
    Cell& cell = win.frontBuffer[y][x + i];
    STL::cursor_move(x + i, y + 1);
    win.UpdateGlyph(cell, text[i]);
  }
}

void WindowManager::WPrintRandomGarbage(Window& win) {
  for (size_t r = 1; r < win.height - 1; r++) {
    for (size_t c = 1; c < win.width - 1; c++) {
      Cell& cell = win.frontBuffer[r][c];
      char randChar = ' ' + (rand() % 95); // Random ASCII char
      win.UpdateGlyph(cell, randChar);
    }
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

void WindowManager::Draw(std::ostream& os, Window& win) {
  short x, y;
  for (size_t r = 0; r < win.height; r++) {
    bool cursorMoved = false;
    for (size_t c = 0; c < win.width; c++) {
      Cell& cell = win.frontBuffer[r][c];
      
      if (!cell.isDirty) {
        cursorMoved = false;
        continue;
      }
      
      if (!cursorMoved) {
        x = win.startX + c + 1;
        y = win.startY + r + 1;
        os << STL::cursor_move(x, y);
        cursorMoved = true;
      }

      os << cell;
      win.Clean(cell);
    }
  }
}
