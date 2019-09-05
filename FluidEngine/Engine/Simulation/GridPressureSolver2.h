#pragma once

#include <memory>

#include "../Utils/Constants.h"
#include "../Geometry/ScalarGrid2.h"
#include "GridBoundaryConditionSolver2.h"
#include "../Math/ConstantScalarField2.h"
#include "../Math/ConstantVectorField2.h"
#include "../Geometry/FaceCenteredGrid2.h"
#include "../Geometry/CollocatedVectorGrid2.h"

namespace Engine
{
	//!
	//! \brief Abstract base class for 2-D grid-based pressure solver.
	//!
	//! This class represents a 2-D grid-based pressure solver interface which can
	//! be used as a sub-step of GridFluidSolver2. Inheriting classes must implement
	//! the core GridPressureSolver2::solve function as well as the helper function
	//! GridPressureSolver2::suggestedBoundaryConditionSolver.
	//!
	class GridPressureSolver2
	{
	public:
		//! Default constructor.
		GridPressureSolver2();

		//! Default destructor.
		virtual ~GridPressureSolver2();

		//!
		//! \brief Solves the pressure term and apply it to the velocity field.
		//!
		//! This function takes input velocity field and outputs pressure-applied
		//! velocity field. It also accepts extra arguments such as \p boundarySdf
		//! and \p fluidSdf that represent signed-distance representation of the
		//! boundary and fluid area. The negative region of \p boundarySdf means
		//! it is occupied by solid object. Also, the positive / negative area of
		//! the \p fluidSdf means it is occupied by fluid / atmosphere. If not
		//! specified, constant scalar field with kMaxD will be used for
		//! \p boundarySdf meaning that no boundary at all. Similarly, a constant
		//! field with -kMaxD will be used for \p fluidSdf which means it's fully
		//! occupied with fluid without any atmosphere.
		//!
		//! \param[in]    input                 The input velocity field.
		//! \param[in]    timeIntervalInSeconds The time interval for the sim.
		//! \param[inout] output                The output velocity field.
		//! \param[in]    boundarySdf           The SDF of the boundary.
		//! \param[in]    fluidSdf              The SDF of the fluid/atmosphere.
		//! \param[in]    useCompressed         True if it uses compressed system.
		//!
		virtual void solve(
			const FaceCenteredGrid2& input,
			double timeIntervalInSeconds,
			FaceCenteredGrid2* output,
			const ScalarField2& boundarySdf = ConstantScalarField2(kMaxD),
			const VectorField2& boundaryVelocity = ConstantVectorField2({ 0, 0 }),
			const ScalarField2& fluidSdf = ConstantScalarField2(-kMaxD),
			bool useCompressed = false) = 0;

		//!
		//! \brief Returns the best boundary condition solver for this solver.
		//!
		//! This function returns the best boundary condition solver that works well
		//! with this pressure solver. Depending on the pressure solver
		//! implementation, different boundary condition solver might be used.
		//!
		virtual GridBoundaryConditionSolver2Ptr suggestedBoundaryConditionSolver() const = 0;

	};

	//! Shared pointer type for the GridPressureSolver2.
	typedef std::shared_ptr<GridPressureSolver2> GridPressureSolver2Ptr;

}

