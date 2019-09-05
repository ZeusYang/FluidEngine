#include "ZhuBridsonPointsToImplicit2.h"

#include "../Simulation/ParticleSystemData2.h"

namespace Engine
{
	inline double k(double s) { return std::max(0.0, cubic(1.0 - s * s)); }

	ZhuBridsonPointsToImplicit2::ZhuBridsonPointsToImplicit2(double kernelRadius, double cutOffThreshold, bool isOutputSdf)
		: _kernelRadius(kernelRadius), _cutOffThreshold(cutOffThreshold), _isOutputSdf(isOutputSdf) {}

	void ZhuBridsonPointsToImplicit2::convert(const ConstArrayAccessor1<Vector2D>& points, ScalarGrid2* output) const
	{
		if (output == nullptr) 
		{
			std::cout << "Null scalar grid output pointer provided.\n";
			return;
		}

		const auto res = output->resolution();
		if (res.x * res.y == 0) 
		{
			std::cout << "Empty grid is provided.\n";
			return;
		}

		const auto bbox = output->boundingBox();
		if (bbox.isEmpty()) 
		{
			std::cout << "Empty domain is provided.\n";
			return;
		}

		ParticleSystemData2 particles;
		particles.addParticles(points);
		particles.buildNeighborSearcher(_kernelRadius);

		const auto neighborSearcher = particles.neighborSearcher();
		const double isoContValue = _cutOffThreshold * _kernelRadius;

		auto temp = output->clone();
		temp->fill([&](const Vector2D& x) -> double 
		{
			Vector2D xAvg;
			double wSum = 0.0;
			const auto func = [&](size_t, const Vector2D& xi) 
			{
				const double wi = k((x - xi).length() / _kernelRadius);
				wSum += wi;
				xAvg += wi * xi;
			};
			neighborSearcher->forEachNearbyPoint(x, _kernelRadius, func);

			if (wSum > 0.0) 
			{
				xAvg /= wSum;
				return (x - xAvg).length() - isoContValue;
			}
			else 
				return output->boundingBox().diagonalLength();
		});

		//if (_isOutputSdf) {
		//	FmmLevelSetSolver2 solver;
		//	solver.reinitialize(*temp, kMaxD, output);
		//}
		//else 
			temp->swap(output);
	}
}