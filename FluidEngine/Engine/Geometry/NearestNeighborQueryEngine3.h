#pragma once

#include <functional>

#include "../Math/Vector3.h"
#include "../Utils/Constants.h"

namespace Engine
{
	//! Nearest neighbor query result.
	template <typename T>
	struct NearestNeighborQueryResult3 
	{
		const T* item = nullptr;
		double distance = kMaxD;
	};

	//! Nearest neighbor distance measure function.
	template <typename T>
	using NearestNeighborDistanceFunc3 = std::function<double(const T&, const Vector3D&)>;

	//! Abstract base class for 3-D nearest neigbor query engine.
	template <typename T>
	class NearestNeighborQueryEngine3 
	{
	public:
		//! Returns the nearest neighbor for given point and distance measure
		//! function.
		virtual NearestNeighborQueryResult3<T> nearest(
			const Vector3D& pt,
			const NearestNeighborDistanceFunc3<T>& distanceFunc) const = 0;
	};

}
