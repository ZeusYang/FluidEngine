#pragma once

#include <memory>

#include "GridFractionalBoundaryConditionSolver3.h"

namespace Engine
{
	//!
	//! \brief Blocked 3-D boundary condition solver for grids.
	//!
	//! This class constrains the velocity field by projecting the flow to the
	//! blocked representation of the collider. A collider is rasterized into voxels
	//! and each face of the collider voxels projects the velocity field onto its
	//! face. This implementation should pair up with GridSinglePhasePressureSolver3
	//! since the pressure solver assumes blocked boundary representation as well.
	//!
	class GridBlockedBoundaryConditionSolver3 final : public GridFractionalBoundaryConditionSolver3
	{
	public:
		//! Default constructor.
		GridBlockedBoundaryConditionSolver3();

		//!
		//! Constrains the velocity field to conform the collider boundary.
		//!
		//! \param velocity Input and output velocity grid.
		//! \param extrapolationDepth Number of inner-collider grid cells that
		//!     velocity will get extrapolated.
		//!
		void constrainVelocity(FaceCenteredGrid3* velocity, unsigned int extrapolationDepth = 5) override;

		//! Returns the marker which is 1 if occupied by the collider.
		const Array3<char>& marker() const;

	protected:
		//! Invoked when a new collider is set.
		void onColliderUpdated(
			const Size3& gridSize,
			const Vector3D& gridSpacing,
			const Vector3D& gridOrigin) override;

	private:
		Array3<char> _marker;
	};

	//! Shared pointer type for the GridBlockedBoundaryConditionSolver3.
	typedef std::shared_ptr<GridBlockedBoundaryConditionSolver3> GridBlockedBoundaryConditionSolver3Ptr;

}
