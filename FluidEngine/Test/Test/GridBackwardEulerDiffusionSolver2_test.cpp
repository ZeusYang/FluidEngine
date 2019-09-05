#include "Engine/Simulation/GridBackwardEulerDiffusionSolver2.h"
#include "Engine/Geometry/CellCenteredScalarGrid2.h"
#include <gtest/gtest.h>

using namespace Engine;

TEST(GridBackwardEulerDiffusionSolver2, Solve) {
	CellCenteredScalarGrid2 src(3, 3, 1.0, 1.0, 0.0, 0.0);
	CellCenteredScalarGrid2 dst(3, 3, 1.0, 1.0, 0.0, 0.0);

	src(1, 1) = 1.0;

	GridBackwardEulerDiffusionSolver2 diffusionSolver;
	diffusionSolver.solve(src, 1.0 / 8.0, 1.0, &dst);

	Array2<double> solution = {
		{0.012987, 0.064935, 0.012987},
		{0.064935, 0.688312, 0.064935},
		{0.012987, 0.064935, 0.012987}
	};

	dst.forEachDataPointIndex([&](size_t i, size_t j) {
		EXPECT_NEAR(solution(i, j), dst(i, j), 1e-6);
	});
}