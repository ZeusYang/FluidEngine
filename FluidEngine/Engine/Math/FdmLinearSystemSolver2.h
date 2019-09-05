#pragma once

#include <memory>

#include "FdmLinearSystem2.h"

namespace Engine
{
	//! Abstract base class for 2-D finite difference-type linear system solver.
	class FdmLinearSystemSolver2
	{
	public:
		FdmLinearSystemSolver2() = default;

		virtual ~FdmLinearSystemSolver2() = default;

		//! Solves the given linear system.
		virtual bool solve(FdmLinearSystem2* system) = 0;

		//! Solves the given compressed linear system.
		virtual bool solveCompressed(FdmCompressedLinearSystem2*) { return false; }

	};

	//! Shared pointer type for the FdmLinearSystemSolver2.
	typedef std::shared_ptr<FdmLinearSystemSolver2> FdmLinearSystemSolver2Ptr;

}

