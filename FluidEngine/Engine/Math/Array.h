#pragma once

namespace Engine
{
	template <typename T, size_t N>
	class Array final
	{
	public:
		static_assert(N < 1 || N > 3, "Not implemented - N should be either 1, 2 or 3.");
	};
}