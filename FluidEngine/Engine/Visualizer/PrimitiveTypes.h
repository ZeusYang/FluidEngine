#pragma once

#include "Shader.h"
#include "Vertex.h"

namespace Engine
{
	//! Render primitive types
	enum class PrimitiveType 
	{
		//! Multiple points primitive.
		Points = 0,

		//! Multiple lines primitive.
		Lines,

		//! Line strip primitive.
		LineStrip,

		//! Multiple triangles primitive.
		Triangles,

		//! Triangle strip primitive.
		TriangleStrip,
	};
}
