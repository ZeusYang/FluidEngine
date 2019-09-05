#pragma once

#include <limits>
#include <algorithm>

#include "../Math/Vector.h"
#include "../Utils/MathUtils.h"

namespace Engine
{
	//!
	//! \brief Generic N-D axis-aligned bounding box class.
	//!
	//! \tparam T - Real number type.
	//! \tparam N - Dimension.
	//!
	template <typename T, size_t N>
	class BoundingBox
	{
	public:
		static_assert(
			N > 0, "Size of static-sized box should be greater than zero.");

		typedef Vector<T, N> VectorType;

		//! Lower corner of the bounding box.
		VectorType lowerCorner;

		//! Upper corner of the bounding box.
		VectorType upperCorner;

		//! Default constructor.
		BoundingBox();

		//! Constructs a box that tightly covers two points.
		BoundingBox(const VectorType& point1, const VectorType& point2);

		//! Constructs a box with other box instance.
		BoundingBox(const BoundingBox& other);

		//! Returns true of this box and other box overlaps.
		bool overlaps(const BoundingBox& other) const;

		//! Returns true if the input point is inside of this box.
		bool contains(const VectorType& point) const;

		//! Returns the mid-point of this box.
		VectorType midPoint() const;

		//! Returns diagonal length of this box.
		T diagonalLength() const;

		//! Returns squared diagonal length of this box.
		T diagonalLengthSquared() const;

		//! Resets this box to initial state (min=infinite, max=-infinite).
		void reset();

		//! Merges this and other point.
		void merge(const VectorType& point);

		//! Merges this and other boxes.
		void merge(const BoundingBox& other);

		//! Expands this box by given delta to all direction.
		//! If the width of the box was x, expand(y) will result a box with
		//! x+y+y width.
		void expand(T delta);
	};

	template <typename T, size_t N>
	BoundingBox<T, N>::BoundingBox() { reset(); }

	template <typename T, size_t N>
	BoundingBox<T, N>::BoundingBox(const VectorType& point1, const VectorType& point2) 
	{
		for (size_t i = 0; i < N; ++i) 
		{
			lowerCorner[i] = std::min(point1[i], point2[i]);
			upperCorner[i] = std::max(point1[i], point2[i]);
		}
	}

	template <typename T, size_t N>
	BoundingBox<T, N>::BoundingBox(const BoundingBox& other) :
		lowerCorner(other.lowerCorner), upperCorner(other.upperCorner) { }

	template <typename T, size_t N>
	bool BoundingBox<T, N>::overlaps(const BoundingBox& other) const 
	{
		for (size_t i = 0; i < N; ++i) 
			if (upperCorner[i] < other.lowerCorner[i]
				|| lowerCorner[i] > other.upperCorner[i]) 
				return false;
		return true;
	}

	template <typename T, size_t N>
	bool BoundingBox<T, N>::contains(const VectorType& point) const 
	{
		for (size_t i = 0; i < N; ++i) 
			if (upperCorner[i] < point[i] || lowerCorner[i] > point[i]) 
				return false;
		return true;
	}

	template <typename T, size_t N>
	Vector<T, N> BoundingBox<T, N>::midPoint() const 
	{
		Vector<T, N> result;
		for (size_t i = 0; i < N; ++i) 
			result[i] = (upperCorner[i] + lowerCorner[i]) / 2;
		return result;
	}

	template <typename T, size_t N>
	T BoundingBox<T, N>::diagonalLength() const 
	{
		T result = 0;
		for (size_t i = 0; i < N; ++i) 
			result += square(upperCorner[i] - lowerCorner[i]);
		return std::sqrt(result);
	}

	template <typename T, size_t N>
	T BoundingBox<T, N>::diagonalLengthSquared() const 
	{
		T result = 0;
		for (size_t i = 0; i < N; ++i) 
			result += square(upperCorner[i] - lowerCorner[i]);
		return result;
	}

	template <typename T, size_t N>
	void BoundingBox<T, N>::reset() 
	{
		for (size_t i = 0; i < N; ++i) 
		{
			lowerCorner[i] = std::numeric_limits<T>::max();
			upperCorner[i] = -std::numeric_limits<T>::max();
		}
	}

	template <typename T, size_t N>
	void BoundingBox<T, N>::merge(const VectorType& point) 
	{
		for (size_t i = 0; i < N; ++i) 
		{
			lowerCorner[i] = std::min(lowerCorner[i], point[i]);
			upperCorner[i] = std::max(upperCorner[i], point[i]);
		}
	}

	template <typename T, size_t N>
	void BoundingBox<T, N>::merge(const BoundingBox& other) 
	{
		for (size_t i = 0; i < N; ++i) 
		{
			lowerCorner[i] = std::min(lowerCorner[i], other.lowerCorner[i]);
			upperCorner[i] = std::max(upperCorner[i], other.upperCorner[i]);
		}
	}

	template <typename T, size_t N>
	void BoundingBox<T, N>::expand(T delta) 
	{
		for (size_t i = 0; i < N; ++i) 
		{
			lowerCorner[i] -= delta;
			upperCorner[i] += delta;
		}
	}


}