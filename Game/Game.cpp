#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif
#include <crtdbg.h>
#include <SmallFrog.h>

#include "QBertGame.h"
int main()
{
    frog::SmallFrog engine;
    engine.m_pGame = new QBertGame();
    engine.Run();
    return 0;
}