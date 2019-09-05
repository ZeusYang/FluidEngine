#pragma once

#include <memory>

#include "GridPressureSolver2.h"
#include "../Math/FdmMgSolver2.h"
#include "../Math/FdmMgLinearSystem2.h"
#include "../Math/FdmLinearSystemSolver2.h"
#include "GridBoundaryConditionSolver2.h"

namespace Engine
{
	//!
	//! \brief 2-D single-phase pressure solver.
	//!
	//! This class implements 2-D single-phase pressure solver. This solver encodes
	//! the boundaries like Lego blocks -- if a grid cell center is inside or
	//! outside the boundaries, it is either marked as occupied or not.
	//! In addition, this class solves single-phase flow, solving the pressure for
	//! selected fluid region only and treat other area as an atmosphere region.
	//! Thus, the pressure outside the fluid will be set to a constant value and
	//! velocity field won't be altered. This solver also computes the fluid
	//! boundary in block-like manner; If a grid cell is inside or outside the
	//! fluid, it is marked as either fluid or atmosphere. Thus, this solver in
	//! general, does not compute subgrid structure.
	//!
	class GridSinglePhasePressureSolver2 : public GridPressureSolver2
	{
	public:
		//! Default constructor.
		GridSinglePhasePressureSolver2();

		//! Default destructor.
		virtual ~GridSinglePhasePressureSolver2();

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
		void solve(
			const FaceCenteredGrid2& input,
			double timeIntervalInSeconds,
			FaceCenteredGrid2* output,
			const ScalarField2& boundarySdf = ConstantScalarField2(kMaxD),
			const VectorField2& boundaryVelocity = ConstantVectorField2({ 0, 0 }),
			const ScalarField2& fluidSdf = ConstantScalarField2(-kMaxD),
			bool useCompressed = false) override;

		//!
		//! \brief Returns the best boundary condition solver for this solver.
		//!
		//! This function returns the best boundary condition solver that works well
		//! with this pressure solver. Depending on the pressure solver
		//! implementation, different boundary condition solver might be used. For
		//! this particular class, an instance of
		//! GridBlockedBoundaryConditionSolver2 will be returned since this pressure
		//! solver encodes boundaries like pixelated Lego blocks.
		//!
		GridBoundaryConditionSolver2Ptr suggestedBoundaryConditionSolver() const override;

		//! Returns the linear system solver
		const FdmLinearSystemSolver2Ptr& linearSystemSolver() const;

		//! Sets the linear system solver.
		void setLinearSystemSolver(const FdmLinearSystemSolver2Ptr& solver);

		//! Returns the pressure field.
		const FdmVector2& pressure() const;

	private:
		FdmLinearSystem2 _system;
		FdmCompressedLinearSystem2 _compSystem;
		FdmLinearSystemSolver2Ptr _systemSolver;

		FdmMgLinearSystem2 _mgSystem;
		FdmMgSolver2Ptr _mgSystemSolver;

		std::vector<Array2<char>> _markers;

		void buildMarkers(const Size2& size,
			const std::function<Vector2D(size_t, size_t)>& pos,
			const ScalarField2& boundarySdf,
			const ScalarField2& fluidSdf);

		void decompressSolution();

		virtual void buildSystem(const FaceCenteredGrid2& input, bool useCompressed);

		virtual void applyPressureGradient(const FaceCenteredGrid2& input, FaceCenteredGrid2* output);

	};

	//! Shared pointer type for the GridSinglePhasePressureSolver2.
	typedef std::shared_ptr<GridSinglePhasePressureSolver2> GridSinglePhasePressureSolver2Ptr;

}
