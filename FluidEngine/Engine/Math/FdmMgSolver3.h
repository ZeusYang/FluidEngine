#pragma once

#include "Mg.h"
#include "FdmMgLinearSystem3.h"
#include "FdmLinearSystemSolver3.h"

namespace Engine
{
	//! \brief 3-D finite difference-type linear system solver using Multigrid.
	class FdmMgSolver3 : public FdmLinearSystemSolver3 
	{
	public:
		FdmMgSolver3() = default;

		virtual ~FdmMgSolver3() = default;

		//! Constructs the solver with given parameters.
		FdmMgSolver3(size_t maxNumberOfLevels,
			unsigned int numberOfRestrictionIter = 5,
			unsigned int numberOfCorrectionIter = 5,
			unsigned int numberOfCoarsestIter = 20,
			unsigned int numberOfFinalIter = 20,
			double maxTolerance = 1e-9, double sorFactor = 1.5,
			bool useRedBlackOrdering = false);

		//! Returns the Multigrid parameters.
		const MgParameters<FdmBlas3>& params() const;

		//! Returns the SOR (Successive Over Relaxation) factor.
		double sorFactor() const;

		//! Returns true if red-black ordering is enabled.
		bool useRedBlackOrdering() const;

		//! No-op. Multigrid-type solvers do not solve FdmLinearSystem3.
		bool solve(FdmLinearSystem3* system) final;

		//! Solves Multigrid linear system.
		virtual bool solve(FdmMgLinearSystem3* system);

	private:
		MgParameters<FdmBlas3> _mgParams;
		double _sorFactor;
		bool _useRedBlackOrdering;
	};

	//! Shared pointer type for the FdmMgSolver3.
	typedef std::shared_ptr<FdmMgSolver3> FdmMgSolver3Ptr;
}