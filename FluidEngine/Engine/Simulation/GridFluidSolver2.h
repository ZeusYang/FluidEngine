#pragma once

#include "GridEmitter2.h"
#include "GridSystemData2.h"
#include "PhysicsAnimation.h"
#include "AdvectionSolver2.h"
#include "GridBoundaryConditionSolver2.h"
#include "../Geometry/FaceCenteredGrid2.h"
#include "../Geometry/CellCenteredScalarGrid2.h"

namespace Engine
{
	//!
	//! \brief Abstract base class for grid-based 2-D fluid solver.
	//!
	//! This is an abstract base class for grid-based 2-D fluid solver based on
	//! Jos Stam's famous 1999 paper - "Stable Fluids". This solver takes fractional
	//! step method as its foundation which is consisted of independent advection,
	//! diffusion, external forces, and pressure projection steps. Each step is
	//! configurable so that a custom step can be implemented. For example, if a
	//! user wants to change the advection solver to her/his own implementation,
	//! simply call GridFluidSolver2::setAdvectionSolver(newSolver).
	//!
	class GridFluidSolver2 : public PhysicsAnimation
	{
	public:
		class Builder;



	};

}
