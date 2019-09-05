#pragma once

#include <limits>
#include <memory>

#include "../Utils/Constants.h"
#include "../Geometry/ScalarGrid2.h"
#include "../Geometry/FaceCenteredGrid2.h"
#include "../Math/ConstantScalarField2.h"
#include "../Geometry/CollocatedVectorGrid2.h"

namespace Engine
{
	//!
	//! \brief Abstract base class for 2-D grid-based diffusion equation solver.
	//!
	//! This class provides functions to solve the diffusion equation for different
	//! types of fields. The target equation can be written as
	//! \f$\frac{\partial f}{\partial t} = \mu\nabla^2 f\f$ where \f$\mu\f$ is
	//! the diffusion coefficient. The field \f$f\f$ can be either scalar or vector
	//! field.
	//!
	class GridDiffusionSolver2
	{
	public:
		//! Default constructor.
		GridDiffusionSolver2();

		//! Default destructor.
		virtual ~GridDiffusionSolver2();

		//!
		//! Solves diffusion equation for a scalar field.
		//!
		//! \param source Input scalar field.
		//! \param diffusionCoefficient Amount of diffusion.
		//! \param timeIntervalInSeconds Small time-interval that diffusion occur.
		//! \param dest Output scalar field.
		//! \param boundarySdf Shape of the solid boundary that is empty by default.
		//! \param boundarySdf Shape of the fluid boundary that is full by default.
		//!
		virtual void solve(
			const ScalarGrid2& source,
			double diffusionCoefficient,
			double timeIntervalInSeconds,
			ScalarGrid2* dest,
			const ScalarField2& boundarySdf = ConstantScalarField2(kMaxD),
			const ScalarField2& fluidSdf = ConstantScalarField2(-kMaxD)) = 0;

		//!
		//! Solves diffusion equation for a collocated vector field.
		//!
		//! \param source Input collocated vector field.
		//! \param diffusionCoefficient Amount of diffusion.
		//! \param timeIntervalInSeconds Small time-interval that diffusion occur.
		//! \param dest Output collocated vector field.
		//! \param boundarySdf Shape of the solid boundary that is empty by default.
		//! \param boundarySdf Shape of the fluid boundary that is full by default.
		//!
		virtual void solve(
			const CollocatedVectorGrid2& source,
			double diffusionCoefficient,
			double timeIntervalInSeconds,
			CollocatedVectorGrid2* dest,
			const ScalarField2& boundarySdf = ConstantScalarField2(kMaxD),
			const ScalarField2& fluidSdf = ConstantScalarField2(-kMaxD)) = 0;

		//!
		//! Solves diffusion equation for a face-centered vector field.
		//!
		//! \param source Input face-centered vector field.
		//! \param diffusionCoefficient Amount of diffusion.
		//! \param timeIntervalInSeconds Small time-interval that diffusion occur.
		//! \param dest Output face-centered vector field.
		//! \param boundarySdf Shape of the solid boundary that is empty by default.
		//! \param boundarySdf Shape of the fluid boundary that is full by default.
		//!
		virtual void solve(
			const FaceCenteredGrid2& source,
			double diffusionCoefficient,
			double timeIntervalInSeconds,
			FaceCenteredGrid2* dest,
			const ScalarField2& boundarySdf = ConstantScalarField2(kMaxD),
			const ScalarField2& fluidSdf = ConstantScalarField2(-kMaxD)) = 0;

	};

	//! Shared pointer type for the GridDiffusionSolver2.
	typedef std::shared_ptr<GridDiffusionSolver2> GridDiffusionSolver2Ptr;

}

