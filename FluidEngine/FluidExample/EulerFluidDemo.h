#pragma once

#include "FluidDemo.h"

#include "Engine/Math/Size3.h"
#include "Engine/Math/Vector3.h"
#include "Engine/Geometry/ScalarGrid3.h"
#include "Engine/Simulation/GridFluidSolver3.h"

class EulerFluidDemo : public FluidDemo
{
public:
	typedef std::shared_ptr<EulerFluidDemo> ptr;

	EulerFluidDemo() = default;

	virtual ~EulerFluidDemo() = default;

	virtual void setup(size_t resolutionX) = 0;

	virtual void run(const std::string &rootDir, int numberOfFrames,
		const std::string &format, double fps) override;

protected:
	std::string _sceneXml;
	double maxX, maxY, maxZ;
	double minX, minY, minZ;
	Engine::Vector3D _origin;
	Engine::Size3 _resolution;
	Engine::GridFluidSolver3Ptr _solver = nullptr;

	void saveAsSmokeXml(const Engine::ScalarGrid3Ptr &density,const std::string &rootDir, int frameCnt);

	float smoothStep(float edge0, float edge1, float x);

};

