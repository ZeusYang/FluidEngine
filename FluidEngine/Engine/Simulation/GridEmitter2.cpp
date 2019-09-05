#include "GridEmitter2.h"


namespace Engine
{
	GridEmitter2::GridEmitter2() {}

	GridEmitter2::~GridEmitter2() {}

	void GridEmitter2::update(double currentTimeInSeconds, double timeIntervalInSeconds) 
	{
		if (_onBeginUpdateCallback) 
			_onBeginUpdateCallback(currentTimeInSeconds, timeIntervalInSeconds);

		onUpdate(currentTimeInSeconds, timeIntervalInSeconds);
	}

	bool GridEmitter2::isEnabled() const { return _isEnabled; }

	void GridEmitter2::setIsEnabled(bool enabled) { _isEnabled = enabled; }

	void GridEmitter2::setOnBeginUpdateCallback(const OnBeginUpdateCallback& callback) 
	{
		_onBeginUpdateCallback = callback;
	}
}