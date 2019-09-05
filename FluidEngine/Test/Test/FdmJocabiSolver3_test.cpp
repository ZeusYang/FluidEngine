#include <gtest/gtest.h>

#include "Engine/Math/FdmJacobiSolver3.h"
#include "FdmLinearSystemSolver3_test_helper.h"

using namespace Engine;

TEST(FdmJacobiSolver3, Solve) {
	FdmLinearSystem3 system;
	FdmLinearSystemSolverTestHelper3::buildTestLinearSystem(&system, { 3, 3, 3 });

	FdmJacobiSolver3 solver(100, 10, 1e-9);
	solver.solve(&system);

	EXPECT_GT(solver.tolerance(), solver.lastResidual());
}

TEST(FdmJacobiSolver3, SolveCompressed) {
	FdmCompressedLinearSystem3 system;
	FdmLinearSystemSolverTestHelper3::buildTestCompressedLinearSystem(
		&system, { 3, 3, 3 });

	FdmJacobiSolver3 solver(100, 10, 1e-9);
	solver.solveCompressed(&system);

	EXPECT_GT(solver.tolerance(), solver.lastResidual());
}
