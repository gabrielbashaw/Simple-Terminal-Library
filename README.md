# Simple Terminal Library

A lightweight C++ terminal rendering library for building text-based applications and games.

STL provides a clean abstraction over terminal rendering, input handling, and windowed text UI construction using a per-window character buffer that is flushed to the terminal in a single render pass.

---

<!-- Features Section -->
### Features:

- Window-based terminal UI system
- Per-window 2D character frame buffers
- Buffered rendering via draw -> present pipeline
- ANSI-compatible terminal output
- Lightweight, dependency-free design
- Simple API for text-based layouts and games

#

<!-- Goals Section -->
### Goals:

**The goal is to better understand:**
- how UI state can be represented in memory
- how rendering pipelines are structured
- how simple abstractions can create reusable UI systems

---

<!-- Example Section -->
## Example:

  The following code demonstrates how to create a window, draw some text, and render it to the terminal.

#

<details>
  <summary><h3>Sample Code:</h3></summary>

  ```cpp
  #include "Color.h"
  #include "Window.h"

  // Function to create and configure a window
  stl::Window WindowBuilder(
  uint16_t width, uint16_t height,
  uint16_t startX, uint16_t startY) {
  stl::Color color;
  stl::WindowConfig cfg{        // Window configuration parameters
    .startX = startX,
    .startY = startY,
    .width = width,
    .height = height,
    .style = color.style_rgb({ 255, 255, 255 }, { 0, 0, 0 }),
  };
  stl::Window win(cfg);         // Create a window with the specified configuration
  win.print_random_garbage();   // Fill the window buffer with random characters for testing
  win.print(3, 3, "String");    // Print "String" at position (3, 3) in the window buffer
  win.border();                 // Draw a border around the window
  return win;
}
  
  int main() {
    uint16_t width = 30;
    uint16_t height = 10;
    uint16_t startX = 5;
    uint16_t startY = 5;

    stl::Window win = WindowBuilder(width, height, startX, startY);

    while (true) {
      win.refresh(std::cout);   // Render the window buffer to the terminal
    }
  }
  ```
</details>

#

<details>
  <summary><h3>Sample Output:</h3></summary>

  ```
  +------------------------------+
  |IE`zjQn#mQ%9&,q0Rcm5{e'Z'@D!UH|
  |@bNK`Y1o>.-]c<#)D0F<w~mmwBnSj2|
  |]zStringjFvW9oRW{DiA[sQ$I\:]]x|
  |BL52;d_wB+sRo2~R,:F]qWGh Brx^m|
  |NuI0>c yIru*?`!*JlT@c@-<>j$d{_|
  |YXS/i#M&OH9yj1n7MSw>?X` Dqs3#e|
  |0oU$((\smw7iK_JN\^-.[0>bp8t0}}|
  |QsQ8j6\\U}<cV#F9__\Diq3xorO^-E|
  |UQM1i0Wx]0TeO*}DOIa<G"~v?n^?N~|
  |JgYeHhCH(o!Z&$Ws^HT9-l6'OYt`gy|
  |:jx"R*.3?,>*ZPtiB]^tBT+=#/cvgR|
  |iE*t`0]Xv(FC9(Yi;MF0+svT&[0r$g|
  |99Z0j~h=Zj=\zBlP)|nUh9#lE/cL$o|
  |jBT3UMmr-'(aU(|4^9P;T.@\78#ON:|
  |Ah9K40EO;?Q/| x$4%MUN/v,a*M.C[|
  +------------------------------+
  ```
</details>

---

<!-- How It Works Section -->
## How It Works:

### Draw Phase

All rendering operations write into an in-memory 2D character buffer inside each window.

During this stage:
- Text is written into buffer cells
- Borders and UI elements modify buffer state
- No output is printed to the terminal yet

Responsible for composing the full frame in memory

#

### Present Phase

Once drawing is complete, the window buffer is flushed to the terminal in a single pass.

- The buffer is iterated row by row
- The terminal cursor is moved to the correct position
- Characters are printed to the screen

This produces the final visual output.

---

<!-- Architecture Section -->
## Architecture

### Window System

Each window maintains its own independent state, including:
- A 2D character buffer
- Dimensions (width, height)
- Screen position coordinates

This allows for multiple UI regions to exist independently

#

### Rendering Model

The library follows a buffered rendering approach:

UI is first composed in memory, then rendered to the terminal.

This design provides:
- Predictable output behavior
- Clear separation between logic and presentation
- Easier UI composition and debugging

#

### Color System

A simple color system is included to support basic terminal styling through color attributes.

It allows defining color pairs and enabling or disabling styling during rendering.

---

<!-- Design Goals Section -->
## Design Goals

- Simple and intuitive API design
- Clear separation between drawing and rendering
- Minimal external dependencies
- Easy experimentation with terminal-based UI concepts
- Foundation for small games and tools

---

<!-- Future Improvements Section -->
## Future Improvements

- Dirty Cell Tracking
- Support for multiple layered windows
- Improved input and event handling system
- Unicode and wide-character support
- Layout utilities (flex/grid-style positioning concepts)
- Cross-platform terminal compatibility improvements

---

<!--- Project Status Section -->
## Project Status

Active development — experimental terminal UI system.
