#pragma once

#include <limits>

#include "Ray2.h"
#include "BoundingBox.h"
#include "../Math/Vector2.h"

namespace Engine
{
	//!
	//! \brief      2-D box-ray intersection result.
	//!
	//! \tparam     T     The value type.
	//!
	template <typename T>
	struct BoundingBoxRayIntersection2
	{
		//! True if the box and ray intersects.
		bool isIntersecting = false;

		//! Distance to the first intersection point.
		T tNear = std::numeric_limits<T>::max();

		//! Distance to the second (and the last) intersection point.
		T tFar = std::numeric_limits<T>::max();
	};

	//!
	//! \brief 2-D axis-aligned bounding box class.
	//!
	//! \tparam T - Real number type.
	//! \tparam N - Dimension.
	//!
	template <typename T>
	class BoundingBox<T, 2>
	{
	public:

		//! Lower corner of the bounding box.
		Vector2<T> lowerCorner;

		//! Upper corner of the bounding box.
		Vector2<T> upperCorner;

		//! Default constructor.
		BoundingBox();

		//! Constructs a box that tightly covers two points.
		BoundingBox(const Vector2<T>& point1, const Vector2<T>& point2);

		//! Constructs a box with other box instance.
		BoundingBox(const BoundingBox& other);

		//! Returns width of the box.
		T width() const;

		//! Returns height of the box.
		T height() const;

		//! Returns length of the box in given axis.
		T length(size_t axis);

		//! Returns true of this box and other box overlaps.
		bool overlaps(const BoundingBox& other) const;

		//! Returns true if the input point is inside of this box.
		bool contains(const Vector2<T>& point) const;

		//! Returns true if the input ray is intersecting with this box.
		bool intersects(const Ray2<T>& ray) const;

		//! Returns intersection.isIntersecting = true if the input ray is
		//! intersecting with this box. If interesects, intersection.tNear is
		//! assigned with distant to the closest intersecting point, and
		//! intersection.tFar with furthest.
		BoundingBoxRayIntersection2<T> closestIntersection(const Ray2<T>& ray) const;

		//! Returns the mid-point of this box.
		Vector2<T> midPoint() const;

		//! Returns diagonal length of this box.
		T diagonalLength() const;

		//! Returns squared diagonal length of this box.
		T diagonalLengthSquared() const;

		//! Resets this box to initial state (min=infinite, max=-infinite).
		void reset();

		//! Merges this and other point.
		void merge(const Vector2<T>& point);

		//! Merges this and other box.
		void merge(const BoundingBox& other);

		//! Expands this box by given delta to all direction.
		//! If the width of the box was x, expand(y) will result a box with
		//! x+y+y width.
		void expand(T delta);

		//! Returns corner position. Index starts from x-first order.
		Vector2<T> corner(size_t idx) const;

		//! Returns the clamped point.
		Vector2<T> clamp(const Vector2<T>& pt) const;

		//! Returns true if the box is empty.
		bool isEmpty() const;

	};

	//! Type alias for 2-D BoundingBox.
	template <typename T>
	using BoundingBox2 = BoundingBox<T, 2>;

	//! Float-type 2-D BoundingBox.
	typedef BoundingBox2<float> BoundingBox2F;

	//! Double-type 2-D BoundingBox.
	typedef BoundingBox2<double> BoundingBox2D;

	//! Float-type 2-D box-ray intersection result.
	typedef BoundingBoxRayIntersection2<float> BoundingBoxRayIntersection2F;

	//! Double-type 2-D box-ray intersection result.
	typedef BoundingBoxRayIntersection2<double> BoundingBoxRayIntersection2D;

	template <typename T>
	BoundingBox<T, 2>::BoundingBox() { reset(); }

	template <typename T>
	BoundingBox<T, 2>::BoundingBox(const Vector2<T>& point1, const Vector2<T>& point2) 
	{
		lowerCorner.x = std::min(point1.x, point2.x);
		lowerCorner.y = std::min(point1.y, point2.y);
		upperCorner.x = std::max(point1.x, point2.x);
		upperCorner.y = std::max(point1.y, point2.y);
	}

	template <typename T>
	BoundingBox<T, 2>::BoundingBox(const BoundingBox& other)
		: lowerCorner(other.lowerCorner), upperCorner(other.upperCorner) {}

	template <typename T>
	T BoundingBox<T, 2>::width() const { return upperCorner.x - lowerCorner.x; }

	template <typename T>
	T BoundingBox<T, 2>::height() const { return upperCorner.y - lowerCorner.y; }

	template <typename T>
	T BoundingBox<T, 2>::length(size_t axis) {
		return upperCorner[axis] - lowerCorner[axis];
	}

	template <typename T>
	bool BoundingBox<T, 2>::overlaps(const BoundingBox& other) const 
	{
		if (upperCorner.x < other.lowerCorner.x ||
			lowerCorner.x > other.upperCorner.x) 
			return false;

		if (upperCorner.y < other.lowerCorner.y ||
			lowerCorner.y > other.upperCorner.y)
			return false;

		return true;
	}

	template <typename T>
	bool BoundingBox<T, 2>::contains(const Vector2<T>& point) const 
	{
		if (upperCorner.x < point.x || lowerCorner.x > point.x) 
			return false;

		if (upperCorner.y < point.y || lowerCorner.y > point.y) 
			return false;

		return true;
	}

	template <typename T>
	bool BoundingBox<T, 2>::intersects(const Ray2<T>& ray) const 
	{
		//Slabs method.
		T tMin = 0;
		T tMax = std::numeric_limits<T>::max();

		const Vector2<T>& rayInvDir = ray.direction.rdiv(1);

		for (int i = 0; i < 2; ++i) 
		{
			T tNear = (lowerCorner[i] - ray.origin[i]) * rayInvDir[i];
			T tFar = (upperCorner[i] - ray.origin[i]) * rayInvDir[i];

			if (tNear > tFar) 
				std::swap(tNear, tFar);

			tMin = std::max(tNear, tMin);
			tMax = std::min(tFar, tMax);

			if (tMin > tMax) 
				return false;
		}

		return true;
	}

	template <typename T>
	BoundingBoxRayIntersection2<T> BoundingBox<T, 2>::closestIntersection(const Ray2<T>& ray) const 
	{
		BoundingBoxRayIntersection2<T> intersection;

		T tMin = 0;
		T tMax = std::numeric_limits<T>::max();

		const Vector2<T>& rayInvDir = ray.direction.rdiv(1);

		for (int i = 0; i < 2; ++i) 
		{
			T tNear = (lowerCorner[i] - ray.origin[i]) * rayInvDir[i];
			T tFar = (upperCorner[i] - ray.origin[i]) * rayInvDir[i];

			if (tNear > tFar) 
				std::swap(tNear, tFar);

			tMin = std::max(tNear, tMin);
			tMax = std::min(tFar, tMax);

			if (tMin > tMax) 
			{
				intersection.isIntersecting = false;
				return intersection;
			}
		}

		intersection.isIntersecting = true;

		if (contains(ray.origin)) 
		{
			intersection.tNear = tMax;
			intersection.tFar = std::numeric_limits<T>::max();
		}
		else 
		{
			intersection.tNear = tMin;
			intersection.tFar = tMax;
		}

		return intersection;
	}

	template <typename T>
	Vector2<T> BoundingBox<T, 2>::midPoint() const 
	{
		return (upperCorner + lowerCorner) / static_cast<T>(2);
	}

	template <typename T>
	T BoundingBox<T, 2>::diagonalLength() const 
	{
		return (upperCorner - lowerCorner).length();
	}

	template <typename T>
	T BoundingBox<T, 2>::diagonalLengthSquared() const 
	{
		return (upperCorner - lowerCorner).lengthSquared();
	}

	template <typename T>
	void BoundingBox<T, 2>::reset() 
	{
		lowerCorner.x = std::numeric_limits<T>::max();
		lowerCorner.y = std::numeric_limits<T>::max();
		upperCorner.x = -std::numeric_limits<T>::max();
		upperCorner.y = -std::numeric_limits<T>::max();
	}

	template <typename T>
	void BoundingBox<T, 2>::merge(const Vector2<T>& point) 
	{
		lowerCorner.x = std::min(lowerCorner.x, point.x);
		lowerCorner.y = std::min(lowerCorner.y, point.y);
		upperCorner.x = std::max(upperCorner.x, point.x);
		upperCorner.y = std::max(upperCorner.y, point.y);
	}

	template <typename T>
	void BoundingBox<T, 2>::merge(const BoundingBox& other) 
	{
		lowerCorner.x = std::min(lowerCorner.x, other.lowerCorner.x);
		lowerCorner.y = std::min(lowerCorner.y, other.lowerCorner.y);
		upperCorner.x = std::max(upperCorner.x, other.upperCorner.x);
		upperCorner.y = std::max(upperCorner.y, other.upperCorner.y);
	}

	template <typename T>
	void BoundingBox<T, 2>::expand(T delta) 
	{
		lowerCorner -= delta;
		upperCorner += delta;
	}

	template <typename T>
	Vector2<T> BoundingBox<T, 2>::corner(size_t idx) const 
	{
		static const T h = static_cast<T>(1) / 2;
		static const Vector2<T> offset[4] = {
			{-h, -h}, {+h, -h}, {-h, +h}, {+h, +h} };
		return Vector2<T>(width(), height()) * offset[idx] + midPoint();
	}

	template <typename T>
	Vector2<T> BoundingBox<T, 2>::clamp(const Vector2<T>& pt) const 
	{
		return Engine::clamp(pt, lowerCorner, upperCorner);
	}

	template <typename T>
	bool BoundingBox<T, 2>::isEmpty() const 
	{
		return (lowerCorner.x >= upperCorner.x || lowerCorner.y >= upperCorner.y);
	}


}