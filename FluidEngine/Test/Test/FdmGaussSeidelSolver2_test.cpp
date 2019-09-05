#include <gtest/gtest.h>

#include "FdmLinearSystemSolver2_test_helper.h"
#include "Engine/Math/FdmGaussSeidelSolver2.h"

using namespace Engine;

TEST(FdmGaussSeidelSolver2, SolveLowRes) {
	FdmLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestLinearSystem(&system, { 3, 3 });

	FdmGaussSeidelSolver2 solver(100, 10, 1e-9);
	solver.solve(&system);

	EXPECT_GT(solver.tolerance(), solver.lastResidual());
}

TEST(FdmGaussSeidelSolver2, Solve) {
	FdmLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestLinearSystem(&system,
		{ 128, 128 });

	auto buffer = system.x;
	FdmBlas2::residual(system.A, system.x, system.b, &buffer);
	double norm0 = FdmBlas2::l2Norm(buffer);

	FdmGaussSeidelSolver2 solver(100, 10, 1e-9);
	solver.solve(&system);

	FdmBlas2::residual(system.A, system.x, system.b, &buffer);
	double norm1 = FdmBlas2::l2Norm(buffer);

	EXPECT_LT(norm1, norm0);
}

TEST(FdmGaussSeidelSolver2, Relax) {
	FdmLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestLinearSystem(&system,
		{ 128, 128 });

	auto buffer = system.x;
	FdmBlas2::residual(system.A, system.x, system.b, &buffer);
	double norm0 = FdmBlas2::l2Norm(buffer);

	for (int i = 0; i < 200; ++i) {
		FdmGaussSeidelSolver2::relax(system.A, system.b, 1.0, &system.x);

		FdmBlas2::residual(system.A, system.x, system.b, &buffer);
		double norm = FdmBlas2::l2Norm(buffer);
		EXPECT_LT(norm, norm0);

		norm0 = norm;
	}
}

TEST(FdmGaussSeidelSolver2, RelaxRedBlack) {
	FdmLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestLinearSystem(&system,
		{ 128, 128 });

	auto buffer = system.x;
	FdmBlas2::residual(system.A, system.x, system.b, &buffer);
	double norm0 = FdmBlas2::l2Norm(buffer);

	for (int i = 0; i < 200; ++i) {
		FdmGaussSeidelSolver2::relaxRedBlack(system.A, system.b, 1.0,
			&system.x);

		FdmBlas2::residual(system.A, system.x, system.b, &buffer);
		double norm = FdmBlas2::l2Norm(buffer);
		EXPECT_LT(norm, norm0);

		norm0 = norm;
	}
}

TEST(FdmGaussSeidelSolver2, SolveCompressedRes) {
	FdmCompressedLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestCompressedLinearSystem(&system,
		{ 3, 3 });

	FdmGaussSeidelSolver2 solver(100, 10, 1e-9);
	solver.solveCompressed(&system);

	EXPECT_GT(solver.tolerance(), solver.lastResidual());
}

TEST(FdmGaussSeidelSolver2, SolveCompressed) {
	FdmCompressedLinearSystem2 system;
	FdmLinearSystemSolverTestHelper2::buildTestCompressedLinearSystem(
		&system, { 128, 128 });

	auto buffer = system.x;
	FdmCompressedBlas2::residual(system.A, system.x, system.b, &buffer);
	double norm0 = FdmCompressedBlas2::l2Norm(buffer);

	FdmGaussSeidelSolver2 solver(100, 10, 1e-9);
	solver.solveCompressed(&system);

	FdmCompressedBlas2::residual(system.A, system.x, system.b, &buffer);
	double norm1 = FdmCompressedBlas2::l2Norm(buffer);

	EXPECT_LT(norm1, norm0);
}


