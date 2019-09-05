#include "SphPointsToImplicit2.h"

#include "../Simulation/SphSystemData2.h"

namespace Engine
{
	SphPointsToImplicit2::SphPointsToImplicit2(double kernelRadius, double cutOffDensity, bool isOutputSdf)
		: _kernelRadius(kernelRadius), _cutOffDensity(cutOffDensity), _isOutputSdf(isOutputSdf) {}

	void SphPointsToImplicit2::convert(const ConstArrayAccessor1<Vector2D>& points, ScalarGrid2* output) const 
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

		SphSystemData2 sphParticles;
		sphParticles.addParticles(points);
		sphParticles.setKernelRadius(_kernelRadius);
		sphParticles.buildNeighborSearcher();
		sphParticles.updateDensities();

		Array1<double> constData(sphParticles.numberOfParticles(), 1.0);
		auto temp = output->clone();
		temp->fill([&](const Vector2D& x)
		{
			double d = sphParticles.interpolate(x, constData.constAccessor());
			return _cutOffDensity - d;
		});

		//if (_isOutputSdf) 
		//{
		//	FmmLevelSetSolver2 solver;
		//	solver.reinitialize(*temp, kMaxD, output);
		//}
		//else 
			temp->swap(output);
	}

}