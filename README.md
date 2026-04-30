# Mandelbrot Set Renderer

A simple Mandelbrot Set visualizer built using **C++** and **raylib**.  
This project demonstrates how mathematical concepts from complex numbers can be used to generate fractals.


## What is the Mandelbrot Set?

The Mandelbrot set is defined by the iterative equation:

zₙ₊₁ = zₙ² + c

Where:
- z and c are complex numbers
- Start with z₀ = 0
- For each point c, iterate the equation

If the magnitude of z stays bounded (does not exceed 2), the point belongs to the set.

---

## How It Works

### 1. Mapping Screen → Complex Plane

Each pixel (x, y) is mapped to:

x ∈ [x_min, x_max]  
y ∈ [y_min, y_max]

---

### 2. Iteration

For each pixel:
- Apply the Mandelbrot equation
- Stop when:
  - |z| > 2 (diverges), or
  - Maximum iterations reached

---

### 3. Coloring

- Points inside the set → darker
- Points that escape earlier → lighter

---

## Features

- Pixel-by-pixel rendering using raylib
- Adjustable coordinate range
- Configurable iteration depth
- Real-time rendering window

---

## Build & Run

### Requirements
- C++ compiler (g++, clang)
- raylib installed

### Compile

```bash
bash build.bash
./a.out