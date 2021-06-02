#include <SmallFrog.h>
#include "QBertGame.h"
int main()
{
    frog::SmallFrog engine;
    engine.m_pGame = new QBertGame();
    engine.Run();
    return 0;
}