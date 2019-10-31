#include "RawParticleEmitter3.h"

namespace Engine
{
	RawParticleEmitter3::RawParticleEmitter3(const Array1<Vector3D>& positions, bool isOneShot)
		: _isOneShot(isOneShot), _positions(positions) { }

	bool RawParticleEmitter3::isOneShot() const { return _isOneShot; }

	RawParticleEmitter3::Builder RawParticleEmitter3::builder() { return Builder(); }

	void RawParticleEmitter3::onUpdate(double currentTimeInSeconds, double timeIntervalInSeconds)
	{
		auto particles = target();
		if (particles == nullptr)
			return;
		if (!isEnabled())
			return;

		Array1<Vector3D> newPositions;
		Array1<Vector3D> newVelocities;

		emit(particles, &newPositions, &newVelocities);
		particles->addParticles(newPositions.constAccessor(), newVelocities.constAccessor());

		if (_isOneShot)
			setIsEnabled(false);
	}

	void RawParticleEmitter3::emit(const ParticleSystemData3Ptr & particles,
		Array1<Vector3D>* newPositions, Array1<Vector3D>* newVelocities)
	{
		newPositions->append(_positions);
		size_t numNewParticles = newPositions->size();
		_numberOfEmittedParticles += numNewParticles;

		std::cout << "Number of newly generated particles: " << numNewParticles << std::endl;
		std::cout << "Number of total generated particles: " << _numberOfEmittedParticles << std::endl;

		newVelocities->resize(newPositions->size());
		newVelocities->parallelForEachIndex([&](size_t i) {
			(*newVelocities)[i] = Vector3D(0.0, 0.0, 0.0); });

		//! release the data.
		if (_isOneShot)
			Array1<Vector3D>().swap(_positions);
	}

	RawParticleEmitter3::Builder & RawParticleEmitter3::Builder::withPositions(Array1<Vector3D>* positions)
	{
		_positions = positions;
		return *this;
	}

	RawParticleEmitter3::Builder& RawParticleEmitter3::Builder::withIsOneShot(bool isOneShot)
	{
		_isOneShot = isOneShot;
		return *this;
	}

	RawParticleEmitter3 RawParticleEmitter3::Builder::build() const
	{
		return RawParticleEmitter3(*_positions, _isOneShot);
	}

	RawParticleEmitter3Ptr RawParticleEmitter3::Builder::makeShared() const
	{
		return std::shared_ptr<RawParticleEmitter3>(
			new RawParticleEmitter3(*_positions, _isOneShot),
			[](RawParticleEmitter3* obj) { delete obj; });
	}

}