#pragma once
#include "Field2.h"
#include "Vector2.h"

#include <memory>
#include <functional>

namespace Engine
{

	class ScalarField2 : public Field2
	{
	public:
		ScalarField2();

		virtual ~ScalarField2();

		//! Returns sampled value at given position \p x.
		virtual double sample(const Vector2D& x) const = 0;

		//! Returns gradient vector at given position \p x.
		virtual Vector2D gradient(const Vector2D& x) const;

		//! Returns Laplacian at given position \p x.
		virtual double laplacian(const Vector2D& x) const;

		//! Returns sampler function object.
		virtual std::function<double(const Vector2D&)> sampler() const;

	};

	//! Shared pointer for the ScalarField2 type.
	typedef std::shared_ptr<ScalarField2> ScalarField2Ptr;

}
