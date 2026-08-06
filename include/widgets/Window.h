#pragma once
#include <ostream>
#include "Cursor.h"
#include "geometry/Rect.h"
#include "core/Buffer.h"

namespace stl {
  // Border characters for the window
  struct BorderChars {
    char top         = '-'; // ─
    char left        = '|';
    char right       = '|';
    char bottom      = '-'; // ─
    char topLeft     = '+';
    char topRight    = '+';
    char bottomLeft  = '+';
    char bottomRight = '+';
  };
  // Window configuration
  struct WindowConfig {
    Rect bounds;
    
    BorderChars border;

    Style styleBody;
    Style styleBorder;
  };

	class Window {
  public:
    Window(WindowConfig& cfg);

    // Draw a border around the window
    void border();
    // Fill window with styles specified in cfg
    void fill();
    // Print random garbage in window for testing
    void print_random_garbage();
    // Print a string at (x, y)
    void print(Point pos, const std::string_view text);
    // Refresh the content of the window
    void refresh();

	private:
    WindowConfig _cfg;
    Buffer _buffer;

    void render(Window& win, std::ostream& os = std::cout);

    unsigned short columns() { return _cfg.bounds.size.columns().get(); }
    unsigned short rows() { return _cfg.bounds.size.rows().get(); }
	};
}