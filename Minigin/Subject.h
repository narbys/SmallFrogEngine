#pragma once
#include <vector>

#include "Observer.h"
namespace dae
{
	class Subject
	{
	public:
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
	protected:
		void Notify(Event event);
	private:
		std::vector<Observer*> m_pObservers;
	};
}
