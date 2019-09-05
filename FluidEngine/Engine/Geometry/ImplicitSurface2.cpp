#include "ImplicitSurface2.h"

#include "../Utils/LevelSetUtils.h"

namespace Engine
{
	ImplicitSurface2::ImplicitSurface2(const Transform2& transform, bool isNormalFlipped)
		: Surface2(transform, isNormalFlipped) { }

	ImplicitSurface2::ImplicitSurface2(const ImplicitSurface2& other) : Surface2(other) { }

	ImplicitSurface2::~ImplicitSurface2() { }

	double ImplicitSurface2::signedDistance(const Vector2D& otherPoint) const 
	{
		double sd = signedDistanceLocal(transform.toLocal(otherPoint));
		return (isNormalFlipped) ? -sd : sd;
	}

	double ImplicitSurface2::closestDistanceLocal(const Vector2D& otherPoint) const 
	{
		return std::fabs(signedDistanceLocal(otherPoint));
	}

	bool ImplicitSurface2::isInsideLocal(const Vector2D& otherPoint) const 
	{
		return isInsideSdf(signedDistanceLocal(otherPoint));
	}
}