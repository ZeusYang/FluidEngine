#pragma once

#include <string>
#include <memory>

#include "Engine/Simulation/PhysicsAnimation.h"

class FluidDemo
{
public:
	typedef std::shared_ptr<FluidDemo> ptr;

	FluidDemo() = default;

	virtual ~FluidDemo() = default;

	virtual void run(const std::string &rootDir, int numberOfFrames,
		const std::string &format, double fps) = 0;
	
};