#pragma once

#include "EulerFluidDemo.h"

class SmokeRisingDragonEulerFluidDemo : public EulerFluidDemo
{
public:
	typedef std::shared_ptr<SmokeRisingDragonEulerFluidDemo> ptr;

	SmokeRisingDragonEulerFluidDemo() = default;

	virtual ~SmokeRisingDragonEulerFluidDemo() = default;

	virtual void setup(size_t resolutionX) override;

};

