#pragma once

#include "ParticleFluidDemo.h"

class BunnyDropPciSphFluidDemo : public ParticleFluidDemo
{
public:
	typedef std::shared_ptr<BunnyDropPciSphFluidDemo> ptr;

	BunnyDropPciSphFluidDemo() = default;

	virtual ~BunnyDropPciSphFluidDemo() = default;

	virtual void setup(double radius) override;

};
