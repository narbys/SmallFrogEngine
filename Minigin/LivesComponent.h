#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace frog
{
    class LivesComponent final : public BaseComponent
    {
    public:
        LivesComponent(int lives);
        virtual ~LivesComponent();
        void Update() override {}
        int GetLives()const;

        void ReduceLives();
        void IncreaseLives();
        void SetLives(int lifeAmount);
    private:
        int m_Lives;
    };
}

