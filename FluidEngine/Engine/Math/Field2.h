#pragma once

#include <memory>

namespace Engine
{

	//! Abstract base class for 2-D fields.	
	class Field2
	{
	public:
		Field2();
		virtual ~Field2();
	};

	typedef std::shared_ptr<Field2> Field2Ptr;

}

