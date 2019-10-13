#include "AnisotropicPointsToImplicit3.h"

#include "../Simulation/SphKernels3.h"
#include "../Simulation/SphSystemData3.h"

namespace Engine
{
	AnisotropicPointsToImplicit3::AnisotropicPointsToImplicit3(double kernelRadius, double cutOffDensity,
		double positionSmoothingFactor, size_t minNumNeighbors, bool isOutputSdf) : 
		_kernelRadius(kernelRadius),
		_cutOffDensity(cutOffDensity),
		_positionSmoothingFactor(positionSmoothingFactor),
		_minNumNeighbors(minNumNeighbors),
		_isOutputSdf(isOutputSdf) {}

	void AnisotropicPointsToImplicit3::convert(const ConstArrayAccessor1<Vector3D>& points, ScalarGrid3 * output) const
	{

	}
}