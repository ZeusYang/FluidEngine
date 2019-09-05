#pragma once

#include <cmath>
#include <algorithm>

#include "Ray2.h"
#include "BoundingBox2.h"
#include "../Math/Vector2.h"

namespace Engine
{
	//!
	//! \brief Represents 2-D rigid body transform.
	//!
	class Transform2
	{
	public:
		//! Constructs identity transform.
		Transform2();

		//! Constructs a transform with translation and orientation.
		Transform2(const Vector2D& translation, double orientation);

		//! Returns the translation.
		const Vector2D& translation() const;

		//! Sets the traslation.
		void setTranslation(const Vector2D& translation);

		//! Returns the orientation in radians.
		double orientation() const;

		//! Sets the orientation in radians.
		void setOrientation(double orientation);

		//! Transforms a point in world coordinate to the local frame.
		Vector2D toLocal(const Vector2D& pointInWorld) const;

		//! Transforms a direction in world coordinate to the local frame.
		Vector2D toLocalDirection(const Vector2D& dirInWorld) const;

		//! Transforms a ray in world coordinate to the local frame.
		Ray2D toLocal(const Ray2D& rayInWorld) const;

		//! Transforms a bounding box in world coordinate to the local frame.
		BoundingBox2D toLocal(const BoundingBox2D& bboxInWorld) const;

		//! Transforms a point in local space to the world coordinate.
		Vector2D toWorld(const Vector2D& pointInLocal) const;

		//! Transforms a direction in local space to the world coordinate.
		Vector2D toWorldDirection(const Vector2D& dirInLocal) const;

		//! Transforms a ray in local space to the world coordinate.
		Ray2D toWorld(const Ray2D& rayInLocal) const;

		//! Transforms a bounding box in local space to the world coordinate.
		BoundingBox2D toWorld(const BoundingBox2D& bboxInLocal) const;

	private:
		Vector2D _translation;
		double _orientation = 0.0;
		double _cosAngle = 1.0;
		double _sinAngle = 0.0;

	};

	//! --------------------------------Definition----------------------------

	inline Transform2::Transform2() { }

	inline Transform2::Transform2(const Vector2D& translation,double orientation)
		: _translation(translation),  _orientation(orientation) 
	{
		_cosAngle = std::cos(orientation);
		_sinAngle = std::sin(orientation);
	}

	inline const Vector2D& Transform2::translation() const { return _translation; }

	inline void Transform2::setTranslation(const Vector2D& translation) { _translation = translation; }

	inline double Transform2::orientation() const { return _orientation; }

	inline void Transform2::setOrientation(double orientation) 
	{
		_orientation = orientation;
		_cosAngle = std::cos(orientation);
		_sinAngle = std::sin(orientation);
	}

	inline Vector2D Transform2::toLocal(const Vector2D& pointInWorld) const 
	{
		// Convert to the local frame
		Vector2D xmt = pointInWorld - _translation;
		return Vector2D(_cosAngle * xmt.x + _sinAngle * xmt.y,
			-_sinAngle * xmt.x + _cosAngle * xmt.y);
	}

	inline Vector2D Transform2::toLocalDirection(const Vector2D& dirInWorld) const 
	{
		// Convert to the local frame
		return Vector2D(_cosAngle * dirInWorld.x + _sinAngle * dirInWorld.y,
			-_sinAngle * dirInWorld.x + _cosAngle * dirInWorld.y);
	}

	inline Ray2D Transform2::toLocal(const Ray2D& rayInWorld) const 
	{
		return Ray2D(toLocal(rayInWorld.origin),
			toLocalDirection(rayInWorld.direction));
	}

	inline BoundingBox2D Transform2::toLocal(
		const BoundingBox2D& bboxInWorld) const {
		BoundingBox2D bboxInLocal;
		for (int i = 0; i < 4; ++i) 
		{
			auto cornerInLocal = toLocal(bboxInWorld.corner(i));
			bboxInLocal.lowerCorner
				= min(bboxInLocal.lowerCorner, cornerInLocal);
			bboxInLocal.upperCorner
				= max(bboxInLocal.upperCorner, cornerInLocal);
		}
		return bboxInLocal;
	}

	inline Vector2D Transform2::toWorld(const Vector2D& pointInLocal) const 
	{
		// Convert to the world frame
		return Vector2D(_cosAngle * pointInLocal.x - _sinAngle * pointInLocal.y
			+ _translation.x,
			_sinAngle * pointInLocal.x + _cosAngle * pointInLocal.y
			+ _translation.y);
	}

	inline Vector2D Transform2::toWorldDirection(const Vector2D& dirInLocal) const 
	{
		// Convert to the world frame
		return Vector2D(_cosAngle * dirInLocal.x - _sinAngle * dirInLocal.y,
			_sinAngle * dirInLocal.x + _cosAngle * dirInLocal.y);
	}

	inline Ray2D Transform2::toWorld(const Ray2D& rayInLocal) const 
	{
		return Ray2D(toWorld(rayInLocal.origin),
			toWorldDirection(rayInLocal.direction));
	}

	inline BoundingBox2D Transform2::toWorld(const BoundingBox2D& bboxInLocal) const 
	{
		BoundingBox2D bboxInWorld;
		for (int i = 0; i < 4; ++i) 
		{
			auto cornerInWorld = toWorld(bboxInLocal.corner(i));
			bboxInWorld.lowerCorner
				= min(bboxInWorld.lowerCorner, cornerInWorld);
			bboxInWorld.upperCorner
				= max(bboxInWorld.upperCorner, cornerInWorld);
		}
		return bboxInWorld;
	}

}