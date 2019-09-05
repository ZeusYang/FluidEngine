#pragma once

#include <functional>

#include "../Math/Vector2.h"

namespace Engine
{
	//! Nearest neighbor query result.
	template <typename T>
	struct NearestNeighborQueryResult2 
	{
		const T* item = nullptr;
		double distance = kMaxD;
	};

	//! Nearest neighbor distance measure function.
	template <typename T>
	using NearestNeighborDistanceFunc2 = std::function<double(const T&, const Vector2D&)>;

	//! Abstract base class for 2-D nearest neigbor query engine.
	template <typename T>
	class NearestNeighborQueryEngine2 
	{
	public:
		//! Returns the nearest neighbor for given point and distance measure
		//! function.
		virtual NearestNeighborQueryResult2<T> nearest(
			const Vector2D& pt,
			const NearestNeighborDistanceFunc2<T>& distanceFunc) const = 0;
	};

}