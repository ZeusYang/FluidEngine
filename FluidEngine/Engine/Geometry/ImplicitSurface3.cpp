#include "ImplicitSurface3.h"

#include "../Utils/LevelSetUtils.h"

namespace Engine
{
	ImplicitSurface3::ImplicitSurface3(const Transform3& transform_, bool isNormalFlipped_)
		: Surface3(transform_, isNormalFlipped_) { }

	ImplicitSurface3::ImplicitSurface3(const ImplicitSurface3& other) : Surface3(other) { }

	ImplicitSurface3::~ImplicitSurface3() { }

	double ImplicitSurface3::signedDistance(const Vector3D& otherPoint) const 
	{
		double sd = signedDistanceLocal(transform.toLocal(otherPoint));
		return (isNormalFlipped) ? -sd : sd;
	}

	double ImplicitSurface3::closestDistanceLocal(const Vector3D& otherPoint) const 
	{
		return std::fabs(signedDistanceLocal(otherPoint));
	}

	bool ImplicitSurface3::isInsideLocal(const Vector3D& otherPoint) const 
	{
		return isInsideSdf(signedDistanceLocal(otherPoint));
	}
}