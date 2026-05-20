#include "Console.h"

void PrintFlag(const char* name, DWORD mode, DWORD flag) {
  std::cout << name << ": "
    << ((mode & flag) ? "\033[32mON\033[0m" : "\033[31mOFF\033[0m")
    << '\n';
}

void Flags(DWORD mode) {
  PrintFlag("PROCESSED_INPUT", mode, ENABLE_PROCESSED_INPUT);
  PrintFlag("LINE_INPUT", mode, ENABLE_LINE_INPUT);
  PrintFlag("ECHO_INPUT", mode, ENABLE_ECHO_INPUT);
  PrintFlag("MOUSE_INPUT", mode, ENABLE_MOUSE_INPUT);
  PrintFlag("INSERT_MODE", mode, ENABLE_INSERT_MODE);
  PrintFlag("QUICK_EDIT_MODE", mode, ENABLE_QUICK_EDIT_MODE);
  PrintFlag("EXTENDED_FLAGS", mode, ENABLE_EXTENDED_FLAGS);
  PrintFlag("AUTO_POSITION", mode, ENABLE_AUTO_POSITION);
  PrintFlag("WINDOW_INPUT", mode, ENABLE_WINDOW_INPUT);
  PrintFlag("VIRTUAL_TERMINAL_INPUT", mode, ENABLE_VIRTUAL_TERMINAL_INPUT);
  PrintFlag("ENABLE_VIRTUAL_TERMINAL_PROCESSING", mode, ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void EnableFlags(DWORD& mode, DWORD flags) {
  mode |= flags;
}

void DisableFlags(DWORD& mode, DWORD flags) {
  mode &= ~flags;
}

DWORD Console::_previousMode = 0;
UINT Console::_previousCP = 0;
void Console::StartupCon() {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;

  if (hStdin == INVALID_HANDLE_VALUE) {
    std::cerr << "Error getting standard input handle: " << GetLastError() << "\n";
    return;
  }

  if (GetConsoleMode(hStdin, &mode)) {
    // Save the current console mode and code page
    _previousMode = mode;
    _previousCP = GetConsoleCP();

    // Disable default input processing and enable virtual terminal input
    DisableFlags(mode, ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    EnableFlags(mode, ENABLE_VIRTUAL_TERMINAL_INPUT | ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT);

    // Apply the modified console mode
    SetConsoleMode(hStdin, mode);
    SetConsoleCP(CP_UTF8); // Set console code page to UTF-8
    SetConsoleOutputCP(CP_UTF8); // Set console output code page to UTF-8
  }

  Flags(mode);
}

void Console::RestoreCon() {
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

  SetConsoleMode(hStdin, _previousMode);
  SetConsoleCP(_previousCP); // Restore previous console code page
  SetConsoleOutputCP(_previousCP); // Restore previous console output code page

  Flags(_previousMode);
}
