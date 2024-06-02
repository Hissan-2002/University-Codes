#include "PongGame.h"

PongGame::PongGame(int screenWidth, int screenHeight, int maxScore)
    : maxScore(maxScore)
{
    InitWindow(screenWidth, screenHeight, "Pong");
    gameMusic = LoadMusicStream("music.wav");
    PlayMusicStream(gameMusic);
    state = GameState::MENU;

    ball.initializeBall(500, 500, 15);

    leftPad.setPosition(50, GetScreenHeight() / 2);
    P1_score = "0";

    rightPad.setPosition(GetScreenWidth() - 50, GetScreenHeight() / 2);
    P2_score = "0";

    chickenDinner = nullptr;
    begin = false;
    gameWon = false;
    controlsInfo = "Controls:\nPlayer 1 - W (Up), S (Down)\nPlayer 2 - Up Arrow (Up), Down Arrow (Down)";

}
bool PongGame::byeBye()
{
    return WindowShouldClose();
}
void PongGame::gameTime()
{
    UpdateMusicStream(gameMusic);
    BeginDrawing();
    updateKeys();
    switch (state)
    {
    case GameState::MENU:
        updateMenu();
        drawMenu();
        break;

    case GameState::GAMEPLAY:
        updateGameplay();
        drawGameplay();
        break;
    }

    EndDrawing();
}
void PongGame::drawMenu()
{
    ClearBackground(RAYWHITE);

    int widthText2 = MeasureText("PONG GAME", 150);
    DrawText("PONG GAME", GetScreenWidth() / 2 - widthText2 / 2, GetScreenHeight() / 2 - 300, 150, BLACK);

    int widthText0 = MeasureText("Press ENTER to Start", 60);
    DrawText("Press ENTER to Start", GetScreenWidth() / 2 - widthText0 / 2, GetScreenHeight() / 2, 60, BLACK);

    int widthText1 = MeasureText("Press ESC to Exit", 40);
    DrawText("Press ESC to Exit", GetScreenWidth() / 2 - widthText1 / 2, GetScreenHeight() / 2 + 90, 40, BLACK);

    int widthText3 = MeasureText(("Goal: " + std::to_string(maxScore)).c_str(), 30);
    DrawText(("Goal: " + std::to_string(maxScore)).c_str(), GetScreenWidth() / 2 - widthText3 / 2, GetScreenHeight() / 2 + 200, 30, BLACK);

    int widthText4 = MeasureText(controlsInfo.c_str(), 30);
    DrawText(controlsInfo.c_str(), GetScreenWidth() / 2 - widthText4 / 2, GetScreenHeight() / 2 + 240, 30, BLACK);

    if (gameWon)
    {
        int TextWidth = MeasureText("Congratulations! You won", 60);
        DrawText("Congratulations! You won", GetScreenWidth() / 2 - TextWidth / 2, GetScreenHeight() - 150, 60, GREEN);
    }
}
void PongGame::drawGameplay()
{
    ClearBackground(BLACK);
    DrawFPS(0, 0);
    ball.draw();
    DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), RAYWHITE);
    DrawCircleLines(GetScreenWidth() / 2, GetScreenHeight() / 2, 160, RAYWHITE);
    leftPad.draw(DARKGREEN);
    rightPad.draw(DARKGREEN);
    DrawText(P1_score.c_str(), GetScreenWidth() / 2 - 80, GetScreenHeight() - 100, 80, PURPLE);
    DrawText(P2_score.c_str(), GetScreenWidth() / 2 + 40, GetScreenHeight() - 100, 80, PURPLE);
}
void PongGame::updateMenu()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        state = GameState::GAMEPLAY;
        begin = true;
    }
}
void PongGame::updateGameplay()
{
    if (!begin)
    {
        int widthText0 = MeasureText("Press Space to Start", 60);
        DrawText("Press Space to Start", GetScreenWidth() / 2 - widthText0 / 2, GetScreenHeight() / 2 - 80, 60, YELLOW);

        if (IsKeyPressed(KEY_ENTER))
        {
            ball.x += ball.ballVelocityX * GetFrameTime();
            ball.y += ball.ballVelocityY * GetFrameTime();
            begin = true;
        }
    }
    else
    {
        ball.x += ball.ballVelocityX * GetFrameTime();
        ball.y += ball.ballVelocityY * GetFrameTime();

        if (ball.y < 0)
        {
            ball.y = 0;
            ball.ballVelocityY *= -1;
        }
        if (ball.y > GetScreenHeight())
        {
            ball.y = GetScreenHeight();
            ball.ballVelocityY *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.rad, leftPad.getRectangle()))
        {
            if (ball.ballVelocityX < 0)
                ball.ballVelocityX *= -1.1f;
        }

        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.rad, rightPad.getRectangle()))
        {
            if (ball.ballVelocityX > 0)
                ball.ballVelocityX *= -1.1f;
        }

        if (ball.x < 0)
            chickenDinner = "Player 1 scores! Press Enter";

        if (ball.x > GetScreenWidth())
            chickenDinner = "Player 2 scores! Press Enter";

        if (chickenDinner && IsKeyPressed(KEY_ENTER))
        {
            if (ball.x < 0)
            {
                P2_score = std::to_string(rightPad.increaseScore());
                if (rightPad.score >= maxScore)
                {
                    gameWon = true;
                    state = GameState::MENU;
                    resetGame();
                }
                ball.velocity(400, 400);
            }
            if (ball.x > GetScreenWidth())
            {
                P1_score = std::to_string(leftPad.increaseScore());
                if (leftPad.score >= maxScore)
                {
                    gameWon = true;
                    state = GameState::MENU;
                    resetGame();
                }
                ball.velocity(-1 * 400, 400);
            }

            ball.x = GetScreenWidth() / 2.0f;
            ball.y = GetScreenHeight() / 2.0f;

            leftPad.y = GetScreenHeight() / 2;
            rightPad.y = GetScreenHeight() / 2;

            chickenDinner = nullptr;
        }

        if (chickenDinner)
        {
            int widthText = MeasureText(chickenDinner, 60);
            DrawText(chickenDinner, GetScreenWidth() / 2 - widthText / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
        }
    }
}
void PongGame::updateKeys()
{
    if (IsKeyDown(KEY_W) && leftPad.y > 50)
        leftPad.y -= leftPad.velocity * GetFrameTime();

    if (IsKeyDown(KEY_S) && leftPad.y < GetScreenHeight() - 55)
        leftPad.y += leftPad.velocity * GetFrameTime();

    if (IsKeyDown(KEY_UP) && rightPad.y > 55)
        rightPad.y -= rightPad.velocity * GetFrameTime();

    if (IsKeyDown(KEY_DOWN) && rightPad.y < GetScreenHeight() - 55)
        rightPad.y += rightPad.velocity * GetFrameTime();
}
void PongGame::resetGame()
{
    leftPad.score = 0;
    rightPad.score = 0;
    P1_score = "0";
    P2_score = "0";
}
PongGame::~PongGame()
{
    CloseWindow();
}