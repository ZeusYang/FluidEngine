#pragma once

#include <tuple>
#include <vector>

#include "ParticleEmitter3.h"

namespace Engine
{
	//!
	//! \brief 3-D particle-based emitter set.
	//!
	class ParticleEmitterSet3 final : public ParticleEmitter3
	{
	public:
		class Builder;

		//! Constructs an emitter.
		ParticleEmitterSet3();

		//! Constructs an emitter with sub-emitters.
		explicit ParticleEmitterSet3(const std::vector<ParticleEmitter3Ptr>& emitters);

		//! Destructor.
		virtual ~ParticleEmitterSet3();

		//! Adds sub-emitter.
		void addEmitter(const ParticleEmitter3Ptr& emitter);

		//! Returns builder fox ParticleEmitterSet3.
		static Builder builder();

	private:
		std::vector<ParticleEmitter3Ptr> _emitters;

		void onSetTarget(const ParticleSystemData3Ptr& particles) override;

		void onUpdate(
			double currentTimeInSeconds,
			double timeIntervalInSecond) override;

	};

	//! Shared pointer type for the ParticleEmitterSet3.
	typedef std::shared_ptr<ParticleEmitterSet3> ParticleEmitterSet3Ptr;

	//!
	//! \brief Front-end to create ParticleEmitterSet3 objects step by step.
	//!
	class ParticleEmitterSet3::Builder final 
	{
	public:
		//! Returns builder with list of sub-emitters.
		Builder& withEmitters(const std::vector<ParticleEmitter3Ptr>& emitters);

		//! Builds ParticleEmitterSet3.
		ParticleEmitterSet3 build() const;

		//! Builds shared pointer of ParticleEmitterSet3 instance.
		ParticleEmitterSet3Ptr makeShared() const;

	private:
		std::vector<ParticleEmitter3Ptr> _emitters;
	};


}
