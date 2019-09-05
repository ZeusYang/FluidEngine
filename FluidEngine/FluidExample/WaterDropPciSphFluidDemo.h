#pragma once

#include "ParticleFluidDemo.h"

class WaterDropPciSphFluidDemo : public ParticleFluidDemo
{
public:
	typedef std::shared_ptr<WaterDropPciSphFluidDemo> ptr;

	WaterDropPciSphFluidDemo() = default;

	virtual ~WaterDropPciSphFluidDemo() = default;

	virtual void setup(double radius) override;

};

