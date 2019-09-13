#pragma once

#include <memory>

#include "../Geometry/ScalarGrid2.h"
#include "../Geometry/FaceCenteredGrid2.h"
#include "../Geometry/CollocatedVectorGrid2.h"

namespace Engine
{
	//! Abstract base class for 2-D level set solver.
	class LevelSetSolver2
	{
	public:
		//! Default constructor.
		LevelSetSolver2() = default;

		//! Default destructor.
		virtual ~LevelSetSolver2() = default;

		//!
		//! Reinitializes given scalar field to signed-distance field.
		//!
		//! \param inputSdf Input signed-distance field which can be distorted.
		//! \param maxDistance Max range of reinitialization.
		//! \param outputSdf Output signed-distance field.
		//!
		virtual void reinitialize(
			const ScalarGrid2& inputSdf,
			double maxDistance,
			ScalarGrid2* outputSdf) = 0;

		//!
		//! Extrapolates given scalar field from negative to positive SDF region.
		//!
		//! \param input Input scalar field to be extrapolated.
		//! \param sdf Reference signed-distance field.
		//! \param maxDistance Max range of extrapolation.
		//! \param output Output scalar field.
		//!
		virtual void extrapolate(
			const ScalarGrid2& input,
			const ScalarField2& sdf,
			double maxDistance,
			ScalarGrid2* output) = 0;

		//!
		//! Extrapolates given collocated vector field from negative to positive SDF
		//! region.
		//!
		//! \param input Input collocated vector field to be extrapolated.
		//! \param sdf Reference signed-distance field.
		//! \param maxDistance Max range of extrapolation.
		//! \param output Output collocated vector field.
		//!
		virtual void extrapolate(
			const CollocatedVectorGrid2& input,
			const ScalarField2& sdf,
			double maxDistance,
			CollocatedVectorGrid2* output) = 0;

		//!
		//! Extrapolates given face-centered vector field from negative to positive
		//! SDF region.
		//!
		//! \param input Input face-centered field to be extrapolated.
		//! \param sdf Reference signed-distance field.
		//! \param maxDistance Max range of extrapolation.
		//! \param output Output face-centered vector field.
		//!
		virtual void extrapolate(
			const FaceCenteredGrid2& input,
			const ScalarField2& sdf,
			double maxDistance,
			FaceCenteredGrid2* output) = 0;

	};

	//! Shared pointer type for the LevelSetSolver2.
	typedef std::shared_ptr<LevelSetSolver2> LevelSetSolver2Ptr;
}
