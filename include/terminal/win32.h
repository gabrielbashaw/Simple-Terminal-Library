#pragma once
#include <iostream>
#include <windows.h>
#include "geometry/point.h"

namespace win32 {
  /* Console mode management */
  // Set terminal to "Raw Mode"
  void start_con(std::string title = "");
  // Disable echoing to the console
  void no_echo();
  // Restore previous mode
  void restore_con();
  // Display flags
  void flags(DWORD mode);

  /* Console dimensions */
  // Gets console size
  const stl::Point get_console_size();
  // Gets current size if resized
  bool get_console_resize(short *width, short *height);
}
