#pragma once

#include "Mg.h"
#include "FdmMgLinearSystem2.h"
#include "FdmLinearSystemSolver2.h"

namespace Engine
{
	//! \brief 2-D finite difference-type linear system solver using Multigrid.
	class FdmMgSolver2 : public FdmLinearSystemSolver2 
	{
	public:
		FdmMgSolver2() = default;

		virtual ~FdmMgSolver2() = default;

		//! Constructs the solver with given parameters.
		FdmMgSolver2(size_t maxNumberOfLevels,
			unsigned int numberOfRestrictionIter = 5,
			unsigned int numberOfCorrectionIter = 5,
			unsigned int numberOfCoarsestIter = 20,
			unsigned int numberOfFinalIter = 20,
			double maxTolerance = 1e-9, double sorFactor = 1.5,
			bool useRedBlackOrdering = false);

		//! Returns the Multigrid parameters.
		const MgParameters<FdmBlas2>& params() const;

		//! Returns the SOR (Successive Over Relaxation) factor.
		double sorFactor() const;

		//! Returns true if red-black ordering is enabled.
		bool useRedBlackOrdering() const;

		//! No-op. Multigrid-type solvers do not solve FdmLinearSystem2.
		bool solve(FdmLinearSystem2* system) final;

		//! Solves Multigrid linear system.
		virtual bool solve(FdmMgLinearSystem2* system);

	private:
		MgParameters<FdmBlas2> _mgParams;
		double _sorFactor;
		bool _useRedBlackOrdering;
	};

	//! Shared pointer type for the FdmMgSolver2.
	typedef std::shared_ptr<FdmMgSolver2> FdmMgSolver2Ptr;
}