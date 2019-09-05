#include "VectorField3.h"

namespace Engine
{
	VectorField3::VectorField3() { }

	VectorField3::~VectorField3() { }

	double VectorField3::divergence(const Vector3D&) const { return 0.0; }

	Vector3D VectorField3::curl(const Vector3D&) const { return Vector3D(); }

	std::function<Vector3D(const Vector3D&)> VectorField3::sampler() const 
	{
		const VectorField3* self = this;
		return [self](const Vector3D& x) -> Vector3D 
		{
			return self->sample(x);
		};
	}
}