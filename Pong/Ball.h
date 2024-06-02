#pragma once
#include "raylib.h"

class Ball
{
public:
    float x;
    float y;
    float ballVelocityX;
    float ballVelocityY;
    float rad;

    Ball();
    void initializeBall(int xVelocity, int yVelocity, int r);
    void velocity(int xVelocity, int yVelocity);
    void draw();
    ~Ball();
};