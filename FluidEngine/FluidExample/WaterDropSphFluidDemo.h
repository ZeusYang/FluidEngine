#pragma once

#include "ParticleFluidDemo.h"

class WaterDropSphFluidDemo : public ParticleFluidDemo
{
public:
	typedef std::shared_ptr<WaterDropSphFluidDemo> ptr;

	WaterDropSphFluidDemo() = default;

	virtual ~WaterDropSphFluidDemo() = default;

	virtual void setup(double radius) override;

};
