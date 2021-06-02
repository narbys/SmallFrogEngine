#pragma once
//Credit to Rhidian De Wit
#include <tuple>

namespace frog
{
	enum class Events
	{
		INIT,
		PLAYER_DEATH,
		SCORE_INCREASE
	};

	struct IEventData abstract
	{
		virtual ~IEventData() = default;
	};
	template<typename ... Args>
	struct EventData final : public IEventData
	{
		explicit EventData(Args ... args) : Data{ std::make_tuple(args...) } {}
		std::tuple<Args...> Data;
	};
	class Event final
	{
	public:
		Event(Events events)
			: event{ events },
			pData(nullptr)
		{
		}

		template<typename ... Args>
		Event(Events events, Args ... args)
			: event{ events }
			, pData{new EventData<Args...>(args...)}
		{
		}
		
		~Event()
		{
			if (pData)
			{
				delete pData;
				pData = nullptr;
			}
		}
		
		template<typename ... Args>
		std::tuple<Args...> GetData() const
		{
			return static_cast<EventData<Args...>*>(pData)->Data;
		}
		
		Events event;
	private:
		IEventData* pData;
	};
}