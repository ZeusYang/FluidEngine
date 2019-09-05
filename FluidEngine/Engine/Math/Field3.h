#pragma once

#include <memory>

namespace Engine
{

	class Field3
	{
	public:
		Field3();
		virtual ~Field3();
	};

	typedef std::shared_ptr<Field3> Field3Ptr;

}
