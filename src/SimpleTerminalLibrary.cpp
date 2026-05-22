#include <stdio.h>
#include "Console.h"
#include "Color.h"
#include "Window.h"

char GetKey() {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  INPUT_RECORD input{};
  DWORD numRead;

  // Read 1 input event
  if (!ReadConsoleInput(hStdin, &input, 1, &numRead)) {
    printf("ReadConsoleInput failed (error: %lu)\n", GetLastError());
    return 0;
  }

  if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
    char c = input.Event.KeyEvent.uChar.AsciiChar;
    if (GetKeyState(VK_MENU) & 0x8000) return 0; // Ignore ALT+key combinations
    if (GetKeyState(VK_CONTROL) & 0x8000) return 0; // Ignore CTRL+key combinations
    printf("Captured: '%c' (ASCII: %d)\n", c, c);
    return c;
  }
}

void WindowBuilder(short winNum, short width, short height, short x, short y) {
  WindowManager term;
  Window win;

  win = term.CreateWin(width, height, x, y);
  term.Border(win);
  term.WPrintLn(win, 19, 2, "Hello, Window " + std::to_string(winNum).append("!"));
  term.RefreshWin(win);
}

void InitColor() {
  for (short fg = 0; fg < 8; ++fg) {
    for (short bg = 0; bg < 8; ++bg) {
      short pairNumber = fg * 8 + bg + 1; // Pair numbers start from 1
      Color::InitColorPair(pairNumber, fg, bg);
    }
  }

  // Custom RGB color pair (white on black)
  Color::InitColorPairRGB(65, RGB{ 255, 255, 255 }, RGB{ 0, 0, 0 });
}

int main() {
  WindowManager term;
  Window win;

  InitColor();
  term.ClrScr();
  term.HideCursor();
  
  while (true) {
    term.MoveCursor(10, 25);

    wchar_t ch = GetKey();
    if (ch == 27) break; // Exit on ESC key

    if (ch == 49) {
      Color::EnableAttribute(9);
      WindowBuilder(1, 30, 10, 5, 5);
      Color::DisableAttribute(9);
    }
    if (ch == 50) {
      Color::EnableAttribute(46);
      WindowBuilder(2, 30, 10, 40, 5);
      Color::DisableAttribute(46);
    }
    if (ch == 51) {
      Color::EnableAttribute(65);
      WindowBuilder(3, 30, 10, 75, 5);
      Color::DisableAttribute(65);
    }
  }
}
