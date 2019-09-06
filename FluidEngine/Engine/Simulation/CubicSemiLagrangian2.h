#pragma once

#include "SemiLagrangian2.h"

namespace Engine
{
	//!
	//! \brief Implementation of 2-D cubic semi-Lagrangian advection solver.
	//!
	//! This class implements 3rd-order cubic 2-D semi-Lagrangian advection solver.
	//!
	class CubicSemiLagrangian2 final : public SemiLagrangian2
	{
	public:
		CubicSemiLagrangian2();

	protected:
		//!
		//! \brief Returns spatial interpolation function object for given scalar
		//! grid.
		//!
		//! This function overrides the original function with cubic interpolation.
		//!
		std::function<double(const Vector2D&)> getScalarSamplerFunc(
			const ScalarGrid2& source) const override;

		//!
		//! \brief Returns spatial interpolation function object for given
		//! collocated vector grid.
		//!
		//! This function overrides the original function with cubic interpolation.
		//!
		std::function<Vector2D(const Vector2D&)> getVectorSamplerFunc(
			const CollocatedVectorGrid2& source) const override;

		//!
		//! \brief Returns spatial interpolation function object for given
		//! face-centered vector grid.
		//!
		//! This function overrides the original function with cubic interpolation.
		//!
		std::function<Vector2D(const Vector2D&)> getVectorSamplerFunc(
			const FaceCenteredGrid2& source) const override;

	};

	typedef std::shared_ptr<CubicSemiLagrangian2> CubicSemiLagrangian2Ptr;

}
