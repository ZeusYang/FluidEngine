#pragma once

#include <limits>
#include <functional>

#include "ArraySamplers.h"
#include "ArrayAccessor1.h"
#include "../Utils/Macros.h"
#include "../Utils/MathUtils.h"

namespace Engine
{
	//!
	//! \brief 1-D nearest array sampler class.
	//!
	//! This class provides nearest sampling interface for a given 1-D array.
	//!
	//! \tparam T - The value type to sample.
	//! \tparam R - The real number type.
	//!
	template <typename T, typename R>
	class NearestArraySampler<T, R, 1> final
	{
	public:
		std::is_floating_point<R>::value, "Samplers only can be instantiated with floating point types");

		//!
		//! \brief      Constructs a sampler using array accessor, spacing between
		//!     the elements, and the position of the first array element.
		//!
		//! \param[in]  accessor    The array accessor.
		//! \param[in]  gridSpacing The grid spacing.
		//! \param[in]  gridOrigin  The grid origin.
		//!
		explicit NearestArraySampler(const ConstArrayAccessor1<T>& accessor, R gridSpacing, R gridOrigin);

		//! Copy constructor.
		NearestArraySampler(const NearestArraySampler& other);

		//! Returns sampled value at point \p pt.
		T operator()(R pt) const;

		//! Returns the nearest array index for point \p x.
		void getCoordinate(R x, size_t* i) const;

		//! Returns a funtion object that wraps this instance.
		std::function<T(R)> functor() const;

	private:
		R _gridSpacing;
		R _origin;
		ConstArrayAccessor1<T> _accessor;
	};

	//! Type alias for 1-D nearest array sampler.
	template <typename T, typename R> using NearestArraySampler1 = NearestArraySampler<T, R, 1>;

	//!
	//! \brief 1-D linear array sampler class.
	//!
	//! This class provides linear sampling interface for a given 1-D array.
	//!
	//! \tparam T - The value type to sample.
	//! \tparam R - The real number type.
	//!
	template <typename T, typename R>
	class LinearArraySampler<T, R, 1> final
	{
	public:
		static_assert(std::is_floating_point<R>::value, "Samplers only can be instantiated with floating point types");

		//!
		//! \brief      Constructs a sampler using array accessor, spacing between
		//!     the elements, and the position of the first array element.
		//!
		//! \param[in]  accessor    The array accessor.
		//! \param[in]  gridSpacing The grid spacing.
		//! \param[in]  gridOrigin  The grid origin.
		//!
		explicit LinearArraySampler(const ConstArrayAccessor1<T>& accessor, R gridSpacing, R gridOrigin);

		//! Copy constructor.
		LinearArraySampler(const LinearArraySampler& other);

		//! Returns sampled value at point \p pt.
		T operator()(R pt) const;

		//! Returns the indices of points and their sampling weight for given point.
		void getCoordinatesAndWeights(R x, size_t* i0, size_t* i1, T* weight0, T* weight1) const;

		//! Returns a funtion object that wraps this instance.
		std::function<T(R)> functor() const;

	private:
		R _gridSpacing;
		R _origin;
		ConstArrayAccessor1<T> _accessor;

	};

	//! Type alias for 1-D linear array sampler.
	template <typename T, typename R> using LinearArraySampler1 = LinearArraySampler<T, R, 1>;

	//!
	//! \brief 1-D cubic array sampler class.
	//!
	//! This class provides cubic sampling interface for a given 1-D array.
	//!
	//! \tparam T - The value type to sample.
	//! \tparam R - The real number type.
	//!
	template <typename T, typename R>
	class CubicArraySampler<T, R, 1> final
	{
	public:

		static_assert(std::is_floating_point<R>::value, "Samplers only can be instantiated with floating point types");

		//!
		//! \brief      Constructs a sampler using array accessor, spacing between
		//!     the elements, and the position of the first array element.
		//!
		//! \param[in]  accessor    The array accessor.
		//! \param[in]  gridSpacing The grid spacing.
		//! \param[in]  gridOrigin  The grid origin.
		//!
		explicit CubicArraySampler(const ConstArrayAccessor1<T>& accessor, R gridSpacing, R gridOrigin);

		//! Copy constructor.
		CubicArraySampler(const CubicArraySampler& other);

		//! Returns sampled value at point \p pt.
		T operator()(R pt) const;

		//! Returns a funtion object that wraps this instance.
		std::function<T(R)> functor() const;

	private:
		R _gridSpacing;
		R _origin;
		ConstArrayAccessor1<T> _accessor;

	};

	//! Type alias for 1-D cubic array sampler.
	template <typename T, typename R> using CubicArraySampler1 = CubicArraySampler<T, R, 1>;

	//! -------------------------------------Definition-----------------------------------------------------

	template <typename T, typename R>
	NearestArraySampler<T, R, 1>::NearestArraySampler(const ConstArrayAccessor1<T>& accessor,
		R gridSpacing, R gridOrigin) 
	{
		_gridSpacing = gridSpacing;
		_origin = gridOrigin;
		_accessor = accessor;
	}

	template <typename T, typename R>
	NearestArraySampler<T, R, 1>::NearestArraySampler(const NearestArraySampler& other) 
	{
		_origin = other._origin;
		_gridSpacing = other._gridSpacing;
		_accessor = other._accessor;
	}

	template <typename T, typename R>
	T NearestArraySampler<T, R, 1>::operator()(R x) const 
	{
		// ??? bug.
		ssize_t i;
		R fx;

		assert(_gridSpacing > std::numeric_limits<R>::epsilon());
		R normalizedX = (x - _origin) / _gridSpacing;

		ssize_t iSize = static_cast<ssize_t>(_accessor.size());

		getBarycentric(normalizedX, 0, iSize - 1, &i, &fx);

		i = std::min(static_cast<ssize_t>(i + fx + 0.5), iSize - 1);

		return _accessor[i];
	}

	template <typename T, typename R>
	void NearestArraySampler<T, R, 1>::getCoordinate(R x, size_t* i) const 
	{
		R fx;

		assert(_gridSpacing > std::numeric_limits<R>::epsilon());
		R normalizedX = (x - _origin) / _gridSpacing;

		ssize_t iSize = static_cast<ssize_t>(_accessor.size());

		ssize_t _i;
		getBarycentric(normalizedX, 0, iSize - 1, &_i, &fx);

		*i = std::min(static_cast<ssize_t>(_i + fx + 0.5), iSize - 1);
	}

	template <typename T, typename R>
	std::function<T(R)> NearestArraySampler<T, R, 1>::functor() const 
	{
		NearestArraySampler sampler(*this);
		return std::bind(&NearestArraySampler::operator(), sampler, std::placeholders::_1);
	}

	template <typename T, typename R>
	LinearArraySampler<T, R, 1>::LinearArraySampler(const ConstArrayAccessor1<T>& accessor,
		R gridSpacing, R gridOrigin) 
	{
		_gridSpacing = gridSpacing;
		_origin = gridOrigin;
		_accessor = accessor;
	}

	template <typename T, typename R>
	LinearArraySampler<T, R, 1>::LinearArraySampler(const LinearArraySampler& other)
	{
		_gridSpacing = other._gridSpacing;
		_origin = other._origin;
		_accessor = other._accessor;
	}

	template <typename T, typename R>
	T LinearArraySampler<T, R, 1>::operator()(R x) const 
	{
		ssize_t i;
		R fx;

		assert(_gridSpacing > std::numeric_limits<R>::epsilon());
		R normalizedX = (x - _origin) / _gridSpacing;

		ssize_t iSize = static_cast<ssize_t>(_accessor.size());

		getBarycentric(normalizedX, 0, iSize - 1, &i, &fx);

		ssize_t ip1 = std::min(i + 1, iSize - 1);

		return lerp(_accessor[i], _accessor[ip1], fx);
	}

	template <typename T, typename R>
	void LinearArraySampler<T, R, 1>::getCoordinatesAndWeights(R x, size_t* i0, size_t* i1, T* weight0, T* weight1) const
	{
		ssize_t i;
		R fx;

		assert(_gridSpacing > std::numeric_limits<R>::epsilon());
		R normalizedX = (x - _origin) / _gridSpacing;

		ssize_t iSize = static_cast<ssize_t>(_accessor.size().x);

		getBarycentric(normalizedX, 0, iSize - 1, &i, &fx);

		ssize_t ip1 = std::min(i + 1, iSize - 1);

		*i0 = i;
		*i1 = ip1;
		*weight0 = 1 - fx;
		*weight1 = fx;
	}

	template <typename T, typename R>
	std::function<T(R)> LinearArraySampler<T, R, 1>::functor() const 
	{
		LinearArraySampler sampler(*this);
		return std::bind(&LinearArraySampler::operator(), sampler, std::placeholders::_1);
	}


	template <typename T, typename R>
	CubicArraySampler<T, R, 1>::CubicArraySampler(const ConstArrayAccessor1<T>& accessor,
		R gridSpacing, R gridOrigin) 
	{
		_gridSpacing = gridSpacing;
		_origin = gridOrigin;
		_accessor = accessor;
	}

	template <typename T, typename R>
	CubicArraySampler<T, R, 1>::CubicArraySampler(const CubicArraySampler& other)
	{
		_gridSpacing = other._gridSpacing;
		_origin = other._origin;
		_accessor = other._accessor;
	}

	template <typename T, typename R>
	T CubicArraySampler<T, R, 1>::operator()(R x) const
	{
		ssize_t i;
		ssize_t iSize = static_cast<ssize_t>(_accessor.size());
		R fx;

		assert(_gridSpacing > std::numeric_limits<R>::epsilon());
		R normalizedX = (x - _origin) / _gridSpacing;

		getBarycentric(normalizedX, 0, iSize - 1, &i, &fx);

		ssize_t im1 = std::max(i - 1, kZeroSSize);
		ssize_t ip1 = std::min(i + 1, iSize - 1);
		ssize_t ip2 = std::min(i + 2, iSize - 1);

		return monotonicCatmullRom(_accessor[im1], _accessor[i], _accessor[ip1], _accessor[ip2], fx);
	}

	template <typename T, typename R>
	std::function<T(R)> CubicArraySampler<T, R, 1>::functor() const 
	{
		CubicArraySampler sampler(*this);
		return std::bind(&CubicArraySampler::operator(), sampler, std::placeholders::_1);
	}

}

