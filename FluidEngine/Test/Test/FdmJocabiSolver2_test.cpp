#include <gtest/gtest.h>

#include "Engine/Math/FdmJacobiSolver2.h"
#include "FdmLinearSystemSolver2_test_helper.h"

using namespace Engine;


TEST(FdmJacobiSolver2, Solve) {
	FdmLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestLinearSystem(&system, { 3, 3 });

	FdmJacobiSolver2 solver(100, 10, 1e-9);
	solver.solve(&system);

	EXPECT_GT(solver.tolerance(), solver.lastResidual());
}

TEST(FdmJacobiSolver2, SolveCompressed) {
	FdmCompressedLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestCompressedLinearSystem(&system,
		{ 3, 3 });

	FdmJacobiSolver2 solver(100, 10, 1e-9);
	solver.solveCompressed(&system);

	EXPECT_GT(solver.tolerance(), solver.lastResidual());
}


