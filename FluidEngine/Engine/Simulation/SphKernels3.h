#pragma once

#include "../Math/Vector3.h"
#include "../Utils/Constants.h"

namespace Engine
{
	//!
	//! \brief Standard 3-D SPH kernel function object.
	//!
	//! \see M¨¹ller, Matthias, David Charypar, and Markus Gross.
	//!     "Particle-based fluid simulation for interactive applications."
	//!     Proceedings of the 2003 ACM SIGGRAPH/Eurographics symposium on Computer
	//!     animation. Eurographics Association, 2003.
	//!
	struct SphStdKernel3
	{
		//! Kernel radius.
		double h;

		//! Square of the kernel radius.
		double h2;

		//! Cubic of the kernel radius.
		double h3;

		//! Fifth-power of the kernel radius.
		double h5;

		//! Constructs a kernel object with zero radius.
		SphStdKernel3();

		//! Constructs a kernel object with given radius.
		explicit SphStdKernel3(double kernelRadius);

		//! Copy constructor
		SphStdKernel3(const SphStdKernel3& other);

		//! Returns kernel function value at given distance.
		double operator()(double distance) const;

		//! Returns the first derivative at given distance.
		double firstDerivative(double distance) const;

		//! Returns the gradient at a point.
		Vector3D gradient(const Vector3D& point) const;

		//! Returns the gradient at a point defined by distance and direction.
		Vector3D gradient(double distance, const Vector3D& direction) const;

		//! Returns the second derivative at given distance.
		double secondDerivative(double distance) const;
	};

	//!
	//! \brief Spiky 3-D SPH kernel function object.
	//!
	//! \see M¨¹ller, Matthias, David Charypar, and Markus Gross.
	//!     "Particle-based fluid simulation for interactive applications."
	//!     Proceedings of the 2003 ACM SIGGRAPH/Eurographics symposium on Computer
	//!     animation. Eurographics Association, 2003.
	//!
	struct SphSpikyKernel3
	{
		//! Kernel radius.
		double h;

		//! Square of the kernel radius.
		double h2;

		//! Cubic of the kernel radius.
		double h3;

		//! Fourth-power of the kernel radius.
		double h4;

		//! Fifth-power of the kernel radius.
		double h5;

		//! Constructs a kernel object with zero radius.
		SphSpikyKernel3();

		//! Constructs a kernel object with given radius.
		explicit SphSpikyKernel3(double kernelRadius);

		//! Copy constructor
		SphSpikyKernel3(const SphSpikyKernel3& other);

		//! Returns kernel function value at given distance.
		double operator()(double distance) const;

		//! Returns the first derivative at given distance.
		double firstDerivative(double distance) const;

		//! Returns the gradient at a point.
		Vector3D gradient(const Vector3D& point) const;

		//! Returns the gradient at a point defined by distance and direction.
		Vector3D gradient(double distance, const Vector3D& direction) const;

		//! Returns the second derivative at given distance.
		double secondDerivative(double distance) const;
	};

	//! --------------------------------------Definition---------------------------------------
	
	inline SphStdKernel3::SphStdKernel3() : h(0), h2(0), h3(0), h5(0) {}

	inline SphStdKernel3::SphStdKernel3(double kernelRadius) : h(kernelRadius), h2(h * h), h3(h2 * h), h5(h2 * h3) {}

	inline SphStdKernel3::SphStdKernel3(const SphStdKernel3& other) : h(other.h), h2(other.h2), h3(other.h3), h5(other.h5) {}

	inline double SphStdKernel3::operator()(double distance) const 
	{
		if (distance * distance >= h2) 
			return 0.0;
		else
		{
			double x = 1.0 - distance * distance / h2;
			return 315.0 / (64.0 * kPiD * h3) * x * x * x;
		}
	}

	inline double SphStdKernel3::firstDerivative(double distance) const 
	{
		if (distance >= h) 
			return 0.0;
		else
		{
			double x = 1.0 - distance * distance / h2;
			return -945.0 / (32.0 * kPiD * h5) * distance * x * x;
		}
	}

	inline Vector3D SphStdKernel3::gradient(const Vector3D& point) const 
	{
		double dist = point.length();
		if (dist > 0.0) 
			return gradient(dist, point / dist);
		else 
			return Vector3D(0, 0, 0);
	}

	inline Vector3D SphStdKernel3::gradient(double distance, const Vector3D& directionToCenter) const
	{
		return -firstDerivative(distance) * directionToCenter;
	}

	inline double SphStdKernel3::secondDerivative(double distance) const 
	{
		if (distance * distance >= h2) 
			return 0.0;
		else
		{
			double x = distance * distance / h2;
			return 945.0 / (32.0 * kPiD * h5) * (1 - x) * (5 * x - 1);
		}
	}

	inline SphSpikyKernel3::SphSpikyKernel3() : h(0), h2(0), h3(0), h4(0), h5(0) {}

	inline SphSpikyKernel3::SphSpikyKernel3(double h_) : h(h_), h2(h * h), h3(h2 * h), h4(h2 * h2), h5(h3 * h2) {}

	inline SphSpikyKernel3::SphSpikyKernel3(const SphSpikyKernel3& other) : h(other.h), h2(other.h2), h3(other.h3), h4(other.h4), h5(other.h5) {}

	inline double SphSpikyKernel3::operator()(double distance) const 
	{
		if (distance >= h) 
			return 0.0;
		else 
		{
			double x = 1.0 - distance / h;
			return 15.0 / (kPiD * h3) * x * x * x;
		}
	}

	inline double SphSpikyKernel3::firstDerivative(double distance) const 
	{
		if (distance >= h) 
			return 0.0;
		else 
		{
			double x = 1.0 - distance / h;
			return -45.0 / (kPiD * h4) * x * x;
		}
	}

	inline Vector3D SphSpikyKernel3::gradient(const Vector3D& point) const 
	{
		double dist = point.length();
		if (dist > 0.0) 
			return gradient(dist, point / dist);
		else 
			return Vector3D(0, 0, 0);
	}

	inline Vector3D SphSpikyKernel3::gradient(double distance, const Vector3D& directionToCenter) const 
	{
		return -firstDerivative(distance) * directionToCenter;
	}

	inline double SphSpikyKernel3::secondDerivative(double distance) const 
	{
		if (distance >= h) 
			return 0.0;
		else 
		{
			double x = 1.0 - distance / h;
			return 90.0 / (kPiD * h5) * x;
		}
	}


}
