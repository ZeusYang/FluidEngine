#pragma once

#include <limits>

#include "ParticleEmitter3.h"

namespace Engine
{
	//!
	//! \brief 3-D particle emitter.
	//!
	//! This class emits particles from given particles.
	//!
	class RawParticleEmitter3 final : public ParticleEmitter3
	{
	public:
		class Builder;

		//!
		//! Constructs an emitter that spawns particles from given positions
		//!
		//! \param[in]  positions         The given positions.
		//! \param[in]  isOneShot         True if emitter gets disabled after one shot.
		//!
		RawParticleEmitter3(
			const Array1<Vector3D> &positions,
			bool isOneShot = true);

		//! Returns true if particles should be emitted just once.
		bool isOneShot() const;

		//! Returns builder fox VolumeParticleEmitter3.
		static Builder builder();

	private:
		bool _isOneShot = true;
		size_t _maxNumberOfParticles = kMaxSize;
		size_t _numberOfEmittedParticles = 0;

		Array1<Vector3D> _positions;

		//!
		//! \brief      Emits particles to the particle system data.
		//!
		//! \param[in]  currentTimeInSeconds    Current simulation time.
		//! \param[in]  timeIntervalInSeconds   The time-step interval.
		//!
		void onUpdate(
			double currentTimeInSeconds,
			double timeIntervalInSeconds) override;

		void emit(
			const ParticleSystemData3Ptr& particles,
			Array1<Vector3D>* newPositions,
			Array1<Vector3D>* newVelocities);

	};

	//! Shared pointer for the RawParticleEmitter3 type.
	typedef std::shared_ptr<RawParticleEmitter3> RawParticleEmitter3Ptr;

	//!
	//! \brief Front-end to create VolumeParticleEmitter3 objects step by step.
	//!
	class RawParticleEmitter3::Builder final
	{
	public:

		//! Returns builder with raw particles' positions.
		Builder& withPositions(Array1<Vector3D> *positions);

		//! Returns builder with one-shot flag.
		Builder& withIsOneShot(bool isOneShot);

		//! Builds VolumeParticleEmitter3.
		RawParticleEmitter3 build() const;

		//! Builds shared pointer of VolumeParticleEmitter3 instance.
		RawParticleEmitter3Ptr makeShared() const;

	private:
		bool _isOneShot = true;
		Array1<Vector3D> *_positions = nullptr;

	};

}
