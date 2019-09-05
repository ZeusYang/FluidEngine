#include "Engine/Math/FdmCgSolver2.h"

#include "FdmLinearSystemSolver2_test_helper.h"
#include <gtest/gtest.h>

using namespace Engine;

TEST(FdmCgSolver2, Solve) {
	FdmLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestLinearSystem(&system, { 3, 3 });

	FdmCgSolver2 solver(10, 1e-9);
	solver.solve(&system);

	EXPECT_GT(solver.tolerance(), solver.lastResidual());
}

TEST(FdmCgSolver2, SolveCompressed) {
	FdmCompressedLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestCompressedLinearSystem(&system,
		{ 3, 3 });

	FdmCgSolver2 solver(10, 1e-9);
	solver.solveCompressed(&system);

	EXPECT_GT(solver.tolerance(), solver.lastResidual());
}

