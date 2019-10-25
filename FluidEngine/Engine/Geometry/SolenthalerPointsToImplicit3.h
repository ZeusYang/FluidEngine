#pragma once

#include "PointsToImplicit3.h"

namespace Engine
{
	//!
	//! \brief 3-D points-to-implicit converter based on Solenthaler's method.
	//!
	//! \see B. Solenthaler, J. Schläfli, and R. Pajarola, “A unified particle
	//!      model for fluidsolid interactions.”
	//!      Computer Animation Virtual Worlds, vol. 18, no. 1, pp. 69–82, 2007.
	//!
	class SolenthalerPointsToImplicit3 final : public PointsToImplicit3
	{
	public:

		//! Constructs the converter with given kernel radius and cut-off threshold.
		SolenthalerPointsToImplicit3(double kernelRadius = 1.0,
			double cutOffThreshold = 0.25, bool isOutputSdf = true);

		//! Converts the given points to implicit surface scalar field.
		void convert(const ConstArrayAccessor1<Vector3D>& points, ScalarGrid3* output) const override;

	private:
		double _kernelRadius = 1.0;
		double _cutOffThreshold = 0.25;
		bool _isOutputSdf = true;

	};

}