#pragma once

#include "ParticleFluidDemo.h"

class FluidPipeDropPciSphFluidDemo : public ParticleFluidDemo
{
public:
	typedef std::shared_ptr<FluidPipeDropPciSphFluidDemo> ptr;

	FluidPipeDropPciSphFluidDemo() = default;

	virtual ~FluidPipeDropPciSphFluidDemo() = default;

	virtual void setup(double radius) override;

};

