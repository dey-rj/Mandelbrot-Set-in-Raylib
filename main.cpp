#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <queue>
#include <cstdio>

using namespace std;

#include "raylib.h"
#include <cmath>

const int screenWidth = 1280;
const int screenHeight = 720;

double x_min = -2.0;
double x_max = 0.7;
double y_min = -1.2;
double y_max = 1.2;
double minRange = 1e-12;

const int maxIter = 50;
const double infinity = 2.0;


struct Vec2d {
    double x, y;
};


Vec2d screenToPlane(int screenX, int screenY) {
    double x = x_min + ((double)screenX / screenWidth) * (x_max - x_min);
    double y = y_max - ((double)screenY / screenHeight) * (y_max - y_min);
    return {x, y};
}


void zoom(float scroll) {
    if (scroll == 0) return;

    if (scroll > 1) scroll = 1;
    if (scroll < -1) scroll = -1;

    Vector2 mouse = GetMousePosition();

    double zoomFactor = 1.1;
    double scale = pow(zoomFactor, -scroll);

    double x_c = x_min + (mouse.x / screenWidth) * (x_max - x_min);
    double y_c = y_max - (mouse.y / screenHeight) * (y_max - y_min);

    
    if ((x_max - x_min) < minRange) return;

    x_min = x_c - (x_c - x_min) * scale;
    x_max = x_c + (x_max - x_c) * scale;

    y_min = y_c - (y_c - y_min) * scale;
    y_max = y_c + (y_max - y_c) * scale;
}


int diverge(double x0, double y0) {
    double x = 0.0;
    double y = 0.0;

    int iter;
    for (iter = 0; iter < maxIter; iter++) {
        double X = x * x - y * y + x0;
        double Y = 2 * x * y + y0;

        if (X * X + Y * Y > infinity * infinity) break;

        x = X;
        y = Y;
    }
    return iter;
}


Color getColor(int iter) {
    unsigned char c = (unsigned char)(iter * 255 / maxIter);
    return {c, c, c, 255};
}


void mandelbrot() {
    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight; y++) {
            Vec2d p = screenToPlane(x, y);
            int iter = diverge(p.x, p.y);
            Color color = getColor(iter);
            DrawPixel(x, y, color);
        }
    }
}


int main() {
    InitWindow(screenWidth, screenHeight, "Mandelbrot Set");
    SetTargetFPS(60);

    bool changed = true;

    while (!WindowShouldClose()) {
        BeginDrawing();

        float scroll = GetMouseWheelMove();
        if (scroll != 0) {
            zoom(scroll);
            changed = true;
        }

        if (changed) {
            ClearBackground(BLACK);
            mandelbrot();
            DrawText("scroll to zoom around cursor", 20, 20, 30, WHITE); 
            changed = false;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}



