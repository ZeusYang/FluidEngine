#pragma once

#include "ParticleFluidDemo.h"

class DamBreakingSphFluidDemo : public ParticleFluidDemo
{
public:
	typedef std::shared_ptr<DamBreakingSphFluidDemo> ptr;

	DamBreakingSphFluidDemo() = default;

	virtual ~DamBreakingSphFluidDemo() = default;

	virtual void setup(double radius) override;

};
