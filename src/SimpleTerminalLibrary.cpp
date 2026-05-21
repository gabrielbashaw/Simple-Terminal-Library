#include <stdio.h>
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

int main() {
  Window term;
  term.HideCursor();

  // Initialize color pairs
  Color::InitColorPair(1, COLOR_WHITE, COLOR_BLUE);
  Color::InitColorPair(2, COLOR_BLACK, COLOR_YELLOW);
  Color::InitColorPairRGB(3, RGB{ 255, 0, 255 }, RGB{ 0, 255, 255 }); // Magenta on Cyan

  // Create a window and draw a border around it
  IWindow win;
  win = term.CreateWin(40, 25, 0, 1);
  term.Border(win, '|', '|', '-', '-', '+', '+', '+', '+');
  // Create a second window to demonstrate multiple windows
  IWindow win2;
  win2 = term.CreateWin(30, 10, 41, 1);
  term.Border(win2, '|', '|', '-', '-', '+', '+', '+', '+');
  // Create a third window to demonstrate multiple windows
  IWindow win3;
  win3 = term.CreateWin(20, 5, 60, 20);
  term.Border(win3, '|', '|', '-', '-', '+', '+', '+', '+');

  while (true) {
    term.MoveCursor(10, 25);

    term.WPrintLn(win, 2, 2, "Hello, Window 1!");
    term.WPrintLn(win2, 19, 2, "Hello, Window 2!");

    wchar_t ch = GetKey();
    if (ch == 27) break; // Exit on ESC key

    if (ch == 49) {
      Color::EnableAttribute(1); // Enable color pair 1 (white on blue)
      term.RefreshWin(win); // Refresh window on '1' key
      Color::DisableAttribute(1); // Disable color pair 1
      
      Color::EnableAttribute(2); // Enable color pair 2 (black on yellow)
      term.RefreshWin(win2); // Refresh window on '1' key
      Color::DisableAttribute(2); // Disable color pair 2

      Color::EnableAttribute(3); // Enable custom RGB color pair 3 (magenta)
      term.RefreshWin(win3); // Refresh window on '1' key
      Color::DisableAttribute(3); // Disable custom RGB color pair 3
    }
  }
}
