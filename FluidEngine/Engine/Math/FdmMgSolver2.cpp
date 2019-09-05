#include "FdmMgSolver2.h"

#include "FdmGaussSeidelSolver2.h"

namespace Engine
{
	FdmMgSolver2::FdmMgSolver2(
		size_t maxNumberOfLevels,
		unsigned int numberOfRestrictionIter,
		unsigned int numberOfCorrectionIter,
		unsigned int numberOfCoarsestIter,
		unsigned int numberOfFinalIter,
		double maxTolerance,
		double sorFactor, bool useRedBlackOrdering) 
	{
		_mgParams.maxNumberOfLevels = maxNumberOfLevels;
		_mgParams.numberOfRestrictionIter = numberOfRestrictionIter;
		_mgParams.numberOfCorrectionIter = numberOfCorrectionIter;
		_mgParams.numberOfCoarsestIter = numberOfCoarsestIter;
		_mgParams.numberOfFinalIter = numberOfFinalIter;
		_mgParams.maxTolerance = maxTolerance;
		if (useRedBlackOrdering)
		{
			_mgParams.relaxFunc = [sorFactor](
				const FdmMatrix2& A, const FdmVector2& b,
				unsigned int numberOfIterations, double maxTolerance, FdmVector2* x,
				FdmVector2* buffer) 
			{
				for (unsigned int iter = 0; iter < numberOfIterations; ++iter) 
					FdmGaussSeidelSolver2::relaxRedBlack(A, b, sorFactor, x);
			};
		}
		else 
		{
			_mgParams.relaxFunc = [sorFactor](
				const FdmMatrix2& A, const FdmVector2& b,
				unsigned int numberOfIterations, double maxTolerance, FdmVector2* x,
				FdmVector2* buffer) 
			{
				for (unsigned int iter = 0; iter < numberOfIterations; ++iter) 
					FdmGaussSeidelSolver2::relax(A, b, sorFactor, x);
			};
		}
		_mgParams.restrictFunc = FdmMgUtils2::restrict;
		_mgParams.correctFunc = FdmMgUtils2::correct;

		_sorFactor = sorFactor;
		_useRedBlackOrdering = useRedBlackOrdering;
	}

	const MgParameters<FdmBlas2>& FdmMgSolver2::params() const { return _mgParams; }

	double FdmMgSolver2::sorFactor() const { return _sorFactor; }

	bool FdmMgSolver2::useRedBlackOrdering() const { return _useRedBlackOrdering; }

	bool FdmMgSolver2::solve(FdmLinearSystem2* system) { return false; }

	bool FdmMgSolver2::solve(FdmMgLinearSystem2* system) 
	{
		FdmMgVector2 buffer = system->x;
		auto result = mgVCycle(system->A, _mgParams, &system->x, &system->b, &buffer);
		return result.lastResidualNorm < _mgParams.maxTolerance;
	}

}
