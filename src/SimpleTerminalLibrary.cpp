#include <stdio.h>
#include "Window.h"

int main() {
  Window term;
  term.HideCursor();

  // Create a window and draw a border around it
  IWindow win;
  win = term.CreateWin(40, 10, 5, 5);
  term.Border(win, '|', '|', '-', '-', '+', '+', '+', '+');
  term.RefreshWin(win);

  // Create a second window to demonstrate multiple windows
  IWindow win2;
  win2 = term.CreateWin(30, 10, 50, 5);
  term.Border(win2, '|', '|', '-', '-', '+', '+', '+', '+');
  term.RefreshWin(win2);
}
