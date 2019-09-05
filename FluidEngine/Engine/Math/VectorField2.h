#pragma once
#include "Field2.h"
#include "Vector2.h"

#include <memory>
#include <functional>

namespace Engine
{

	class VectorField2 : public Field2
	{
	public:
		//! Default constructor.
		VectorField2();

		//! Default destructor.
		virtual ~VectorField2();

		//! Returns sampled value at given position \p x.
		virtual Vector2D sample(const Vector2D& x) const = 0;

		//! Returns divergence at given position \p x.
		virtual double divergence(const Vector2D& x) const;

		//! Returns curl at given position \p x.
		virtual double curl(const Vector2D& x) const;

		//! Returns sampler function object.
		virtual std::function<Vector2D(const Vector2D&)> sampler() const;
	};

	//! Shared pointer for the VectorField2 type.
	typedef std::shared_ptr<VectorField2> VectorField2Ptr;

}

