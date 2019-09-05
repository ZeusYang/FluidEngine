#pragma once

#include "ParticleFluidDemo.h"

class DamBreakingPciSphFluidDemo : public ParticleFluidDemo
{
public:
	typedef std::shared_ptr<DamBreakingPciSphFluidDemo> ptr;

	DamBreakingPciSphFluidDemo() = default;

	virtual ~DamBreakingPciSphFluidDemo() = default;

	virtual void setup(double radius) override;

};
