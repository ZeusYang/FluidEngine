#pragma once

#include "Blas.h"
#include "../Utils/Constants.h"

#include <limits>

namespace Engine
{
	//!
	//! \brief No-op preconditioner for conjugate gradient.
	//!
	//! This preconditioner does nothing but simply copies the input vector to the
	//! output vector. Thus, it can be considered as an identity matrix.
	//!
	template <typename BlasType>
	struct NullCgPreconditioner final
	{
		void build(const typename BlasType::MatrixType &) {}

		void solve(const typename BlasType::VectorType &b, typename BlasType::VectorType *x)
		{
			BlasType::set(b, x);
		}
	};

	//!
	//! \brief Solves conjugate gradient.
	//!
	template <typename BlasType>
	void cg(
		const typename BlasType::MatrixType& A,
		const typename BlasType::VectorType& b,
		unsigned int maxNumberOfIterations,
		double tolerance,
		typename BlasType::VectorType* x,
		typename BlasType::VectorType* r,
		typename BlasType::VectorType* d,
		typename BlasType::VectorType* q,
		typename BlasType::VectorType* s,
		unsigned int* lastNumberOfIterations,
		double* lastResidualNorm);

	//!
	//! \brief Solves pre-conditioned conjugate gradient.
	//!
	template < typename BlasType, typename PrecondType>
	void pcg(
		const typename BlasType::MatrixType& A,
		const typename BlasType::VectorType& b,
		unsigned int maxNumberOfIterations,
		double tolerance,
		PrecondType* M,
		typename BlasType::VectorType* x,
		typename BlasType::VectorType* r,
		typename BlasType::VectorType* d,
		typename BlasType::VectorType* q,
		typename BlasType::VectorType* s,
		unsigned int* lastNumberOfIterations,
		double* lastResidualNorm);

	//! --------------------------------Definition------------------------------------

	template <typename BlasType, typename PrecondType>
	void pcg(
		const typename BlasType::MatrixType& A,
		const typename BlasType::VectorType& b,
		unsigned int maxNumberOfIterations,
		double tolerance,
		PrecondType* M,
		typename BlasType::VectorType* x,
		typename BlasType::VectorType* r,
		typename BlasType::VectorType* d,
		typename BlasType::VectorType* q,
		typename BlasType::VectorType* s,
		unsigned int* lastNumberOfIterations,
		double* lastResidualNorm) 
	{
		//https://en.wikipedia.org/wiki/Conjugate_gradient_method

		// Clear
		BlasType::set(0, r);
		BlasType::set(0, d);
		BlasType::set(0, q);
		BlasType::set(0, s);

		// r = b - Ax
		BlasType::residual(A, *x, b, r);

		// d = M^-1r
		M->solve(*r, d);

		// sigmaNew = r.d
		double sigmaNew = BlasType::dot(*r, *d);

		unsigned int iter = 0;
		bool trigger = false;

		// d is p
		// s is z
		// q = Ap
		// sigmaNew is z.r
		while (sigmaNew > square(tolerance) && iter < maxNumberOfIterations) 
		{
			// q = Ad = Ap
			BlasType::mvm(A, *d, q);

			// alpha = sigmaNew/d.q = sigmaNew/(p.A.p)
			double alpha = sigmaNew / BlasType::dot(*d, *q);

			// x = x + alpha*d = x + alpha*p
			BlasType::axpy(alpha, *d, *x, x);

			// if i is divisible by 50...
			if (trigger || (iter % 50 == 0 && iter > 0)) 
			{
				// r = b - Ax
				BlasType::residual(A, *x, b, r);
				trigger = false;
			}
			else 
			{
				// r = r - alpha*q = r - alpha*A.p
				BlasType::axpy(-alpha, *q, *r, r);
			}

			// s = M^-1r = z
			M->solve(*r, s);

			// sigmaOld = sigmaNew
			double sigmaOld = sigmaNew;

			// sigmaNew = r.s = r.z
			sigmaNew = BlasType::dot(*r, *s);

			if (sigmaNew > sigmaOld) 
				trigger = true;

			// beta = sigmaNew/sigmaOld
			double beta = sigmaNew / sigmaOld;

			// d = s + beta*d = z + beta*p
			BlasType::axpy(beta, *d, *s, d);

			++iter;
		}

		*lastNumberOfIterations = iter;

		// std::fabs(sigmaNew) - Workaround for negative zero
		*lastResidualNorm = std::sqrt(std::fabs(sigmaNew));
	}

	template <typename BlasType>
	void cg(
		const typename BlasType::MatrixType& A,
		const typename BlasType::VectorType& b,
		unsigned int maxNumberOfIterations,
		double tolerance,
		typename BlasType::VectorType* x,
		typename BlasType::VectorType* r,
		typename BlasType::VectorType* d,
		typename BlasType::VectorType* q,
		typename BlasType::VectorType* s,
		unsigned int* lastNumberOfIterations,
		double* lastResidualNorm) 
	{
		typedef NullCgPreconditioner<BlasType> PrecondType;
		PrecondType precond;
		pcg<BlasType, PrecondType>(
			A,
			b,
			maxNumberOfIterations,
			tolerance,
			&precond,
			x,
			r,
			d,
			q,
			s,
			lastNumberOfIterations,
			lastResidualNorm);
	}

}