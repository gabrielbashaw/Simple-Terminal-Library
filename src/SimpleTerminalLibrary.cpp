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

  // Create a window and draw a border around it
  IWindow win;
  term.SetBackgroundColor(4); // Set background color to blue
  win = term.CreateWin(40, 10, 5, 5);
  term.Border(win, '|', '|', '-', '-', '+', '+', '+', '+');
  term.RefreshWin(win);
  term.ResetColors();

  // Create a second window to demonstrate multiple windows
  IWindow win2;
  term.SetBackgroundColor(2); // Set background color to green
  win2 = term.CreateWin(30, 10, 50, 5);
  term.Border(win2, '|', '|', '-', '-', '+', '+', '+', '+');
  term.RefreshWin(win2);
  term.ResetColors();

  while (true) {
    term.MoveCursor(10, 20);

    term.WPrintLn(win, 2, 2, "Hello, Window 1!");
    term.WPrintLn(win2, 19, 2, "Hello, Window 2!");

    wchar_t ch = GetKey();
    if (ch == 27) break; // Exit on ESC key
    if (ch == 49) {
      term.RefreshWin(win); // Refresh window on '1' key
      term.RefreshWin(win2); // Refresh window on '1' key
    }
  }
}
