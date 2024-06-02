#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "GameState.h"
#include "raylib.h"
#include <string>
using namespace std;

class PongGame
{
    GameState state;
    bool begin;
    std::string P1_score, P2_score;
    Paddle leftPad, rightPad;
    Ball ball;
    const char* chickenDinner;
    bool gameWon;
    string controlsInfo;
    Music gameMusic;

    void drawMenu();
    void drawGameplay();
    void updateMenu();
    void updateGameplay();
    void updateKeys();
    void resetGame();
    const int maxScore;

public:
    PongGame(int scWidth, int scLength, int maxScore);
    bool byeBye();
    void gameTime();
    ~PongGame();
};
