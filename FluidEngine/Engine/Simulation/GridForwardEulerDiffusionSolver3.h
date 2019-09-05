#pragma once

#include <limits>
#include <memory>

#include "GridDiffusionSolver3.h"
#include "../Math/ConstantScalarField3.h"

namespace Engine
{
	//!
	//! \brief 3-D grid-based forward Euler diffusion solver.
	//!
	//! This class implements 3-D grid-based forward Euler diffusion solver using
	//! second-order central differencing spatially. Since the method is relying on
	//! explicit time-integration (i.e. forward Euler), the diffusion coefficient is
	//! limited by the time interval and grid spacing such as:
	//! \f$\mu < \frac{h}{12\Delta t} \f$ where \f$\mu\f$, \f$h\f$, and
	//! \f$\Delta t\f$ are the diffusion coefficient, grid spacing, and time
	//! interval, respectively.
	//!
	class GridForwardEulerDiffusionSolver3 final : public GridDiffusionSolver3
	{
	public:
		//! Default constructor.
		GridForwardEulerDiffusionSolver3();

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
			const ScalarGrid3& source,
			double diffusionCoefficient,
			double timeIntervalInSeconds,
			ScalarGrid3* dest,
			const ScalarField3& boundarySdf = ConstantScalarField3(kMaxD),
			const ScalarField3& fluidSdf = ConstantScalarField3(-kMaxD)) override;

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
			const CollocatedVectorGrid3& source,
			double diffusionCoefficient,
			double timeIntervalInSeconds,
			CollocatedVectorGrid3* dest,
			const ScalarField3& boundarySdf = ConstantScalarField3(kMaxD),
			const ScalarField3& fluidSdf = ConstantScalarField3(-kMaxD)) override;

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
			const FaceCenteredGrid3& source,
			double diffusionCoefficient,
			double timeIntervalInSeconds,
			FaceCenteredGrid3* dest,
			const ScalarField3& boundarySdf = ConstantScalarField3(kMaxD),
			const ScalarField3& fluidSdf = ConstantScalarField3(-kMaxD)) override;

	private:
		Array3<char> _markers;

		void buildMarkers(
			const Size3& size,
			const std::function<Vector3D(size_t, size_t, size_t)>& pos,
			const ScalarField3& boundarySdf,
			const ScalarField3& fluidSdf);

	};

	//! Shared pointer type for the GridForwardEulerDiffusionSolver3.
	typedef std::shared_ptr<GridForwardEulerDiffusionSolver3> GridForwardEulerDiffusionSolver3Ptr;

}
