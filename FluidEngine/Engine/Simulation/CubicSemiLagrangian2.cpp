#include "CubicSemiLagrangian2.h"

#include "../Math/ArraySamplers2.h"

namespace Engine
{
	CubicSemiLagrangian2::CubicSemiLagrangian2() {}

	std::function<double(const Vector2D&)>
		CubicSemiLagrangian2::getScalarSamplerFunc(const ScalarGrid2& source) const
	{
		auto sourceSampler = CubicArraySampler2<double, double>(source.constDataAccessor(),
			source.gridSpacing(), source.dataOrigin());
		return sourceSampler.functor();
	}

	std::function<Vector2D(const Vector2D&)>
		CubicSemiLagrangian2::getVectorSamplerFunc(const CollocatedVectorGrid2& source) const 
	{
		auto sourceSampler = CubicArraySampler2<Vector2D, double>(source.constDataAccessor(),
			source.gridSpacing(), source.dataOrigin());
		return sourceSampler.functor();
	}

	std::function<Vector2D(const Vector2D&)>
		CubicSemiLagrangian2::getVectorSamplerFunc(const FaceCenteredGrid2& source) const 
	{
		auto uSourceSampler = CubicArraySampler2<double, double>(source.uConstAccessor(),
			source.gridSpacing(), source.uOrigin());
		auto vSourceSampler = CubicArraySampler2<double, double>(source.vConstAccessor(),
			source.gridSpacing(), source.vOrigin());
		return [uSourceSampler, vSourceSampler](const Vector2D& x) 
		{
			return Vector2D(uSourceSampler(x), vSourceSampler(x));
		};
	}

}