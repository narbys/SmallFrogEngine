#pragma once
namespace frog
{
	class Game
	{
	public:
		virtual ~Game() = default;
		virtual void LoadGame() const = 0;
	};
}

