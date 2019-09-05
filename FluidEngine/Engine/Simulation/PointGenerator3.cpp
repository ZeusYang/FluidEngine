#include "PointGenerator3.h"

namespace Engine
{

	PointGenerator3::PointGenerator3() {}

	PointGenerator3::~PointGenerator3() {}

	void PointGenerator3::generate(const BoundingBox3D& boundingBox,
		double spacing, Array1<Vector3D>* points) const 
	{
		forEachPoint(
			boundingBox,
			spacing,
			[&points](const Vector3D& point) {
			points->append(point);
			return true;});
	}
}