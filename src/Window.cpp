#include "Window.h"

stl::Window::Window(const WindowConfig& config) : mCfg(config) {
  if ((mCfg.width < 1) || (mCfg.height < 1)) {
    mCfg.width = 25;
    mCfg.height = 10;
  }

  mOuterWidth = mCfg.width + 2;
  mOuterHeight = mCfg.height + 2;

  // Initialize buffer with cells from cfg
  mState.buffer.resize(mOuterHeight);
  for (auto& row : mState.buffer) {
    row.resize(mOuterWidth);
    for (auto& cell : row) {
      cell.glyph = ' ';
      cell.isDirty = true;
    }
  }
}

void stl::Window::border(){
  short x = mOuterWidth - 1;
  short y = mOuterHeight - 1;
  WindowBorder border = mCfg.border;

  // Window Corners
  mState.update_glyph(0, 0, border.topLeft);
  mState.update_glyph(x, 0, border.topRight);
  mState.update_glyph(0, y, border.bottomLeft);
  mState.update_glyph(x, y, border.bottomRight);

  // Draw top and bottom borders
  for (short i = 1; i < x; ++i) {
    mState.update_glyph(i, 0, border.top);
    mState.update_glyph(i, y, border.bottom);
  }

  // Draw left and right borders
  for (short i = 1; i < y; ++i) {
    mState.update_glyph(0, i, border.left);
    mState.update_glyph(x, i, border.right);
  }
}

void stl::Window::print_random_garbage() {
  short x = mOuterWidth;
  short y = mOuterHeight;
  for (short r = 0; r < y - 1; r++) {
    for (short c = 0; c < x - 1; c++) {
      char randChar = ' ' + (rand() % 95); // Random ASCII char
      mState.update_glyph(c, r, randChar);
    }
  }
}

void stl::Window::print(short x, short y, const std::string& text) {
  //TODO: Replace with an error msg
  // Bounds checking to prevent writing outside the window buffer
  if (y <= 0 || y >= mOuterHeight) return;
  if (x <= 0 || x >= mOuterWidth) return;

  for (short i = 0; i < text.size() && (x + i) < mOuterWidth - 1; ++i) {
    mState.update_glyph(x + i, y, text[i]);
  }
}

void stl::Window::refresh(std::ostream& os) {
  short cX, cY;
  short x = mOuterWidth;
  short y = mOuterHeight;

  for (short r = 0; r < y; r++) {
    bool cursorMoved = false;
    for (short c = 0; c < x; c++) {
      if (!mState.get_cell(c, r).isDirty) {
        cursorMoved = false;
        continue;
      }

      if (!cursorMoved) {
        cX = mCfg.startX + c + 1;
        cY = mCfg.startY + r + 1;
        os << stl::cursor_move(cX, cY);
        cursorMoved = true;
      }

      // Style interior and exterior separately
      if ((c == 0 || c == x - 1) || (r == 0 || r == y - 1))
        os << mCfg.styleBorder.ansi() << mState.get_cell(c, r);
      else
        os << mCfg.styleBody.ansi() << mState.get_cell(c, r);

      mState.clean(c, r);
    }
  }
}
