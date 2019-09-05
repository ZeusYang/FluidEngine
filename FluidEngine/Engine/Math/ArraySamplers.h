#pragma once

#include "Array.h"

namespace Engine
{
	//!
	//! \brief Generic N-D nearest array sampler class.
	//!
	//! \tparam T - The value type to sample.
	//! \tparam R - The real number type.
	//! \tparam N - Dimension.
	//!
	template <typename T, typename R, size_t N>
	class NearestArraySampler final 
	{
	public:
		static_assert(N < 1 || N > 3, "Not implemented - N should be either 1, 2 or 3.");
	};

	//!
	//! \brief Generic N-D linear array sampler class.
	//!
	//! \tparam T - The value type to sample.
	//! \tparam R - The real number type.
	//! \tparam N - Dimension.
	//!
	template <typename T, typename R, size_t N>
	class LinearArraySampler final
	{
	public:
		static_assert(N < 1 || N > 3, "Not implemented - N should be either 1, 2 or 3.");
	};

	//!
	//! \brief Generic N-D cubic array sampler class.
	//!
	//! \tparam T - The value type to sample.
	//! \tparam R - The real number type.
	//! \tparam N - Dimension.
	//!
	template <typename T, typename R, size_t N>
	class CubicArraySampler final 
	{
	public:
		static_assert(N < 1 || N > 3, "Not implemented - N should be either 1, 2 or 3.");
	};

}
