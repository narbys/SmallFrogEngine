#pragma once

#include "Renderer.h"
#include "GameObject.h"
#include "ComponentIncludes.h"
#include "ServiceLocator.h"

namespace frog
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute() = 0;
	};

	class BeepboopCommand : public Command
	{
	public:
		void Execute() override
		{
			Renderer::GetInstance().LogDebugText("Beepboop");
			ServiceLocator::GetSoundSystem()->PlaySound("../Data/door1.wav", 10);
		};
	};

	class KillPlayerCommand : public Command
	{
	public:
		KillPlayerCommand(GameObject* pGameObject) : m_pGameObj(pGameObject){}
		void Execute() override
		{
			m_pGameObj->GetComponent<LivesComponent>()->ReduceLives();
			Renderer::GetInstance().LogDebugText("Kill Player");
		}
	private:
		GameObject* m_pGameObj;
	};
	class IncreaseScoreCommand : public Command
	{
	public:
		IncreaseScoreCommand(GameObject* pGameObject) : m_pGameObj(pGameObject) {}
		void Execute() override
		{
			m_pGameObj->GetComponent<ScoreComponent>()->AddToScore(25);
			Renderer::GetInstance().LogDebugText("Added 25 to score\n");
		}
	private:
		GameObject* m_pGameObj;
	};
}
