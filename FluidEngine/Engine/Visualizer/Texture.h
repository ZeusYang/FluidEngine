#pragma once

#include <cstdint>

namespace Engine
{
	//! Texture sampling modes.
	enum class TextureSamplingMode : uint8_t 
	{
		//! Sample nearest pixel.
		kNearest = 0,

		//! Linear-interpolate nearby pixels.
		kLinear = 1
	};
}
