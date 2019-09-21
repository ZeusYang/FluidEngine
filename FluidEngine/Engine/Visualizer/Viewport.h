#pragma once

#include "../Math/Vector2.h"

namespace Engine
{
	struct Viewport 
	{
		float x;
		float y;
		float width;
		float height;

		Viewport();
		Viewport(float newX, float newY, float newWidth, float newHeight);

		float aspectRatio() const;

		Vector2F center() const;

		//! Returns true if equal to the other viewport.
		bool operator==(const Viewport& other) const;

		//! Returns true if not equal to the other viewport.
		bool operator!=(const Viewport& other) const;
	};
}
