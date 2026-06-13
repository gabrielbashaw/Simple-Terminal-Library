#pragma once
#include <iostream>
#include <Windows.h>

/// <summary>
/// Provides functionality for managing the console mode, 
/// including saving the current mode, modifying it for custom input handling, 
/// and restoring it to its previous mState. 
/// It allows for enabling and disabling specific console input modes to 
/// facilitate features like capturing key events without interference from default processing.
/// </summary>
class Console {
public:
  Console(int width, int height, int startX, int startY);
  ~Console();

  /* Console mode management */
  // Save the current console mode, modify it for custom input handling, and apply it
  static void StartupCon();
  // Disable echoing of input characters to the console
  static void NoEcho();
  // Restore the console mode to its previous mState
  static void RestoreCon();
  /* End Console mode management */

private:
  static DWORD _previousMode;
  static UINT _previousCP;
};

