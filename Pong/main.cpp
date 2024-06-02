#include "raylib.h"
#include "PongGame.h"
using namespace std;


int main()
{
    const int screenWidth = GetScreenWidth();
    const int screenLength = GetScreenHeight();
    const int maxScore = 5;

    InitAudioDevice();
    PongGame game(screenWidth, screenLength, maxScore);

    while (!game.byeBye())
    {
        game.gameTime();
    }

    return 0;
}