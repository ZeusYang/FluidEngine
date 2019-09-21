#include "Event.h"

namespace Engine
{
	template <typename... EventArgTypes>
	bool Event<EventArgTypes...>::operator()(EventArgTypes... args)
	{
		bool handled = false;
		for (auto& callback : _callbacks) 
			handled |= callback.second(args...);
		return handled;
	}

	template <typename... EventArgTypes>
	EventToken Event<EventArgTypes...>::operator+=(const CallbackType& callback) 
	{
		_callbacks[++_lastToken] = callback;
		return _lastToken;
	}

	template <typename... EventArgTypes>
	void Event<EventArgTypes...>::operator-=(EventToken token)
	{
		_callbacks.erase(token);
	}
}