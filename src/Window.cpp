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
  win.frontBuffer[0][0].UpdateGlyph(glyph.topLeft);
  win.frontBuffer[0][win.width - 1].UpdateGlyph(glyph.topRight);
  win.frontBuffer[win.height - 1][0].UpdateGlyph(glyph.bottomLeft);
  win.frontBuffer[win.height - 1][win.width - 1].UpdateGlyph(glyph.bottomRight);

  // Draw top and bottom borders
  for (int i = 1; i < win.width - 1; ++i) {
    win.frontBuffer[0][i].UpdateGlyph(glyph.top);
    win.frontBuffer[win.height - 1][i].UpdateGlyph(glyph.bottom);
  }

  // Draw left and right borders
  for (int i = 1; i < win.height - 1; ++i) {
    win.frontBuffer[i][0].UpdateGlyph(glyph.left);
    win.frontBuffer[i][win.width - 1].UpdateGlyph(glyph.right);
  }
}

void WindowManager::WPrint(Window& win, short x, short y, std::string text) {
  //TODO: Replace with an error msg
  // Bounds checking to prevent writing outside the window frontBuffer
  if (y <= 0 || y >= win.height) return;
  if (x <= 0 || x >= win.width) return;
  
  for (size_t i = 0; i < text.size() && (x + i) < win.width - 1; ++i) {
    Cell& cell = win.frontBuffer[y][x + i];
    MoveCursor(x + i, y + 1);
    cell.UpdateGlyph(text[i]);
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
        os << "\033[" << y << ";" << x << "H";
        cursorMoved = true;
      }
      
      os << cell;
      cell.Clean();
    }
  }
}
