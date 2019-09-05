#pragma once

#include "Point.h"

namespace Engine
{
	//! \brief N-D size type.
	template <size_t N> using Size = Point<size_t, N>;
}