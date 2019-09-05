#pragma once


#include "Surface3.h"

namespace Engine
{
	//! Abstract base class for 3-D implicit surface.
	class ImplicitSurface3 : public Surface3
	{
	public:

		//! Default constructor.
		ImplicitSurface3(const Transform3& transform = Transform3(), bool isNormalFlipped = false);

		//! Copy constructor.
		ImplicitSurface3(const ImplicitSurface3& other);

		//! Default destructor.
		virtual ~ImplicitSurface3();

		//! Returns signed distance from the given point \p otherPoint.
		double signedDistance(const Vector3D& otherPoint) const;

	protected:
		//! Returns signed distance from the given point \p otherPoint in local
		//! space.
		virtual double signedDistanceLocal(const Vector3D& otherPoint) const = 0;

	private:
		double closestDistanceLocal(const Vector3D& otherPoint) const override;

		bool isInsideLocal(const Vector3D& otherPoint) const override;

	};

	//! Shared pointer type for the ImplicitSurface3.
	typedef std::shared_ptr<ImplicitSurface3> ImplicitSurface3Ptr;

}