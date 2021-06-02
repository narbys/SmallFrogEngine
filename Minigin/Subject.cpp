#include "Subject.h"

void frog::Subject::AddObserver(std::shared_ptr<Observer> pObserver)
{
	m_pObservers.push_back(pObserver);
}

void frog::Subject::RemoveObserver(std::shared_ptr<Observer> pObserver)
{
	const auto it = std::find(m_pObservers.begin(), m_pObservers.end(), pObserver);
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), *it), m_pObservers.end());
}

void frog::Subject::Notify(const Event& event)
{
	for(auto pObs : m_pObservers)
	{
		pObs->OnNotify(event);
	}
}
