#pragma once

#include "Ray.h"
#include "../Math/Vector2.h"

namespace Engine
{
	//!
	//! \brief      Class for 2-D ray.
	//!
	//! \tparam     T     The value type.
	//!
	template <typename T>
	class Ray<T, 2> final
	{
	public:
		static_assert(
			std::is_floating_point<T>::value,
			"Ray only can be instantiated with floating point types");

		//! The origin of the ray.
		Vector2<T> origin;

		//! The direction of the ray.
		Vector2<T> direction;

		//! Constructs an empty ray that points (1, 0) from (0, 0).
		Ray();

		//! Constructs a ray with given origin and riection.
		Ray(const Vector2<T>& newOrigin, const Vector2<T>& newDirection);

		//! Copy constructor.
		Ray(const Ray& other);

		//! Returns a point on the ray at distance \p t.
		Vector2<T> pointAt(T t) const;

	};

	//! Type alias for 2-D ray.
	template <typename T> using Ray2 = Ray<T, 2>;

	//! Float-type 2-D ray.
	typedef Ray2<float> Ray2F;

	//! Double-type 2-D ray.
	typedef Ray2<double> Ray2D;

	//! ------------------------------Definition--------------------------------

	template <typename T>
	Ray<T, 2>::Ray() : Ray(Vector2<T>(), Vector2<T>(1, 0)) { }

	template <typename T>
	Ray<T, 2>::Ray(const Vector2<T>& newOrigin,const Vector2<T>& newDirection) :
		origin(newOrigin), direction(newDirection.normalized()) { }

	template <typename T>
	Ray<T, 2>::Ray(const Ray& other) : origin(other.origin), direction(other.direction) { }

	template <typename T>
	Vector2<T> Ray<T, 2>::pointAt(T t) const { return origin + t * direction; }

}