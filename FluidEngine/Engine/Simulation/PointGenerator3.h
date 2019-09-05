#pragma once

#include <memory>
#include <functional>

#include "../Math/Array1.h"
#include "../Geometry/BoundingBox3.h"

namespace Engine
{
	//!
	//! \brief Abstract base class for 3-D point generator.
	//!
	//! This class provides interface for 3-D point generator. For given bounding
	//! box and point spacing, the inherited classes generates points with specified
	//! pattern.
	//!
	class PointGenerator3
	{
	public:
		PointGenerator3();

		virtual ~PointGenerator3();

		//! Generates points to output array \p points inside given \p boundingBox
		//! with target point \p spacing.
		void generate(
			const BoundingBox3D& boundingBox,
			double spacing,
			Array1<Vector3D>* points) const;

		//!
		//! \brief Iterates every point within the bounding box with specified
		//! point pattern and invokes the callback function.
		//!
		//! This function iterates every point within the bounding box and invokes
		//! the callback function. The position of the point is specified by the
		//! actual implementation. The suggested spacing between the points are
		//! given by \p spacing. The input parameter of the callback function is
		//! the position of the point and the return value tells whether the
		//! iteration should stop or not.
		//!
		virtual void forEachPoint(
			const BoundingBox3D& boundingBox,
			double spacing,
			const std::function<bool(const Vector3D&)>& callback) const = 0;

	};

	//! Shared pointer for the PointGenerator3 type.
	typedef std::shared_ptr<PointGenerator3> PointGenerator3Ptr;

}

