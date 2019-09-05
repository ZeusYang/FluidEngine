#pragma once

#include "FluidDemo.h"

#include "Engine/Math/Size3.h"
#include "Engine/Simulation/ParticleSystemData3.h"
#include "Engine/Simulation/ParticleSystemSolver3.h"

class ParticleFluidDemo : public FluidDemo
{
public:
	typedef std::shared_ptr<ParticleFluidDemo> ptr;

	ParticleFluidDemo() = default;

	virtual ~ParticleFluidDemo() = default;

	virtual void setup(double radius) = 0;

	virtual void run(const std::string &rootDir, int numberOfFrames,
		const std::string &format, double fps) override;

protected:
	std::string _sceneXml;
	double maxX, maxY, maxZ;
	double minX, minY, minZ;
	double _sphCutOffDensity = 0.5;
	Engine::Vector3D _origin;
	Engine::Size3 _resolution;

	Engine::ParticleSystemSolver3Ptr _solver = nullptr;

	void saveParticleAsObj(const Engine::ParticleSystemData3Ptr &particles,
		const std::string &rootDir, int frameCnt);

	void saveParticleAsXml(const Engine::ParticleSystemData3Ptr &particles,
		const std::string &rootDir, int frameCnt);

	void saveParticleAsPos(const Engine::ParticleSystemData3Ptr &particles,
		const std::string &rootDir, int frameCnt);

	void saveParticleAsXyz(const Engine::ParticleSystemData3Ptr &particles,
		const std::string &rootDir, int frameCnt);

};
