#pragma once
#include <vector>

#include "Observer.h"
namespace frog
{
	class Subject
	{
	public:
		void AddObserver(std::shared_ptr<Observer>pObserver);
		void RemoveObserver(std::shared_ptr<Observer>pObserver);
		void Notify(const Event& event);
	private:
		std::vector<std::shared_ptr<Observer>> m_pObservers;
	};
}
