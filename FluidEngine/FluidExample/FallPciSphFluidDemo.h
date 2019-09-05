#pragma once

#include "ParticleFluidDemo.h"

class FallPciSphFluidDemo : public ParticleFluidDemo
{
public:
	typedef std::shared_ptr<FallPciSphFluidDemo> ptr;

	FallPciSphFluidDemo() = default;

	virtual ~FallPciSphFluidDemo() = default;

	virtual void setup(double radius) override;

};