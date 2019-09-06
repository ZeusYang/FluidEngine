#pragma once

#include "EulerFluidDemo.h"

class SmokeRisingEulerFluidDemo : public EulerFluidDemo
{
public:
	typedef std::shared_ptr<SmokeRisingEulerFluidDemo> ptr;

	SmokeRisingEulerFluidDemo() = default;

	virtual ~SmokeRisingEulerFluidDemo() = default;

	virtual void setup(size_t resolutionX) override;

};

