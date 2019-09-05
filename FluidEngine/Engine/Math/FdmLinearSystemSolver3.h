#pragma once

#include <memory>

#include "FdmLinearSystem3.h"

namespace Engine
{
	//! Abstract base class for 3-D finite difference-type linear system solver.
	class FdmLinearSystemSolver3
	{
	public:
		FdmLinearSystemSolver3() = default;

		virtual ~FdmLinearSystemSolver3() = default;

		//! Solves the given linear system.
		virtual bool solve(FdmLinearSystem3* system) = 0;

		//! Solves the given compressed linear system.
		virtual bool solveCompressed(FdmCompressedLinearSystem3*) { return false; }

	};

	//! Shared pointer type for the FdmLinearSystemSolver3.
	typedef std::shared_ptr<FdmLinearSystemSolver3> FdmLinearSystemSolver3Ptr;

}
