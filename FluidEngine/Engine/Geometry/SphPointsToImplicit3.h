#pragma once

#include "PointsToImplicit3.h"

namespace Engine
{
	//!
	//! \brief 3-D points-to-implicit converter based on standard SPH kernel.
	//!
	//! \see M¨¹ller, Matthias, David Charypar, and Markus Gross.
	//!      "Particle-based fluid simulation for interactive applications."
	//!      Proceedings of the 2003 ACM SIGGRAPH/Eurographics symposium on Computer
	//!      animation. Eurographics Association, 2003.
	//!
	class SphPointsToImplicit3 final : public PointsToImplicit3
	{
	public:
		//! Constructs the converter with given kernel radius and cut-off density.
		SphPointsToImplicit3(double kernelRadius = 1.0, double cutOffDensity = 0.5, bool isOutputSdf = true);

		//! Converts the given points to implicit surface scalar field.
		void convert(const ConstArrayAccessor1<Vector3D>& points, ScalarGrid3* output) const override;

	private:
		double _kernelRadius = 1.0;
		double _cutOffDensity = 0.5;
		bool _isOutputSdf = true;
	};

	//! Shared pointer type for SphPointsToImplicit3 class.
	typedef std::shared_ptr<SphPointsToImplicit3> SphPointsToImplicit3Ptr;

}
