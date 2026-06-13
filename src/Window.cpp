#include "Window.h"

stl::Window::Window(const WindowConfig& config) : mCfg(config) {
  if ((mCfg.width < 1) || (mCfg.height < 1)) {
    mCfg.width = 25;
    mCfg.height = 10;
  }

  mOuterWidth = mCfg.width + 2;
  mOuterHeight = mCfg.height + 2;

  // Initialize buffer with default cells
  mState.buffer.resize(mOuterHeight, std::vector<Cell>(mOuterWidth));
}

const void stl::Window::border() {
  short x = mOuterWidth;
  short y = mOuterHeight;
  WindowBorder border = mCfg.border;

  // Window Corners
  mState.UpdateGlyph(0, 0, border.topLeft);
  mState.UpdateGlyph(x - 1, 0, border.topRight);
  mState.UpdateGlyph(0, y - 1, border.bottomLeft);
  mState.UpdateGlyph(x - 1, y - 1, border.bottomRight);

  // Draw top and bottom borders
  for (short i = 1; i < x - 1; ++i) {
    mState.UpdateGlyph(i, 0, border.top);
    mState.UpdateGlyph(i, y - 1, border.bottom);
  }

  // Draw left and right borders
  for (short i = 1; i < y - 1; ++i) {
    mState.UpdateGlyph(0, i, border.left);
    mState.UpdateGlyph(x - 1, i, border.right);
  }
}

const void stl::Window::print_random_garbage() {
  short x = mOuterWidth;
  short y = mOuterHeight;
  for (short r = 1; r < y - 1; r++) {
    for (short c = 1; c < x - 1; c++) {
      char randChar = ' ' + (rand() % 95); // Random ASCII char
      mState.UpdateGlyph(c, r, randChar);
    }
  }
}

const void stl::Window::print(short x, short y, std::string text) {
  //TODO: Replace with an error msg
  // Bounds checking to prevent writing outside the window buffer
  if (y <= 0 || y >= mOuterHeight) return;
  if (x <= 0 || x >= mOuterWidth) return;

  for (short i = 0; i < text.size() && (x + i) < mOuterWidth - 1; ++i) {
    mState.UpdateGlyph(x + i, y, text[i]);
  }
}

const void stl::Window::refresh(std::ostream& os) {
  short cX, cY;
  short x = mOuterWidth;
  short y = mOuterHeight;
  for (short r = 0; r < y; r++) {
    bool cursorMoved = false;
    for (short c = 0; c < x; c++) {
      if (!mState.GetCell(c, r).isDirty) {
        cursorMoved = false;
        continue;
      }

      if (!cursorMoved) {
        cX = mCfg.startX + c + 1;
        cY = mCfg.startY + r + 1;
        os << stl::cursor_move(cX, cY);
        cursorMoved = true;
      }

      os << mState.GetCell(c, r);
      mState.Clean(c, r);
    }
  }
}
