#include "PointGenerator2.h"

namespace Engine
{
	PointGenerator2::PointGenerator2() {}

	PointGenerator2::~PointGenerator2() {}

	void PointGenerator2::generate(const BoundingBox2D& boundingBox,
		double spacing, Array1<Vector2D>* points) const 
	{
		forEachPoint(
			boundingBox,
			spacing,
			[&points](const Vector2D& point) {
			points->append(point);
			return true; });
	}
}