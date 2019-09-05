#pragma once

#include <vector>
#include <functional>

#include "Blas.h"

namespace Engine
{
	//! Multigrid matrix wrapper.
	template <typename BlasType>
	struct MgMatrix 
	{
		std::vector<typename BlasType::MatrixType> levels;
		const typename BlasType::MatrixType& operator[](size_t i) const;
		typename BlasType::MatrixType& operator[](size_t i);
		const typename BlasType::MatrixType& finest() const;
		typename BlasType::MatrixType& finest();
	};

	//! Multigrid vector wrapper.
	template <typename BlasType>
	struct MgVector
	{
		std::vector<typename BlasType::VectorType> levels;
		const typename BlasType::VectorType& operator[](size_t i) const;
		typename BlasType::VectorType& operator[](size_t i);
		const typename BlasType::VectorType& finest() const;
		typename BlasType::VectorType& finest();
	};

	//! Multigrid relax function type.
	template <typename BlasType>
	using MgRelaxFunc = std::function<void(
		const typename BlasType::MatrixType& A,
		const typename BlasType::VectorType& b,
		unsigned int numberOfIterations,
		double maxTolerance,
		typename BlasType::VectorType* x,
		typename BlasType::VectorType* buffer)>;

	//! Multigrid restriction function type.
	template <typename BlasType>
	using MgRestrictFunc = std::function<void(const typename BlasType::VectorType& finer,
			typename BlasType::VectorType* coarser)>;

	//! Multigrid correction function type.
	template <typename BlasType>
	using MgCorrectFunc = std::function<void(const typename BlasType::VectorType& coarser,
			typename BlasType::VectorType* finer)>;

	//! Multigrid input parameter set.
	template <typename BlasType>
	struct MgParameters 
	{
		//! Max number of multigrid levels.
		size_t maxNumberOfLevels = 1;

		//! Number of iteration at restriction step.
		unsigned int numberOfRestrictionIter = 5;

		//! Number of iteration at correction step.
		unsigned int numberOfCorrectionIter = 5;

		//! Number of iteration at coarsest step.
		unsigned int numberOfCoarsestIter = 20;

		//! Number of iteration at final step.
		unsigned int numberOfFinalIter = 20;

		//! Relaxation function such as Jacobi or Gauss-Seidel.
		MgRelaxFunc<BlasType> relaxFunc;

		//! Restrict function that maps finer to coarser grid.
		MgRestrictFunc<BlasType> restrictFunc;

		//! Correction function that maps coarser to finer grid.
		MgCorrectFunc<BlasType> correctFunc;

		//! Max error tolerance.
		double maxTolerance = 1e-9;
	};

	//! Multigrid result type.
	struct MgResult 
	{
		//! Lastly measured norm of residual.
		double lastResidualNorm;
	};

	//!
	//! \brief Performs Multigrid with V-cycle.
	//!
	//! For given linear system matrix \p A and RHS vector \p b, this function
	//! computes the solution \p x using Multigrid method with V-cycle.
	//!
	template <typename BlasType>
	MgResult mgVCycle(const MgMatrix<BlasType>& A, MgParameters<BlasType> params,
		MgVector<BlasType>* x, MgVector<BlasType>* b, MgVector<BlasType>* buffer);


	//! ----------------------------------Definition---------------------------------------------

	template <typename BlasType>
	MgResult mgVCycle(
		const MgMatrix<BlasType>& A,
		MgParameters<BlasType> params,
		unsigned int currentLevel,
		MgVector<BlasType>* x,
		MgVector<BlasType>* b,
		MgVector<BlasType>* buffer) 
	{
		// 1) Relax a few times on Ax = b, with arbitrary x
		params.relaxFunc(A[currentLevel], (*b)[currentLevel],
			params.numberOfRestrictionIter, params.maxTolerance,
			&((*x)[currentLevel]), &((*buffer)[currentLevel]));

		// 2) if currentLevel is the coarsest grid, goto 5)
		if (currentLevel < A.levels.size() - 1) 
		{
			auto r = buffer;
			BlasType::residual(A[currentLevel], (*x)[currentLevel], (*b)[currentLevel], &(*r)[currentLevel]);
			params.restrictFunc((*r)[currentLevel], &(*b)[currentLevel + 1]);

			BlasType::set(0.0, &(*x)[currentLevel + 1]);

			params.maxTolerance *= 0.5;
			// Solve Ae = r
			mgVCycle(A, params, currentLevel + 1, x, b, buffer);
			params.maxTolerance *= 2.0;

			// 3) correct
			params.correctFunc((*x)[currentLevel + 1], &(*x)[currentLevel]);

			// 4) relax nItr times on Ax = b, with initial guess x
			if (currentLevel > 0) 
			{
				params.relaxFunc(A[currentLevel], (*b)[currentLevel],
					params.numberOfCorrectionIter, params.maxTolerance,
					&((*x)[currentLevel]), &((*buffer)[currentLevel]));
			}
			else
			{
				params.relaxFunc(A[currentLevel], (*b)[currentLevel],
					params.numberOfFinalIter, params.maxTolerance,
					&((*x)[currentLevel]), &((*buffer)[currentLevel]));
			}
		}
		else
		{
			// 5) solve directly with initial guess x
			params.relaxFunc(A[currentLevel], (*b)[currentLevel],
				params.numberOfCoarsestIter, params.maxTolerance,
				&((*x)[currentLevel]), &((*buffer)[currentLevel]));

			BlasType::residual(A[currentLevel], (*x)[currentLevel],
				(*b)[currentLevel], &(*buffer)[currentLevel]);
		}

		BlasType::residual(A[currentLevel], (*x)[currentLevel], (*b)[currentLevel], &(*buffer)[currentLevel]);

		MgResult result;
		result.lastResidualNorm = BlasType::l2Norm((*buffer)[currentLevel]);
		return result;
	}

	template <typename BlasType>
	const typename BlasType::MatrixType& MgMatrix<BlasType>::operator[](size_t i) const { return levels[i]; }

	template <typename BlasType>
	typename BlasType::MatrixType& MgMatrix<BlasType>::operator[](size_t i) { return levels[i]; }

	template <typename BlasType>
	const typename BlasType::MatrixType& MgMatrix<BlasType>::finest() const { return levels.front(); }

	template <typename BlasType>
	typename BlasType::MatrixType& MgMatrix<BlasType>::finest() { return levels.front(); }

	template <typename BlasType>
	const typename BlasType::VectorType& MgVector<BlasType>::operator[](size_t i) const { return levels[i]; }

	template <typename BlasType>
	typename BlasType::VectorType& MgVector<BlasType>::operator[](size_t i) { return levels[i]; }

	template <typename BlasType>
	const typename BlasType::VectorType& MgVector<BlasType>::finest() const { return levels.front(); }

	template <typename BlasType>
	typename BlasType::VectorType& MgVector<BlasType>::finest() { return levels.front(); }

	template <typename BlasType>
	MgResult mgVCycle(
		const MgMatrix<BlasType>& A,
		MgParameters<BlasType> params,
		MgVector<BlasType>* x,
		MgVector<BlasType>* b,
		MgVector<BlasType>* buffer) 
	{
		return mgVCycle<BlasType>(A, params, 0u, x, b, buffer);
	}

}
