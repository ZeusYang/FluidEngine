#include "GridBlockedBoundaryConditionSolver3.h"

#include <algorithm>

#include "../Utils/ArrayUtils.h"
#include "../Utils/PhysicsHelper.h"
#include "../Utils/LevelSetUtils.h"
#include "../Geometry/SurfaceToImplicit3.h"

namespace Engine
{
	static const char kFluid = 1;
	static const char kCollider = 0;

	GridBlockedBoundaryConditionSolver3::GridBlockedBoundaryConditionSolver3() {}

	void GridBlockedBoundaryConditionSolver3::constrainVelocity(
		FaceCenteredGrid3* velocity,
		unsigned int extrapolationDepth) 
	{
		GridFractionalBoundaryConditionSolver3::constrainVelocity(velocity, extrapolationDepth);

		// No-flux: project the velocity at the marker interface
		Size3 size = velocity->resolution();
		auto u = velocity->uAccessor();
		auto v = velocity->vAccessor();
		auto w = velocity->wAccessor();
		auto uPos = velocity->uPosition();
		auto vPos = velocity->vPosition();
		auto wPos = velocity->wPosition();

		_marker.forEachIndex([&](size_t i, size_t j, size_t k)
		{
			if (_marker(i, j, k) == kCollider) 
			{
				if (i > 0 && _marker(i - 1, j, k) == kFluid) 
				{
					Vector3D colliderVel = collider()->velocityAt(uPos(i, j, k));
					u(i, j, k) = colliderVel.x;
				}
				if (i < size.x - 1 && _marker(i + 1, j, k) == kFluid) 
				{
					Vector3D colliderVel = collider()->velocityAt(uPos(i + 1, j, k));
					u(i + 1, j, k) = colliderVel.x;
				}
				if (j > 0 && _marker(i, j - 1, k) == kFluid) 
				{
					Vector3D colliderVel = collider()->velocityAt(vPos(i, j, k));
					v(i, j, k) = colliderVel.y;
				}
				if (j < size.y - 1 && _marker(i, j + 1, k) == kFluid) 
				{
					Vector3D colliderVel = collider()->velocityAt(vPos(i, j + 1, k));
					v(i, j + 1, k) = colliderVel.y;
				}
				if (k > 0 && _marker(i, j, k - 1) == kFluid) 
				{
					Vector3D colliderVel = collider()->velocityAt(wPos(i, j, k));
					w(i, j, k) = colliderVel.z;
				}
				if (k < size.z - 1 && _marker(i, j, k + 1) == kFluid)
				{
					Vector3D colliderVel = collider()->velocityAt(wPos(i, j, k + 1));
					w(i, j, k + 1) = colliderVel.z;
				}
			}
		});
	}

	const Array3<char>& GridBlockedBoundaryConditionSolver3::marker() const { return _marker; }

	void GridBlockedBoundaryConditionSolver3::onColliderUpdated(
		const Size3& gridSize,
		const Vector3D& gridSpacing,
		const Vector3D& gridOrigin) 
	{
		GridFractionalBoundaryConditionSolver3::onColliderUpdated(gridSize, gridSpacing, gridOrigin);

		const auto sdf = std::dynamic_pointer_cast<CellCenteredScalarGrid3>(colliderSdf());

		_marker.resize(gridSize);
		_marker.parallelForEachIndex([&](size_t i, size_t j, size_t k) 
		{
			if (isInsideSdf((*sdf)(i, j, k))) 
				_marker(i, j, k) = kCollider;
			else 
				_marker(i, j, k) = kFluid;
		});
	}

}
