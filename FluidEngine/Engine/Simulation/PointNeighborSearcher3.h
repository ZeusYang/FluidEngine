#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>

#include "Serialization.h"
#include "../Math/Vector3.h"
#include "../Math/ArrayAccessor1.h"

namespace Engine
{
	//!
	//! \brief Abstract base class for 3-D neighbor point searcher.
	//!
	//! This class provides interface for 3-D neighbor point searcher. For given
	//! list of points, the class builds internal cache to accelerate the search.
	//! Once built, the data structure is used to search nearby points for given
	//! origin point.
	//!
	class PointNeighborSearcher3
	{
	public:
		//! Callback function for nearby search query. The first parameter is the
		//! index of the nearby point, and the second is the position of the point.
		typedef std::function<void(size_t, const Vector3D&)> ForEachNearbyPointFunc;

		//! Default constructor.
		PointNeighborSearcher3();

		//! Destructor.
		virtual ~PointNeighborSearcher3();

		//! Returns the type name of the derived class.
		virtual std::string typeName() const = 0;

		//! Builds internal acceleration structure for given points list.
		virtual void build(const ConstArrayAccessor1<Vector3D>& points) = 0;

		//!
		//! Invokes the callback function for each nearby point around the origin
		//! within given radius.
		//!
		//! \param[in]  origin   The origin position.
		//! \param[in]  radius   The search radius.
		//! \param[in]  callback The callback function.
		//!
		virtual void forEachNearbyPoint(
			const Vector3D& origin,
			double radius,
			const ForEachNearbyPointFunc& callback) const = 0;

		//!
		//! Returns true if there are any nearby points for given origin within
		//! radius.
		//!
		//! \param[in]  origin The origin.
		//! \param[in]  radius The radius.
		//!
		//! \return     True if has nearby point, false otherwise.
		//!
		virtual bool hasNearbyPoint(const Vector3D& origin, double radius) const = 0;

		//!
		//! \brief      Creates a new instance of the object with same properties
		//!             than original.
		//!
		//! \return     Copy of this object.
		//!
		virtual std::shared_ptr<PointNeighborSearcher3> clone() const = 0;


	};

	//! Shared pointer for the PointNeighborSearcher3 type.
	typedef std::shared_ptr<PointNeighborSearcher3> PointNeighborSearcher3Ptr;

	//! Abstract base class for 3-D point neighbor searcher builders.
	class PointNeighborSearcherBuilder3 
	{
	public:
		//! Returns shared pointer of PointNeighborSearcher3 type.
		virtual PointNeighborSearcher3Ptr buildPointNeighborSearcher() const = 0;
	};

	//! Shared pointer for the PointNeighborSearcherBuilder3 type.
	typedef std::shared_ptr<PointNeighborSearcherBuilder3> PointNeighborSearcherBuilder3Ptr;


}


