#pragma once

#include "Vector4.h"
#include "Matrix4x4.h"

namespace Engine
{
	//!
	//! \brief Generic BLAS operator wrapper class
	//!
	//! This class provides BLAS (Basic Linear Algebra Subprograms)-like set of
	//! operators for vector and matrix class. By default, it supports Vector<T, 2>,
	//! Vector<T, 3>, Vector<T, 4>, Matrix<T, 2, 2>, Matrix<T, 3, 3> and
	//! Matrix<T, 4, 4>. For custom vector/matrix classes, create a new BLAS class
	//! that conforms the function interfaces defined in this class. It will enable
	//! performing linear algebra routines (such as conjugate gradient) for the
	//! custom vector/matrix types.
	//!
	template <typename S, typename V, typename M>
	class Blas
	{
	public:
		typedef S ScalarType;
		typedef V VectorType;
		typedef M MatrixType;

		//! Sets entire element of given vector \p result with scalar \p s.
		static void set(ScalarType s, VectorType* result);

		//! Copies entire element of given vector \p result with other vector \p v.
		static void set(const VectorType& v, VectorType* result);

		//! Sets entire element of given matrix \p result with scalar \p s.
		static void set(ScalarType s, MatrixType* result);

		//! Copies entire element of given matrix \p result with other matrix \p v.
		static void set(const MatrixType& m, MatrixType* result);

		//! Performs dot product with vector \p a and \p b.
		static ScalarType dot(const VectorType& a, const VectorType& b);

		//! Performs ax + y operation where \p a is a matrix and \p x and \p y are
		//! vectors.
		static void axpy(
			ScalarType a,
			const VectorType& x,
			const VectorType& y,
			VectorType* result);

		//! Performs matrix-vector multiplication.
		static void mvm(
			const MatrixType& m,
			const VectorType& v,
			VectorType* result);

		//! Computes residual vector (b - ax).
		static void residual(
			const MatrixType& a,
			const VectorType& x,
			const VectorType& b,
			VectorType* result);

		//! Returns L2-norm of the given vector \p v.
		static ScalarType l2Norm(const VectorType& v);

		//! Returns Linf-norm of the given vector \p v.
		static ScalarType lInfNorm(const VectorType& v);

	};

	//! -----------------------------Definition------------------------------------

	template <typename ScalarType, typename VectorType, typename MatrixType>
	void Blas<ScalarType, VectorType, MatrixType>::set(ScalarType s, VectorType* result) 
	{ result->set(s); }

	template <typename ScalarType, typename VectorType, typename MatrixType>
	void Blas<ScalarType, VectorType, MatrixType>::set(const VectorType& v, VectorType* result) 
	{ result->set(v); }

	template <typename ScalarType, typename VectorType, typename MatrixType>
	void Blas<ScalarType, VectorType, MatrixType>::set(ScalarType s, MatrixType* result) 
	{ result->set(s); }

	template <typename ScalarType, typename VectorType, typename MatrixType>
	void Blas<ScalarType, VectorType, MatrixType>::set(const MatrixType& m, MatrixType* result) 
	{ result->set(m); }

	template <typename ScalarType, typename VectorType, typename MatrixType>
	ScalarType Blas<ScalarType, VectorType, MatrixType>::dot(
		const VectorType& a, const VectorType& b) 
	{ return a.dot(b); }

	template <typename ScalarType, typename VectorType, typename MatrixType>
	void Blas<ScalarType, VectorType, MatrixType>::axpy(
		ScalarType a,
		const VectorType& x,
		const VectorType& y,
		VectorType* result) 
	{ *result = a * x + y; }

	template <typename ScalarType, typename VectorType, typename MatrixType>
	void Blas<ScalarType, VectorType, MatrixType>::mvm(
		const MatrixType& m, const VectorType& v, VectorType* result) 
	{ *result = m * v; }

	template <typename ScalarType, typename VectorType, typename MatrixType>
	void Blas<ScalarType, VectorType, MatrixType>::residual(
		const MatrixType& a,
		const VectorType& x,
		const VectorType& b,
		VectorType* result) 
	{ *result = b - a * x; }

	template <typename ScalarType, typename VectorType, typename MatrixType>
	ScalarType Blas<ScalarType, VectorType, MatrixType>::l2Norm(
		const VectorType& v) 
	{ return std::sqrt(v.dot(v)); }

	template <typename ScalarType, typename VectorType, typename MatrixType>
	ScalarType Blas<ScalarType, VectorType, MatrixType>::lInfNorm(
		const VectorType& v) 
	{ return std::fabs(v.absmax()); }

}