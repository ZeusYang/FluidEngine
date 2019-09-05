#pragma once

#include <memory>

#include "ScalarGrid3.h"
#include "../Math/Vector3.h"
#include "../Math/ArrayAccessor1.h"

namespace Engine
{
	//! Abstract base class for 3-D points-to-implicit converters.
	class PointsToImplicit3
	{
	public:
		//! Default constructor.
		PointsToImplicit3();

		//! Default destructor.
		virtual ~PointsToImplicit3();

		//! Converts the given points to implicit surface scalar field.
		virtual void convert(const ConstArrayAccessor1<Vector3D>& points, ScalarGrid3* output) const = 0;

	};

	//! Shared pointer for the PointsToImplicit3 type.
	typedef std::shared_ptr<PointsToImplicit3> PointsToImplicit3Ptr;
}
