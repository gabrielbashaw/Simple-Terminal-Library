#pragma once
#include <iostream>
#include <Windows.h>

class Console {
public:
  Console(int width, int height, int startX, int startY);
  ~Console();

  /* Console mode management */
  // Save the current console mode, modify it for custom input handling, and apply it
  static void StartupCon();
  // Restore the console mode to its previous state
  static void RestoreCon();

private:
  static DWORD _previousMode;
  static UINT _previousCP;
};

