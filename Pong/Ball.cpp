#include"Ball.h"

Ball::Ball()
{
    x = GetScreenWidth() / 2.0f;
    y = GetScreenHeight() / 2.0f;
    rad = 15;
    ballVelocityX = 420;
    ballVelocityY = 420;
}
void Ball::initializeBall(int x_speed, int y_speed, int radius)
{
    x = GetScreenWidth() / 2.0f;
    y = GetScreenHeight() / 2.0f;
    rad = radius;
    ballVelocityX = x_speed;
    ballVelocityY = y_speed;
}
void Ball::velocity(int x_speed, int y_speed)
{
    ballVelocityX = x_speed;
    ballVelocityY = y_speed;
}
void Ball::draw()
{
    DrawCircle((int)x, (int)y, rad, RAYWHITE);
}

Ball::~Ball() {}