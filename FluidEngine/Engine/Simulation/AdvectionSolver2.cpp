#include "AdvectionSolver2.h"

namespace Engine
{
	AdvectionSolver2::AdvectionSolver2() {}

	AdvectionSolver2::~AdvectionSolver2() {}

	void AdvectionSolver2::advect(
		const CollocatedVectorGrid2& source,
		const VectorField2& flow,
		double dt,
		CollocatedVectorGrid2* target,
		const ScalarField2& boundarySdf)  {}

	void AdvectionSolver2::advect(
		const FaceCenteredGrid2& source,
		const VectorField2& flow,
		double dt,
		FaceCenteredGrid2* target,
		const ScalarField2& boundarySdf) {}
}