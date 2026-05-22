# Simple Terminal Library

A lightweight C++ terminal rendering library for building text-based applications and games.

STL provides a clean abstraction over terminal rendering, input handling, and windowed text UI construction using a per-window character buffer that is flushed to the terminal in a single render pass.

---

## Features

- Window-based terminal UI system
- Per-window 2D character frame buffers
- Buffered rendering via draw -> present pipeline
- ANSI-compatible terminal output
- Lightweight, dependency-free design
- Simple API for text-based layouts and games

---

## Goal

The goal is to better understand:
- how UI state can be represented in memory
- how rendering pipelines are structured
- how simple abstractions can create reusable UI systems

---

## Example

```cpp
#include "Color.h"
#include "Window.h"

int main() {
  WindowManager wm;
  Window win = wm.CreateWin(30, 10, 10, 5);
  wm.Border(win);
  wm.WPrintLn(win, 8, 4, "Hello, Window " + std::to_string(1).append("!"));

  Color::InitColorPairRGB(1, { 255, 255, 255 }, { 0, 0, 0 });

  Color::EnableAttribute(1);
  wm.RefreshWin(win);
  Color::DisableAttribute(1);
}
```
## Sample Output

```
          +------------------------------+
          |                              |
          |                              |
          |                              |
          |       Hello, Window 1!       |
          |                              |
          |                              |
          |                              |
          |                              |
          |                              |
          |                              |
          +------------------------------+
```

## How It Works

### Draw Phase

All rendering operations write into an in-memory 2D character buffer inside each window.

During this stage:
- Text is written into buffer cells
- Borders and UI elements modify buffer state
- No output is printed to the terminal yet

Responsible for composing the full frame in memory

---

### Present Phase

Once drawing is complete, the window buffer is flushed to the terminal in a single pass.

- The buffer is iterated row by row
- The terminal cursor is moved to the correct position
- Characters are printed to the screen

This produces the final visual output.

---

## Architecture

### Window System

Each window maintains its own independent state, including:
- A 2D character buffer
- Dimensions (width, height)
- Screen position coordinates

This allows for multiple UI regions to exist independently

---

### Rendering Model

The library follows a buffered rendering approach:

UI is first composed in memory, then rendered to the terminal.

This design provides:
- Predictable output behavior
- Clear separation between logic and presentation
- Easier UI composition and debugging

---

### Color System

A simple color system is included to support basic terminal styling through color attributes.

It allows defining color pairs and enabling or disabling styling during rendering.

---

## Design Goals

- Simple and intuitive API design
- Clear separation between drawing and rendering
- Minimal external dependencies
- Easy experimentation with terminal-based UI concepts
- Foundation for small games and tools

---
## Future Improvements

- Dirty Cell Tracking
- Support for multiple layered windows
- Improved input and event handling system
- Unicode and wide-character support
- Layout utilities (flex/grid-style positioning concepts)
- Cross-platform terminal compatibility improvements

---
## Project Status

Active development — experimental terminal UI system.
