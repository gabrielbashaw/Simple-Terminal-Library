#include "terminal/win32.h"

void print_flag(const char* name, DWORD mode, DWORD flag) {
  std::cout << name << ": "
    << ((mode & flag) ? "\033[32mON\033[0m" : "\033[31mOFF\033[0m")
    << '\n';
}

void enable_flags(DWORD& mode, DWORD flags) { mode |= flags; }

void disable_flags(DWORD& mode, DWORD flags) { mode &= ~flags; }

void win32::flags(DWORD mode) {
  print_flag("PROCESSED_INPUT", mode, ENABLE_PROCESSED_INPUT);
  print_flag("LINE_INPUT", mode, ENABLE_LINE_INPUT);
  print_flag("ECHO_INPUT", mode, ENABLE_ECHO_INPUT);
  print_flag("MOUSE_INPUT", mode, ENABLE_MOUSE_INPUT);
  print_flag("INSERT_MODE", mode, ENABLE_INSERT_MODE);
  print_flag("QUICK_EDIT_MODE", mode, ENABLE_QUICK_EDIT_MODE);
  print_flag("EXTENDED_FLAGS", mode, ENABLE_EXTENDED_FLAGS);
  print_flag("AUTO_POSITION", mode, ENABLE_AUTO_POSITION);
  print_flag("WINDOW_INPUT", mode, ENABLE_WINDOW_INPUT);
  print_flag("VIRTUAL_TERMINAL_INPUT", mode, ENABLE_VIRTUAL_TERMINAL_INPUT);
  print_flag("ENABLE_VIRTUAL_TERMINAL_PROCESSING", mode, ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

DWORD _previousMode = 0;
UINT  _previousCP   = 0;

void win32::start_con(std::string title) {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;

  if (hStdin == INVALID_HANDLE_VALUE) {
    std::cerr << "Error getting standard input handle: " << GetLastError() << "\n";
    return;
  }
  
  std::cout << "\033]2;" << title << "\007";
  
  if (GetConsoleMode(hStdin, &mode)) {
    _previousMode = mode;
    _previousCP = GetConsoleCP();

    // Disable default input processing and enable virtual terminal input
    disable_flags(mode, ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT);
    enable_flags(mode, ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    // Apply the modified console mode
    SetConsoleMode(hStdin, mode);
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
  }
}

void win32::no_echo() {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;

  if (hStdin == INVALID_HANDLE_VALUE) {
    std::cerr << "Error getting standard input handle: " << GetLastError() << "\n";
    return;
  }

  // Disable echoing of input characters
  if (GetConsoleMode(hStdin, &mode)) {
    disable_flags(mode, ENABLE_ECHO_INPUT);
    SetConsoleMode(hStdin, mode);
  }
}

void win32::restore_con() {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

  SetConsoleMode(hStdin, _previousMode);
  SetConsoleCP(_previousCP);
  SetConsoleOutputCP(_previousCP);

  flags(_previousMode);
}

const stl::Point win32::get_console_size() {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  return { 
    csbi.srWindow.Right - csbi.srWindow.Left + 1,
    csbi.srWindow.Bottom - csbi.srWindow.Top + 1
  };
}

bool win32::get_console_resize(short *w, short *h) {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) 
    return false;
  *w = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  *h = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  return true;
}
