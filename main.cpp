#include "raylib.h"
#include <cmath>
#include <cstdlib>
#include <queue>
#include <cstdio>

using namespace std;

const int screenWidth = 1280;
const int screenHeight = 720;
const float x_min = -2.0;
const float x_max = 0.7;
const float y_min = -1.2;
const float y_max = 1.2;
const int infinity = 2;
const int maxIter = 40;


Vector2 screenToPlane(int screenX, int screenY) {
    float x = x_min + ((float)screenX / screenWidth) * (x_max - x_min);
    float y = y_max - ((float)screenY / screenHeight) * (y_max - y_min);
    return {x, y};
}

Color getColor(float iter) {
    unsigned char c = (unsigned char) (iter * 255.0f / (float)maxIter);
    Color color = {c, c, c, 255};
    return color;
}

float diverge(float x0, float y0) {
    float x = 0;
    float y = 0;
    float iter = 0;
    float X, Y;

    for(iter=0; iter<maxIter; iter++) {
        X = x*x - y*y + x0;
        Y = 2*x*y + y0;
        if(X*X + Y*Y > infinity*infinity) {
            break;
        }
        x = X;
        y = Y;
    }
    return iter;
}


void mandelbrot() {
    for(int screenX=0; screenX<screenWidth; screenX++) {
        for(int screenY=0; screenY<screenHeight; screenY++) {
            Vector2 coordinates = screenToPlane(screenX, screenY);
            float iter = diverge(coordinates.x, coordinates.y);
            Color color = getColor(iter);
            DrawPixel(screenX, screenY, color);
        }
    }
}


int main(void)
{
    InitWindow(screenWidth, screenHeight, "Mandelbrot Set");
    SetTargetFPS(60);               
    
    bool changed = true;

    while (!WindowShouldClose()) {
        BeginDrawing();
        if (changed) {
            ClearBackground(BLACK); 
            mandelbrot();
            changed = false;
        } 
        EndDrawing();
    }
    CloseWindow();   

    return 0;
}



