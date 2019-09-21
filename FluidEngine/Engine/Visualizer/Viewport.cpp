#include "Viewport.h"

#include <assert.h>

namespace Engine
{
	Viewport::Viewport() : x(0), y(0), width(256), height(256) {}

	Viewport::Viewport(float newX, float newY, float newWidth, float newHeight)
		: x(newX), y(newY), width(newWidth), height(newHeight) 
	{
		assert(width > 0.0f && height > 0.0f);
	}

	float Viewport::aspectRatio() const { return width / height; }

	Vector2F Viewport::center() const 
	{
		return Vector2F(x + width / 2.0f, y + height / 2.0f);
	}

	bool Viewport::operator==(const Viewport& other) const 
	{
		return x == other.x && y == other.y && width == other.width && height == other.height;
	}

	bool Viewport::operator!=(const Viewport& other) const 
	{
		return !(*this == other);
	}
}