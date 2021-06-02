#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "SmallFrog.h"

int main(int, char*[]) {
	frog::SmallFrog engine;
	engine.Run();
    return 0;
}