#ifndef PERLIN_NOISE2D_H
#define PERLIN_NOISE2D_H

#include <math.h>

typedef struct Vec2d {
    float x, y;
} Vec2d;

Vec2d randomGradient(int ix, int iy);
float Pnoise(float x, float y);
float dotGridGradient(int ix, int iy, float x, float y);
float interpolate(float a0, float a1, float w);

#endif
