#pragma once

#include <limits>
#include <algorithm>
#include <functional>

#include "Point2.h"
#include "Vector2.h"
#include "ArraySamplers.h"
#include "ArrayAccessor2.h"
#include "../Utils/Macros.h"
#include "../Utils/MathUtils.h"

namespace Engine
{
	//!
	//! \brief 2-D nearest array sampler class.
	//!
	//! This class provides nearest sampling interface for a given 2-D array.
	//!
	//! \tparam T - The value type to sample.
	//! \tparam R - The real number type.
	//!
	template <typename T, typename R>
	class NearestArraySampler<T, R, 2> final
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
		explicit NearestArraySampler(const ConstArrayAccessor2<T>& accessor, const Vector2<R>& gridSpacing, 
			const Vector2<R>& gridOrigin);

		//! Copy constructor.
		NearestArraySampler(const NearestArraySampler& other);

		//! Returns sampled value at point \p pt.
		T operator()(const Vector2<R>& pt) const;

		//! Returns the nearest array index for point \p x.
		void getCoordinate(const Vector2<R>& pt, Point2UI* index) const;

		//! Returns a funtion object that wraps this instance.
		std::function<T(const Vector2<R>&)> functor() const;

	private:
		Vector2<R> _gridSpacing;
		Vector2<R> _origin;
		ConstArrayAccessor2<T> _accessor;

	};

	//! Type alias for 2-D nearest array sampler.
	template <typename T, typename R> using NearestArraySampler2 = NearestArraySampler<T, R, 2>;

	//!
	//! \brief 2-D linear array sampler class.
	//!
	//! This class provides linear sampling interface for a given 2-D array.
	//!
	//! \tparam T - The value type to sample.
	//! \tparam R - The real number type.
	//!
	template <typename T, typename R>
	class LinearArraySampler<T, R, 2> final
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
		explicit LinearArraySampler(const ConstArrayAccessor2<T>& accessor, const Vector2<R>& gridSpacing,
			const Vector2<R>& gridOrigin);

		//! Copy constructor.
		LinearArraySampler(const LinearArraySampler& other);

		//! Returns sampled value at point \p pt.
		T operator()(const Vector2<R>& pt) const;

		//! Returns the indices of points and their sampling weight for given point.
		void getCoordinatesAndWeights(const Vector2<R>& pt, std::array<Point2UI, 4>* indices,
			std::array<R, 4>* weights) const;

		//! Returns the indices of points and their gradient of sampling weight for
		//! given point.
		void getCoordinatesAndGradientWeights(const Vector2<R>& pt, std::array<Point2UI, 4>* indices,
			std::array<Vector2<R>, 4>* weights) const;

		//! Returns a funtion object that wraps this instance.
		std::function<T(const Vector2<R>&)> functor() const;

	private:
		Vector2<R> _gridSpacing;
		Vector2<R> _invGridSpacing;
		Vector2<R> _origin;
		ConstArrayAccessor2<T> _accessor;
	};

	//! Type alias for 2-D linear array sampler.
	template <typename T, typename R> using LinearArraySampler2 = LinearArraySampler<T, R, 2>;

	//!
	//! \brief 2-D cubic array sampler class.
	//!
	//! This class provides cubic sampling interface for a given 2-D array.
	//!
	//! \tparam T - The value type to sample.
	//! \tparam R - The real number type.
	//!
	template <typename T, typename R>
	class CubicArraySampler<T, R, 2> final
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
		explicit CubicArraySampler(const ConstArrayAccessor2<T>& accessor, const Vector2<R>& gridSpacing,
			const Vector2<R>& gridOrigin);

		//! Copy constructor.
		CubicArraySampler(const CubicArraySampler& other);

		//! Returns sampled value at point \p pt.
		T operator()(const Vector2<R>& pt) const;

		//! Returns a funtion object that wraps this instance.
		std::function<T(const Vector2<R>&)> functor() const;

	private:
		Vector2<R> _gridSpacing;
		Vector2<R> _origin;
		ConstArrayAccessor2<T> _accessor;

	};

	//! Type alias for 2-D cubic array sampler.
	template <typename T, typename R> using CubicArraySampler2 = CubicArraySampler<T, R, 2>;

	//! -------------------------------------Definition-----------------------------------------------------
	
	template <typename T, typename R>
	NearestArraySampler<T, R, 2>::NearestArraySampler(const ConstArrayAccessor2<T>& accessor,
		const Vector2<R>& gridSpacing, const Vector2<R>& gridOrigin) 
	{
		_gridSpacing = gridSpacing;
		_origin = gridOrigin;
		_accessor = accessor;
	}

	template <typename T, typename R>
	NearestArraySampler<T, R, 2>::NearestArraySampler(const NearestArraySampler& other) 
	{
		_gridSpacing = other._gridSpacing;
		_origin = other._origin;
		_accessor = other._accessor;
	}

	template <typename T, typename R>
	T NearestArraySampler<T, R, 2>::operator()(const Vector2<R>& x) const 
	{
		ssize_t i, j;
		R fx, fy;

		assert(_gridSpacing.x > std::numeric_limits<R>::epsilon() &&
			_gridSpacing.y > std::numeric_limits<R>::epsilon());
		Vector2<R> normalizedX = (x - _origin) / _gridSpacing;

		ssize_t iSize = static_cast<ssize_t>(_accessor.size().x);
		ssize_t jSize = static_cast<ssize_t>(_accessor.size().y);

		getBarycentric(normalizedX.x, 0, iSize - 1, &i, &fx);
		getBarycentric(normalizedX.y, 0, jSize - 1, &j, &fy);

		i = std::min(static_cast<ssize_t>(i + fx + 0.5), iSize - 1);
		j = std::min(static_cast<ssize_t>(j + fy + 0.5), jSize - 1);

		return _accessor(i, j);
	}

	template <typename T, typename R>
	void NearestArraySampler<T, R, 2>::getCoordinate(const Vector2<R>& x, Point2UI* index) const 
	{
		ssize_t i, j;
		R fx, fy;

		assert(_gridSpacing.x > std::numeric_limits<R>::epsilon() &&
			_gridSpacing.y > std::numeric_limits<R>::epsilon());
		Vector2<R> normalizedX = (x - _origin) / _gridSpacing;

		ssize_t iSize = static_cast<ssize_t>(_accessor.size().x);
		ssize_t jSize = static_cast<ssize_t>(_accessor.size().y);

		getBarycentric(normalizedX.x, 0, iSize - 1, &i, &fx);
		getBarycentric(normalizedX.y, 0, jSize - 1, &j, &fy);

		index->x = std::min(static_cast<ssize_t>(i + fx + 0.5), iSize - 1);
		index->y = std::min(static_cast<ssize_t>(j + fy + 0.5), jSize - 1);
	}

	template <typename T, typename R>
	std::function<T(const Vector2<R>&)> NearestArraySampler<T, R, 2>::functor() const 
	{
		NearestArraySampler sampler(*this);
		return std::bind(&NearestArraySampler::operator(), sampler, std::placeholders::_1);
	}

	template <typename T, typename R>
	LinearArraySampler<T, R, 2>::LinearArraySampler(const ConstArrayAccessor2<T>& accessor,
		const Vector2<R>& gridSpacing, const Vector2<R>& gridOrigin) 
	{
		_gridSpacing = gridSpacing;
		_invGridSpacing = static_cast<R>(1) / _gridSpacing;
		_origin = gridOrigin;
		_accessor = accessor;
	}

	template <typename T, typename R>
	LinearArraySampler<T, R, 2>::LinearArraySampler(const LinearArraySampler& other) 
	{
		_gridSpacing = other._gridSpacing;
		_invGridSpacing = other._invGridSpacing;
		_origin = other._origin;
		_accessor = other._accessor;
	}

	template <typename T, typename R>
	T LinearArraySampler<T, R, 2>::operator()(const Vector2<R>& x) const 
	{
		ssize_t i, j;
		R fx, fy;

		assert(_gridSpacing.x > std::numeric_limits<R>::epsilon() &&
			_gridSpacing.y > std::numeric_limits<R>::epsilon());
		Vector2<R> normalizedX = (x - _origin) / _gridSpacing;

		ssize_t iSize = static_cast<ssize_t>(_accessor.size().x);
		ssize_t jSize = static_cast<ssize_t>(_accessor.size().y);

		getBarycentric(normalizedX.x, 0, iSize - 1, &i, &fx);
		getBarycentric(normalizedX.y, 0, jSize - 1, &j, &fy);

		ssize_t ip1 = std::min(i + 1, iSize - 1);
		ssize_t jp1 = std::min(j + 1, jSize - 1);

		return bilerp(_accessor(i, j), _accessor(ip1, j), _accessor(i, jp1), _accessor(ip1, jp1), fx, fy);
	}

	template <typename T, typename R>
	void LinearArraySampler<T, R, 2>::getCoordinatesAndWeights(const Vector2<R>& x,
		std::array<Point2UI, 4>* indices, std::array<R, 4>* weights) const
	{
		ssize_t i, j;
		R fx, fy;

		assert(_gridSpacing.x > 0.0 && _gridSpacing.y > 0.0);

		Vector2<R> normalizedX = (x - _origin) / _gridSpacing;

		ssize_t iSize = static_cast<ssize_t>(_accessor.size().x);
		ssize_t jSize = static_cast<ssize_t>(_accessor.size().y);

		getBarycentric(normalizedX.x, 0, iSize - 1, &i, &fx);
		getBarycentric(normalizedX.y, 0, jSize - 1, &j, &fy);

		ssize_t ip1 = std::min(i + 1, iSize - 1);
		ssize_t jp1 = std::min(j + 1, jSize - 1);

		(*indices)[0] = Point2UI(i, j);
		(*indices)[1] = Point2UI(ip1, j);
		(*indices)[2] = Point2UI(i, jp1);
		(*indices)[3] = Point2UI(ip1, jp1);

		(*weights)[0] = (1 - fx) * (1 - fy);
		(*weights)[1] = fx * (1 - fy);
		(*weights)[2] = (1 - fx) * fy;
		(*weights)[3] = fx * fy;
	}

	template <typename T, typename R>
	void LinearArraySampler<T, R, 2>::getCoordinatesAndGradientWeights(
		const Vector2<R>& x, std::array<Point2UI, 4>* indices, std::array<Vector2<R>, 4>* weights) const 
	{
		ssize_t i, j;
		R fx, fy;

		assert(_gridSpacing.x > 0.0 && _gridSpacing.y > 0.0);

		const Vector2<R> normalizedX = (x - _origin) * _invGridSpacing;

		const ssize_t iSize = static_cast<ssize_t>(_accessor.size().x);
		const ssize_t jSize = static_cast<ssize_t>(_accessor.size().y);

		getBarycentric(normalizedX.x, 0, iSize - 1, &i, &fx);
		getBarycentric(normalizedX.y, 0, jSize - 1, &j, &fy);

		const ssize_t ip1 = std::min(i + 1, iSize - 1);
		const ssize_t jp1 = std::min(j + 1, jSize - 1);

		(*indices)[0] = Point2UI(i, j);
		(*indices)[1] = Point2UI(ip1, j);
		(*indices)[2] = Point2UI(i, jp1);
		(*indices)[3] = Point2UI(ip1, jp1);

		(*weights)[0] = Vector2<R>(fy * _invGridSpacing.x - _invGridSpacing.x, fx * _invGridSpacing.y - _invGridSpacing.y);
		(*weights)[1] = Vector2<R>(-fy * _invGridSpacing.x + _invGridSpacing.x, -fx * _invGridSpacing.y);
		(*weights)[2] = Vector2<R>(-fy * _invGridSpacing.x, -fx * _invGridSpacing.y + _invGridSpacing.y);
		(*weights)[3] = Vector2<R>(fy * _invGridSpacing.x, fx * _invGridSpacing.y);
	}

	template <typename T, typename R>
	std::function<T(const Vector2<R>&)> LinearArraySampler<T, R, 2>::functor() const 
	{
		LinearArraySampler sampler(*this);
		return std::bind(&LinearArraySampler::operator(), sampler, std::placeholders::_1);
	}

	template <typename T, typename R>
	CubicArraySampler<T, R, 2>::CubicArraySampler(const ConstArrayAccessor2<T>& accessor,
		const Vector2<R>& gridSpacing, const Vector2<R>& gridOrigin) 
	{
		_gridSpacing = gridSpacing;
		_origin = gridOrigin;
		_accessor = accessor;
	}

	template <typename T, typename R>
	CubicArraySampler<T, R, 2>::CubicArraySampler(const CubicArraySampler& other) 
	{
		_gridSpacing = other._gridSpacing;
		_origin = other._origin;
		_accessor = other._accessor;
	}

	template <typename T, typename R>
	T CubicArraySampler<T, R, 2>::operator()(const Vector2<R>& x) const
	{
		ssize_t i, j;
		const ssize_t iSize = static_cast<ssize_t>(_accessor.size().x);
		const ssize_t jSize = static_cast<ssize_t>(_accessor.size().y);
		R fx, fy;

		assert(_gridSpacing.x > std::numeric_limits<R>::epsilon() &&
			_gridSpacing.y > std::numeric_limits<R>::epsilon());
		const Vector2<R> normalizedX = (x - _origin) / _gridSpacing;

		getBarycentric(normalizedX.x, 0, iSize - 1, &i, &fx);
		getBarycentric(normalizedX.y, 0, jSize - 1, &j, &fy);

		ssize_t is[4] = 
		{
			std::max(i - 1, kZeroSSize),
			i,
			std::min(i + 1, iSize - 1),
			std::min(i + 2, iSize - 1)
		};
		ssize_t js[4] = 
		{
			std::max(j - 1, kZeroSSize),
			j,
			std::min(j + 1, jSize - 1),
			std::min(j + 2, jSize - 1)
		};

		// Calculate in i direction first
		T values[4];
		for (int n = 0; n < 4; ++n) 
		{
			values[n] = monotonicCatmullRom(
				_accessor(is[0], js[n]), _accessor(is[1], js[n]),
				_accessor(is[2], js[n]), _accessor(is[3], js[n]),
				fx);
		}

		return monotonicCatmullRom(values[0], values[1], values[2], values[3], fy);
	}

	template <typename T, typename R>
	std::function<T(const Vector2<R>&)> CubicArraySampler<T, R, 2>::functor() const 
	{
		CubicArraySampler sampler(*this);
		return std::bind(&CubicArraySampler::operator(), sampler, std::placeholders::_1);
	}

}
