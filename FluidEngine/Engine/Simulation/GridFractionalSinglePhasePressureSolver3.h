#pragma once

#include <memory>

#include "GridPressureSolver3.h"
#include "../Math/FdmMgSolver3.h"
#include "../Math/FdmMgLinearSystem3.h"
#include "GridBoundaryConditionSolver3.h"
#include "../Math/FdmLinearSystemSolver3.h"
#include "../Geometry/CellCenteredScalarGrid3.h"
#include "../Geometry/VertexCenteredScalarGrid3.h"

namespace Engine
{
	//!
	//! \brief 3-D fractional single-phase pressure solver.
	//!
	//! This class implements 3-D fractional (or variational) single-phase pressure
	//! solver. It is called fractional because the solver encodes the boundaries
	//! to the grid cells like anti-aliased pixels, meaning that a grid cell will
	//! record the partially overlapping boundary as a fractional number.
	//! Alternative apporach is to represent boundaries like Lego blocks which is
	//! the case for GridSinglePhasePressureSolver2.
	//! In addition, this class solves single-phase flow, solving the pressure for
	//! selected fluid region only and treat other area as an atmosphere region.
	//! Thus, the pressure outside the fluid will be set to a constant value and
	//! velocity field won't be altered. This solver also computes the fluid
	//! boundary in fractional manner, meaning that the solver tries to capture the
	//! subgrid structures. This class uses ghost fluid method for such calculation.
	//!
	//! \see Batty, Christopher, Florence Bertails, and Robert Bridson.
	//!     "A fast variational framework for accurate solid-fluid coupling."
	//!     ACM Transactions on Graphics (TOG). Vol. 26. No. 3. ACM, 2007.
	//! \see Enright, Doug, et al. "Using the particle level set method and
	//!     a second order accurate pressure boundary condition for free surface
	//!     flows." ASME/JSME 2003 4th Joint Fluids Summer Engineering Conference.
	//!     American Society of Mechanical Engineers, 2003.
	//!
	class GridFractionalSinglePhasePressureSolver3 : public GridPressureSolver3
	{
	public:
		GridFractionalSinglePhasePressureSolver3();

		virtual ~GridFractionalSinglePhasePressureSolver3();

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
			const FaceCenteredGrid3& input, 
			double timeIntervalInSeconds,
			FaceCenteredGrid3* output,
			const ScalarField3& boundarySdf = ConstantScalarField3(kMaxD),
			const VectorField3& boundaryVelocity = ConstantVectorField3({ 0, 0, 0 }),
			const ScalarField3& fluidSdf = ConstantScalarField3(-kMaxD),
			bool useCompressed = false) override;

		//!
		//! \brief Returns the best boundary condition solver for this solver.
		//!
		//! This function returns the best boundary condition solver that works well
		//! with this pressure solver. Depending on the pressure solver
		//! implementation, different boundary condition solver might be used. For
		//! this particular class, an instance of
		//! GridFractionalBoundaryConditionSolver3 will be returned.
		//!
		GridBoundaryConditionSolver3Ptr suggestedBoundaryConditionSolver() const override;

		//! Returns the linear system solver.
		const FdmLinearSystemSolver3Ptr& linearSystemSolver() const;

		//! Sets the linear system solver.
		void setLinearSystemSolver(const FdmLinearSystemSolver3Ptr& solver);

		//! Returns the pressure field.
		const FdmVector3& pressure() const;

	private:
		FdmLinearSystem3 _system;
		FdmCompressedLinearSystem3 _compSystem;
		FdmLinearSystemSolver3Ptr _systemSolver;

		FdmMgLinearSystem3 _mgSystem;
		FdmMgSolver3Ptr _mgSystemSolver;

		std::vector<Array3<float>> _uWeights;
		std::vector<Array3<float>> _vWeights;
		std::vector<Array3<float>> _wWeights;
		std::vector<Array3<float>> _fluidSdf;

		std::function<Vector3D(const Vector3D&)> _boundaryVel;

		void buildWeights(
			const FaceCenteredGrid3& input,
			const ScalarField3& boundarySdf,
			const VectorField3& boundaryVelocity,
			const ScalarField3& fluidSdf);

		void decompressSolution();

		virtual void buildSystem(const FaceCenteredGrid3& input, bool useCompressed);

		virtual void applyPressureGradient(const FaceCenteredGrid3& input, FaceCenteredGrid3* output);

	};

	//! Shared pointer type for the GridFractionalSinglePhasePressureSolver3.
	typedef std::shared_ptr<GridFractionalSinglePhasePressureSolver3> GridFractionalSinglePhasePressureSolver3Ptr;

}