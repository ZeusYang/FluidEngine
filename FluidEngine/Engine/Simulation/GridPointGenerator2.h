#pragma once

#include "PointGenerator2.h"

namespace Engine
{
	//!
	//! \brief 2-D regular-grid point generator.
	//!
	class GridPointGenerator2 final : public PointGenerator2
	{
	public:
		//!
		//! \brief Invokes \p callback function for each regular grid points inside
		//! \p boundingBox.
		//!
		//! This function iterates every regular grid points inside \p boundingBox
		//! where \p spacing is the size of the unit cell of regular grid structure.
		//!
		void forEachPoint(
			const BoundingBox2D& boundingBox,
			double spacing,
			const std::function<bool(const Vector2D&)>& callback) const;

	};

	//! Shared pointer type for the GridPointGenerator2.
	typedef std::shared_ptr<GridPointGenerator2> GridPointGenerator2Ptr;

}
