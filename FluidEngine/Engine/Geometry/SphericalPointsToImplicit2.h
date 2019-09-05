#pragma once

#include "PointsToImplicit2.h"

namespace Engine
{
	//!
	//! \brief 2-D points-to-implicit converter based on simple sphere model.
	//!
	class SphericalPointsToImplicit2 final : public PointsToImplicit2
	{
	public:

		//! Constructs the converter with given sphere radius.
		SphericalPointsToImplicit2(double radius = 1.0, bool isOutputSdf = true);

		//! Converts the given points to implicit surface scalar field.
		void convert(const ConstArrayAccessor1<Vector2D>& points,
			ScalarGrid2* output) const override;

	private:
		double _radius = 1.0;
		bool _isOutputSdf = true;

	};

	//! Shared pointer type for SphericalPointsToImplicit2.
	typedef std::shared_ptr<SphericalPointsToImplicit2> SphericalPointsToImplicit2Ptr;

}
