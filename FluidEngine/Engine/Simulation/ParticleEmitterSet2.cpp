#include "ParticleEmitterSet2.h"

#include <vector>

namespace Engine
{
	ParticleEmitterSet2::ParticleEmitterSet2() {}

	ParticleEmitterSet2::ParticleEmitterSet2(const std::vector<ParticleEmitter2Ptr>& emitters)
		: _emitters(emitters) {}

	ParticleEmitterSet2::~ParticleEmitterSet2() {}

	void ParticleEmitterSet2::addEmitter(const ParticleEmitter2Ptr& emitter) { _emitters.push_back(emitter); }

	void ParticleEmitterSet2::onSetTarget(const ParticleSystemData2Ptr& particles)
	{
		for (auto& emitter : _emitters) 
			emitter->setTarget(particles);
	}

	void ParticleEmitterSet2::onUpdate(double currentTimeInSeconds, double timeIntervalInSeconds) 
	{
		if (!isEnabled())
			return;
		for (auto& emitter : _emitters) 
			emitter->update(currentTimeInSeconds, timeIntervalInSeconds);
	}

	ParticleEmitterSet2::Builder ParticleEmitterSet2::builder() { return Builder(); }

	ParticleEmitterSet2::Builder& ParticleEmitterSet2::Builder::withEmitters(
		const std::vector<ParticleEmitter2Ptr>& emitters) 
	{
		_emitters = emitters;
		return *this;
	}

	ParticleEmitterSet2 ParticleEmitterSet2::Builder::build() const 
	{
		return ParticleEmitterSet2(_emitters);
	}

	ParticleEmitterSet2Ptr ParticleEmitterSet2::Builder::makeShared() const 
	{
		return std::shared_ptr<ParticleEmitterSet2>(
			new ParticleEmitterSet2(_emitters),
			[](ParticleEmitterSet2* obj) { delete obj; });
	}
}