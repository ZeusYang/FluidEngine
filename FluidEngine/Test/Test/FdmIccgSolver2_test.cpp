#include "Engine/Math/FdmIccgSolver2.h"

#include "FdmLinearSystemSolver2_test_helper.h"
#include <gtest/gtest.h>

using namespace Engine;

TEST(FdmIccgSolver2, SolveLowRes) {
	FdmLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestLinearSystem(&system, { 3, 3 });

	FdmIccgSolver2 solver(10, 1e-9);
	solver.solve(&system);

	EXPECT_GT(solver.tolerance(), solver.lastResidual());
}

TEST(FdmIccgSolver2, Solve) {
	FdmLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestLinearSystem(&system,
		{ 128, 128 });

	FdmIccgSolver2 solver(200, 1e-4);
	EXPECT_TRUE(solver.solve(&system));
}

TEST(FdmIccgSolver2, SolveCompressed) {
	FdmLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestLinearSystem(&system, { 3, 3 });

	FdmIccgSolver2 solver(200, 1e-4);
	EXPECT_TRUE(solver.solve(&system));
}