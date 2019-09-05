#pragma once

#include <algorithm>

#include "Vector2.h"
#include "Vector3.h"
#include "../Utils/MathUtils.h"
#include "../Utils/Constants.h"

namespace Engine
{
	//!
	//! \brief      Returns randomly sampled direction within a cone.
	//!
	//! For a given cone, defined by axis and angle, this function returns a sampled
	//! direction vector within the cone.
	//!
	//! \param[in]  u1    First random sample.
	//! \param[in]  u2    Second random sample.
	//! \param[in]  axis  The axis of the cone.
	//! \param[in]  angle The angle of the cone.
	//!
	//! \tparam     T     Real number type.
	//!
	//! \return     Sampled direction vector.
	//!
	template <typename T>
	inline Vector3<T> uniformSampleCone(T u1, T u2, const Vector3<T>& axis, T angle);

	//!
	//! \brief      Returns randomly sampled point within a unit hemisphere.
	//!
	//! For a given unit hemisphere, defined by center normal vector, this function
	//! returns a point within the hemisphere.
	//!
	//! \param[in]  u1      First random sample.
	//! \param[in]  u2      Second random sample.
	//! \param[in]  normal  The center normal of the hemisphere.
	//!
	//! \tparam     T       Real number type.
	//!
	//! \return     Sampled point.
	//!
	template <typename T>
	inline Vector3<T> uniformSampleHemisphere(T u1, T u2, const Vector3<T>& normal);

	//!
	//! \brief      Returns weighted sampled point on a hemisphere.
	//!
	//! For a given hemisphere, defined by center normal vector, this function
	//! returns a point on the hemisphere, where the probability is
	//! consine-weighted.
	//!
	//! \param[in]  u1      First random sample.
	//! \param[in]  u2      Second random sample.
	//! \param[in]  normal  The center normal of the hemisphere.
	//!
	//! \tparam     T       Real number type.
	//!
	//! \return     Sampled point.
	//!
	template <typename T>
	inline Vector3<T> cosineWeightedSampleHemisphere(T u1, T u2, const Vector3<T>& normal);

	//!
	//! \brief      Returns randomly a point on a sphere.
	//!
	//! For a given sphere, defined by center normal vector, this function returns a
	//! point on the sphere.
	//!
	//! \param[in]  u1    First random sample.
	//! \param[in]  u2    Second random sample.
	//! \param[in]  axis  The axis of the cone.
	//! \param[in]  angle The angle of the cone.
	//!
	//! \tparam     T     Real number type.
	//!
	//! \return     Sampled point.
	//!
	template <typename T>
	inline Vector3<T> uniformSampleSphere(T u1, T u2);

	//!
	//! \brief      Returns randomly a point on a disk.
	//!
	//! For a given disk, this function returns a point on the disk.
	//!
	//! \param[in]  u1    First random sample.
	//! \param[in]  u2    Second random sample.
	//!
	//! \tparam     T     Real number type.
	//!
	//! \return     Sampled point.
	//!
	template <typename T>
	inline Vector2<T> uniformSampleDisk(T u1, T u2);

	//! ----------------------------------Definition-----------------------------------------

	template <typename T>
	inline Vector3<T> uniformSampleCone(T u1, T u2, const Vector3<T>& axis, T angle) 
	{
		T cosAngle_2 = std::cos(angle / 2);
		T y = 1 - (1 - cosAngle_2) * u1;
		T r = std::sqrt(std::max<T>(0, 1 - y * y));
		T phi = twoPi<T>() * u2;
		T x = r * std::cos(phi);
		T z = r * std::sin(phi);
		auto ts = axis.tangential();
		return std::get<0>(ts) * x + axis * y + std::get<1>(ts) * z;
	}

	template <typename T>
	inline Vector3<T> uniformSampleHemisphere(T u1, T u2, const Vector3<T>& normal) 
	{
		T y = u1;
		T r = std::sqrt(std::max<T>(0, 1 - y * y));
		T phi = twoPi<T>() * u2;
		T x = r * std::cos(phi);
		T z = r * std::sin(phi);
		auto ts = normal.tangential();
		return std::get<0>(ts) * x + normal * y + std::get<1>(ts) * z;
	}

	template <typename T>
	inline Vector3<T> cosineWeightedSampleHemisphere(T u1, T u2, const Vector3<T> &normal) 
	{
		T phi = twoPi<T>()*u1;
		T y = std::sqrt(u2);
		T theta = std::acos(y);
		T x = std::cos(phi) * std::sin(theta);
		T z = std::sin(phi) * std::sin(theta);
		Vector3<T> t = tangential(normal);
		auto ts = normal.tangential();
		return std::get<0>(ts) * x + normal * y + std::get<1>(ts) * z;
	}

	template <typename T>
	inline Vector3<T> uniformSampleSphere(T u1, T u2) 
	{
		T y = 1 - 2 * u1;
		T r = std::sqrt(std::max<T>(0, 1 - y * y));
		T phi = twoPi<T>() * u2;
		T x = r * std::cos(phi);
		T z = r * std::sin(phi);
		return Vector3<T>(x, y, z);
	}

	template <typename T>
	inline Vector2<T> uniformSampleDisk(T u1, T u2) 
	{
		T r = std::sqrt(u1);
		T theta = twoPi<T>() * u2;
		return Vector2<T>(r * std::cos(theta), r * std::sin(theta));
	}

}