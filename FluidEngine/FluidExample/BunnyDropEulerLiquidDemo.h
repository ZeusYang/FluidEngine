#pragma once

#include "EulerFluidDemo.h"

class BunnyDropEulerLiquidDemo : public EulerFluidDemo
{
public:
	typedef std::shared_ptr<BunnyDropEulerLiquidDemo> ptr;

	BunnyDropEulerLiquidDemo() = default;

	~BunnyDropEulerLiquidDemo() = default;

	virtual void setup(size_t resolutionX);

};

