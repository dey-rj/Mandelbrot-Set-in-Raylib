# Mandelbrot Set Renderer
<img width="1261" height="716" alt="Image" src="https://github.com/user-attachments/assets/6ae0d3c4-e681-431d-8348-2773e6c5a836" />
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

## Math Behind the Scenes

### 1. Setting up Global Variables

These values determine which portion of the Mandelbrot set is initially visible:

- $x_{min} = -2.0$  
- $x_{max} = 0.7$  
- $y_{min} = -1.2$  
- $y_{max} = 1.2$  

#### Screen Resolution

These define the size of the rendering window.

- $\text{width} = 1280$  
- $\text{height} = 720$  


#### Iteration Parameters

- $\text{maxIter} = 50$  
- $\text{escape radius} = 2$  

A point is considered to diverge if:

$x^2 + y^2 > 2^2$

#### Precision Control

- $\text{minRange} = 10^{-12}$  

This prevents excessive zooming where floating-point precision becomes unreliable.

---



### 2. Mapping Screen → Complex Plane


Each pixel $(x_{screen}, y_{screen})$ is mapped to a point $(x, y)$ in the complex plane:

$x = x_{min} + \frac{x_{screen}}{\text{width}} \cdot (x_{max} - x_{min})$

As y axis is inverted in raylib,

$y = y_{max} - \frac{y_{screen}}{\text{height}} \cdot (y_{max} - y_{min})$ 

---

### 3. Iteration

For each pixel:
- Apply the Mandelbrot equation
- Stop when:
  - |z| > 2 (diverges), or
  - Maximum iterations reached

---

### 4. Coloring

- Points inside the set → darker
- Points that escape earlier → lighter

The grayscale color is based on iteration count:

$\text{color} = \frac{\text{iter}}{\text{maxIter}} \times 255$


---

### 5. Zooming (Mouse-Centered)

The zoom is performed using mouse scroll wheel **around the mouse cursor**, making exploration intuitive.

The mouse position on the screen $(mouse_x, mouse_y)$ is mapped to a point in the complex plane as $(x_c, y_c)$:

$x_c = x_{min} + \frac{mouse_x}{\text{width}} (x_{max} - x_{min})$

$y_c = y_{max} - \frac{mouse_y}{\text{height}} (y_{max} - y_{min})$


Zooming is controlled by a scale factor:

$\text{scale} = zoomFactor^{-scroll}$, eg. zoomFactor = 1.1


The new coordinate bounds are scaled around the cursor:

$x_{min} = x_c - (x_c - x_{min}) \cdot \text{scale}$

$x_{max} = x_c + (x_{max} - x_c) \cdot \text{scale}$

$y_{min} = y_c - (y_c - y_{min}) \cdot \text{scale}$

$y_{max} = y_c + (y_{max} - y_c) \cdot \text{scale}$

---



## Build & Run

### Requirements
- C++ compiler (g++, clang)
- raylib installed

### Compile

```bash
bash build.bash
./a.out