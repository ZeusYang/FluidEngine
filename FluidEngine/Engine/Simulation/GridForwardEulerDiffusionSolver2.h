#pragma once

#include <limits>
#include <memory>

#include "GridDiffusionSolver2.h"
#include "../Math/ConstantScalarField2.h"

namespace Engine
{
	//!
	//! \brief 2-D grid-based forward Euler diffusion solver.
	//!
	//! This class implements 2-D grid-based forward Euler diffusion solver using
	//! second-order central differencing spatially. Since the method is relying on
	//! explicit time-integration (i.e. forward Euler), the diffusion coefficient is
	//! limited by the time interval and grid spacing such as:
	//! \f$\mu < \frac{h}{8\Delta t} \f$ where \f$\mu\f$, \f$h\f$, and
	//! \f$\Delta t\f$ are the diffusion coefficient, grid spacing, and time
	//! interval, respectively.
	//!
	class GridForwardEulerDiffusionSolver2 final : public GridDiffusionSolver2
	{
	public:
		//! Default constructor.
		GridForwardEulerDiffusionSolver2();

		//!
		//! Solves diffusion equation for a scalar field.
		//!
		//! \param source Input scalar field.
		//! \param diffusionCoefficient Amount of diffusion.
		//! \param timeIntervalInSeconds Small time-interval that diffusion occur.
		//! \param dest Output scalar field.
		//! \param boundarySdf Shape of the solid boundary that is empty by default.
		//! \param fluidSdf Shape of the fluid boundary that is full by default.
		//!
		void solve(
			const ScalarGrid2& source,
			double diffusionCoefficient,
			double timeIntervalInSeconds,
			ScalarGrid2* dest,
			const ScalarField2& boundarySdf = ConstantScalarField2(kMaxD),
			const ScalarField2& fluidSdf = ConstantScalarField2(-kMaxD)) override;

		//!
		//! Solves diffusion equation for a collocated vector field.
		//!
		//! \param source Input collocated vector field.
		//! \param diffusionCoefficient Amount of diffusion.
		//! \param timeIntervalInSeconds Small time-interval that diffusion occur.
		//! \param dest Output collocated vector field.
		//! \param boundarySdf Shape of the solid boundary that is empty by default.
		//! \param fluidSdf Shape of the fluid boundary that is full by default.
		//!
		void solve(
			const CollocatedVectorGrid2& source,
			double diffusionCoefficient,
			double timeIntervalInSeconds,
			CollocatedVectorGrid2* dest,
			const ScalarField2& boundarySdf = ConstantScalarField2(kMaxD),
			const ScalarField2& fluidSdf = ConstantScalarField2(-kMaxD)) override;

		//!
		//! Solves diffusion equation for a face-centered vector field.
		//!
		//! \param source Input face-centered vector field.
		//! \param diffusionCoefficient Amount of diffusion.
		//! \param timeIntervalInSeconds Small time-interval that diffusion occur.
		//! \param dest Output face-centered vector field.
		//! \param boundarySdf Shape of the solid boundary that is empty by default.
		//! \param fluidSdf Shape of the fluid boundary that is full by default.
		//!
		void solve(
			const FaceCenteredGrid2& source,
			double diffusionCoefficient,
			double timeIntervalInSeconds,
			FaceCenteredGrid2* dest,
			const ScalarField2& boundarySdf = ConstantScalarField2(kMaxD),
			const ScalarField2& fluidSdf = ConstantScalarField2(-kMaxD)) override;

	private:
		Array2<char> _markers;

		void buildMarkers(
			const Size2& size,
			const std::function<Vector2D(size_t, size_t)>& pos,
			const ScalarField2& boundarySdf,
			const ScalarField2& fluidSdf);

	};

	//! Shared pointer type for the GridForwardEulerDiffusionSolver2.
	typedef std::shared_ptr<GridForwardEulerDiffusionSolver2> GridForwardEulerDiffusionSolver2Ptr;

}

