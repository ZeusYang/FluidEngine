#pragma once

#include "IterativeLevelSetSolver3.h"

namespace Engine
{
	//! Three-dimensional first-order upwind-based iterative level set solver.
	class UpwindLevelSetSolver3 final : public IterativeLevelSetSolver3
	{
	public:
		//! Default constructor.
		UpwindLevelSetSolver3();

	protected:
		//! Computes the derivatives for given grid point.
		void getDerivatives(
			ConstArrayAccessor3<double> grid,
			const Vector3D& gridSpacing, size_t i, size_t j,
			size_t k, std::array<double, 2>* dx,
			std::array<double, 2>* dy,
			std::array<double, 2>* dz) const override;

	};

	typedef std::shared_ptr<UpwindLevelSetSolver3> UpwindLevelSetSolver3Ptr;
}
