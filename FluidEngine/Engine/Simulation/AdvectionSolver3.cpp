#include "AdvectionSolver3.h"

namespace Engine
{
	AdvectionSolver3::AdvectionSolver3() {}

	AdvectionSolver3::~AdvectionSolver3() {}

	void AdvectionSolver3::advect(
		const CollocatedVectorGrid3& source,
		const VectorField3& flow,
		double dt,
		CollocatedVectorGrid3* target,
		const ScalarField3& boundarySdf) {}

	void AdvectionSolver3::advect(
		const FaceCenteredGrid3& source,
		const VectorField3& flow,
		double dt,
		FaceCenteredGrid3* target,
		const ScalarField3& boundarySdf) {}

}