#pragma once
#include "raylib.h"

class Paddle
{
public:
    int score;
    float x;
    float y;
    float width;
    float length;
    float velocity;

    Paddle();
    Paddle(float len, float wid, float vel);
    void draw(Color col);
    void setPosition(float x, float y);
    int increaseScore();
    Rectangle getRectangle();
    ~Paddle();
};