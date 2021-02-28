#pragma once
namespace dae
{
	enum class Event
	{
		
	};
	
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(const class Subject& subject, Event event)=0;
	};
}
