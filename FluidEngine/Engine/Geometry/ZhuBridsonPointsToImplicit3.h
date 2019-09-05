#pragma once

#include "PointsToImplicit3.h"

namespace Engine
{
	//!
	//! \brief 3-D points-to-implicit converter based on Zhu and Bridson's method.
	//!
	//! \see Zhu, Yongning, and Robert Bridson. "Animating sand as a fluid."
	//!      ACM Transactions on Graphics (TOG). Vol. 24. No. 3. ACM, 2005.
	//!
	class ZhuBridsonPointsToImplicit3 final : public PointsToImplicit3
	{
	public:
		//! Constructs the converter with given kernel radius and cut-off threshold.
		ZhuBridsonPointsToImplicit3(double kernelRadius = 1.0, double cutOffThreshold = 0.25, bool isOutputSdf = true);

		//! Converts the given points to implicit surface scalar field.
		void convert(const ConstArrayAccessor1<Vector3D>& points, ScalarGrid3* output) const override;

	private:
		double _kernelRadius = 1.0;
		double _cutOffThreshold = 0.25;
		bool _isOutputSdf = true;

	};

	//! Shared pointer type for ZhuBridsonPointsToImplicit3 class
	typedef std::shared_ptr<ZhuBridsonPointsToImplicit3> ZhuBridsonPointsToImplicit3Ptr;

}
