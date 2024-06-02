#include "Paddle.h"

Paddle::Paddle()
{
    velocity = 900;
    length = 220;
    width = 25;
    score = 0;
}
Paddle::Paddle(float len, float wid, float vel)
{
    length = len;
    width = wid;
    velocity = vel;
    score = 0;
}
int Paddle::increaseScore()
{
    score++;
    return score;
}
void Paddle::setPosition(float xx, float yy)
{
    x = xx;
    y = yy;
}
Rectangle Paddle::getRectangle()
{
    return Rectangle{ x - width / 2, y - length / 2, width, length };
}
void Paddle::draw(Color col)
{
    DrawRectangleRec(getRectangle(), col);
}
Paddle::~Paddle() {}