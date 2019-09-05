#include "GridEmitter3.h"

namespace Engine
{
	GridEmitter3::GridEmitter3() {}

	GridEmitter3::~GridEmitter3() {}

	void GridEmitter3::update(double currentTimeInSeconds, double timeIntervalInSeconds)
	{
		if (_onBeginUpdateCallback) 
			_onBeginUpdateCallback(currentTimeInSeconds, timeIntervalInSeconds);

		onUpdate(currentTimeInSeconds, timeIntervalInSeconds);
	}

	bool GridEmitter3::isEnabled() const { return _isEnabled; }

	void GridEmitter3::setIsEnabled(bool enabled) { _isEnabled = enabled; }

	void GridEmitter3::setOnBeginUpdateCallback(const OnBeginUpdateCallback& callback) 
	{
		_onBeginUpdateCallback = callback;
	}

}