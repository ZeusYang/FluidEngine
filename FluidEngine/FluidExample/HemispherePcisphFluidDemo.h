#pragma once

#include "ParticleFluidDemo.h"

class HemispherePcisphFluidDemo : public ParticleFluidDemo
{
public:
	typedef std::shared_ptr<HemispherePcisphFluidDemo> ptr;

	HemispherePcisphFluidDemo() = default;

	virtual ~HemispherePcisphFluidDemo() = default;

	virtual void setup(double radius) override;

	void setupFromPreviousFrame(double radius, const std::string &dir, int frameCnt);

};
