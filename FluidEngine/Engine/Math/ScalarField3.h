#pragma once
#include "Field3.h"
#include "Vector3.h"

#include <memory>
#include <functional>

namespace Engine
{

	class ScalarField3 : public Field3
	{
	public:
		//! Default constructor.
		ScalarField3();

		//! Default destructor.
		virtual ~ScalarField3();

		//! Returns sampled value at given position \p x.
		virtual double sample(const Vector3D& x) const = 0;

		//! Returns gradient vector at given position \p x. 
		virtual Vector3D gradient(const Vector3D& x) const;

		//! Returns Laplacian at given position \p x.
		virtual double laplacian(const Vector3D& x) const;

		//! Returns sampler function object.                                          
		virtual std::function<double(const Vector3D&)> sampler() const; 
	};

	//! Shared pointer for the ScalarField3 type.
	typedef std::shared_ptr<ScalarField3> ScalarField3Ptr;

}