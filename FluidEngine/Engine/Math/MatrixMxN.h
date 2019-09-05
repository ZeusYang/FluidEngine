#pragma once

#include "Array2.h"
#include "VectorN.h"
#include "../Utils/Parallel.h"
#include "../Utils/MathUtils.h"
#include "MatrixExpression.h"

namespace Engine
{
	//!
	//! \brief M x N matrix class.
	//!
	//! This class defines M x N row-major matrix.
	//!
	//! \tparam T Type of the element.
	//!
	template <typename T>
	class MatrixMxN final : public MatrixExpression<T, MatrixMxN<T>>
	{
	public:
		static_assert(
			std::is_floating_point<T>::value,
			"MatrixMxN only can be instantiated with floating point types");

		typedef Array2<T> ContainerType;
		typedef typename ContainerType::Iterator Iterator;
		typedef typename ContainerType::ConstIterator ConstIterator;

		// MARK: Constructors

		//! Constructs an empty matrix.
		MatrixMxN();

		//! Constructs m x n constant value matrix.
		MatrixMxN(size_t m, size_t n, const T& s = T(0));

		//!
		//! \brief Constructs a matrix with given initializer list \p lst.
		//!
		//! This constructor will build a matrix with given initializer list \p lst
		//! such as
		//!
		//! \code{.cpp}
		//! MatrixMxN<float> mat = {
		//!     {1.f, 2.f, 4.f, 3.f},
		//!     {9.f, 3.f, 5.f, 1.f},
		//!     {4.f, 8.f, 1.f, 5.f}
		//! };
		//! \endcode
		//!
		//! Note the initializer has 4x3 structure which will create 4x3 matrix.
		//!
		//! \param lst Initializer list that should be copy to the new matrix.
		//!
		MatrixMxN(const std::initializer_list<std::initializer_list<T>>& lst);

		//! Constructs a matrix with expression template.
		template <typename E>
		MatrixMxN(const MatrixExpression<T, E>& other);

		//! Constructs a m x n matrix with input array.
		//! \warning Ordering of the input elements is row-major.
		MatrixMxN(size_t m, size_t n, const T* arr);

		//! Copy constructor.
		MatrixMxN(const MatrixMxN& other);

		//! Move constructor.
		MatrixMxN(MatrixMxN&& other);

		// MARK: Basic setters

		//! Resizes to m x n matrix with initial value \p s.
		void resize(size_t m, size_t n, const T& s = T(0));

		//! Sets whole matrix with input scalar.
		void set(const T& s);

		//!
		//! \brief Sets a matrix with given initializer list \p lst.
		//!
		//! This function will fill the matrix with given initializer list \p lst
		//! such as
		//!
		//! \code{.cpp}
		//! MatrixMxN<float> mat;
		//! mat.set({
		//!     {1.f, 2.f, 4.f, 3.f},
		//!     {9.f, 3.f, 5.f, 1.f},
		//!     {4.f, 8.f, 1.f, 5.f}
		//! });
		//! \endcode
		//!
		//! Note the initializer has 4x3 structure which will resize to 4x3 matrix.
		//!
		//! \param lst Initializer list that should be copy to the new matrix.
		//!
		void set(const std::initializer_list<std::initializer_list<T>>& lst);

		//! Copies from input matrix expression.
		template <typename E>
		void set(const MatrixExpression<T, E>& other);

		//! Copies from input array.
		//! \warning Ordering of the input elements is row-major.
		void set(size_t m, size_t n, const T* arr);

		//! Sets diagonal elements with input scalar.
		void setDiagonal(const T& s);

		//! Sets off-diagonal elements with input scalar.
		void setOffDiagonal(const T& s);

		//! Sets i-th row with input vector.
		template <typename E>
		void setRow(size_t i, const VectorExpression<T, E>& row);

		//! Sets j-th column with input vector.
		template <typename E>
		void setColumn(size_t j, const VectorExpression<T, E>& col);

		// MARK: Basic getters
		template <typename E>
		bool isEqual(const MatrixExpression<T, E>& other) const;

		//! Returns true if this matrix is similar to the input matrix within the
		//! given tolerance.
		template <typename E>
		bool isSimilar(const MatrixExpression<T, E>& other,
			double tol = std::numeric_limits<double>::epsilon()) const;

		//! Returns true if this matrix is a square matrix.
		bool isSquare() const;

		//! Returns the size of this matrix.
		Size2 size() const;

		//! Returns number of rows of this matrix.
		size_t rows() const;

		//! Returns number of columns of this matrix.
		size_t cols() const;

		//! Returns data pointer of this matrix.
		T* data();

		//! Returns constant pointer of this matrix.
		const T* const data() const;

		//! Returns the begin iterator of the matrix.
		Iterator begin();

		//! Returns the begin const iterator of the matrix.
		ConstIterator begin() const;

		//! Returns the end iterator of the matrix.
		Iterator end();

		//! Returns the end const iterator of the matrix.
		ConstIterator end() const;

		// MARK: Binary operator methods - new instance = this instance (+) input

		//! Returns this matrix + input scalar.
		MatrixScalarAdd<T, MatrixMxN> add(const T& s) const;

		//! Returns this matrix + input matrix (element-wise).
		template <typename E>
		MatrixAdd<T, MatrixMxN, E> add(const E& m) const;

		//! Returns this matrix - input scalar.
		MatrixScalarSub<T, MatrixMxN> sub(const T& s) const;

		//! Returns this matrix - input matrix (element-wise).
		template <typename E>
		MatrixSub<T, MatrixMxN, E> sub(const E& m) const;

		//! Returns this matrix * input scalar.
		MatrixScalarMul<T, MatrixMxN> mul(const T& s) const;

		//! Returns this matrix * input vector.
		template <typename VE>
		MatrixVectorMul<T, MatrixMxN, VE> mul(
			const VectorExpression<T, VE>& v) const;

		//! Returns this matrix * input matrix.
		template <typename E>
		MatrixMul<T, MatrixMxN, E> mul(const E& m) const;

		//! Returns this matrix / input scalar.
		MatrixScalarDiv<T, MatrixMxN> div(const T& s) const;

		// MARK: Binary operator methods - new instance = input (+) this instance
		//! Returns input scalar + this matrix.
		MatrixScalarAdd<T, MatrixMxN> radd(const T& s) const;

		//! Returns input matrix + this matrix (element-wise).
		template <typename E>
		MatrixAdd<T, MatrixMxN, E> radd(const E& m) const;

		//! Returns input scalar - this matrix.
		MatrixScalarRSub<T, MatrixMxN> rsub(const T& s) const;

		//! Returns input matrix - this matrix (element-wise).
		template <typename E>
		MatrixSub<T, MatrixMxN, E> rsub(const E& m) const;

		//! Returns input scalar * this matrix.
		MatrixScalarMul<T, MatrixMxN> rmul(const T& s) const;

		//! Returns input matrix * this matrix.
		template <typename E>
		MatrixMul<T, E, MatrixMxN> rmul(const E& m) const;

		//! Returns input matrix / this scalar.
		MatrixScalarRDiv<T, MatrixMxN> rdiv(const T& s) const;

		// MARK: Augmented operator methods - this instance (+)= input

		//! Adds input scalar to this matrix.
		void iadd(const T& s);

		//! Adds input matrix to this matrix (element-wise).
		template <typename E>
		void iadd(const E& m);

		//! Subtracts input scalar from this matrix.
		void isub(const T& s);

		//! Subtracts input matrix from this matrix (element-wise).
		template <typename E>
		void isub(const E& m);

		//! Multiplies input scalar to this matrix.
		void imul(const T& s);

		//! Multiplies input matrix to this matrix.
		template <typename E>
		void imul(const E& m);

		//! Divides this matrix with input scalar.
		void idiv(const T& s);

		// MARK: Modifiers

		//! Transposes this matrix.
		void transpose();

		//!
		//! \brief Inverts this matrix.
		//!
		//! This function computes the inverse using Gaussian elimination method.
		//!
		void invert();

		// MARK: Complex getters
		//! Returns sum of all elements.
		T sum() const;

		//! Returns average of all elements.
		T avg() const;

		//! Returns minimum among all elements.
		T min() const;

		//! Returns maximum among all elements.
		T max() const;

		//! Returns absolute minimum among all elements.
		T absmin() const;

		//! Returns absolute maximum among all elements.
		T absmax() const;

		//! Returns sum of all diagonal elements.
		//! \warning Should be a square matrix.
		T trace() const;

		//! Returns determinant of this matrix.
		T determinant() const;

		//! Returns diagonal part of this matrix.
		MatrixDiagonal<T, MatrixMxN> diagonal() const;

		//! Returns off-diagonal part of this matrix.
		MatrixDiagonal<T, MatrixMxN> offDiagonal() const;

		//! Returns strictly lower triangle part of this matrix.
		MatrixTriangular<T, MatrixMxN> strictLowerTri() const;

		//! Returns strictly upper triangle part of this matrix.
		MatrixTriangular<T, MatrixMxN> strictUpperTri() const;

		//! Returns lower triangle part of this matrix (including the diagonal).
		MatrixTriangular<T, MatrixMxN> lowerTri() const;

		//! Returns upper triangle part of this matrix (including the diagonal).
		MatrixTriangular<T, MatrixMxN> upperTri() const;

		//! Returns transposed matrix.
		MatrixMxN transposed() const;

		//! Returns inverse matrix.
		MatrixMxN inverse() const;

		//! Type-casts to different value-typed matrix.
		template <typename U>
		MatrixTypeCast<U, MatrixMxN, T> castTo() const;

		// MARK: Setter operators

		//! Assigns input matrix.
		template <typename E>
		MatrixMxN& operator=(const E& m);

		//! Copies to this matrix.
		MatrixMxN& operator=(const MatrixMxN& other);

		//! Moves to this matrix.
		MatrixMxN& operator=(MatrixMxN&& other);

		//! Addition assignment with input scalar.
		MatrixMxN& operator+=(const T& s);

		//! Addition assignment with input matrix (element-wise).
		template <typename E>
		MatrixMxN& operator+=(const E& m);

		//! Subtraction assignment with input scalar.
		MatrixMxN& operator-=(const T& s);

		//! Subtraction assignment with input matrix (element-wise).
		template <typename E>
		MatrixMxN& operator-=(const E& m);

		//! Multiplication assignment with input scalar.
		MatrixMxN& operator*=(const T& s);

		//! Multiplication assignment with input matrix.
		template <typename E>
		MatrixMxN& operator*=(const E& m);

		//! Division assignment with input scalar.
		MatrixMxN& operator/=(const T& s);

		// MARK: Getter operators

		//! Returns reference of i-th element.
		T& operator[](size_t i);

		//! Returns constant reference of i-th element.
		const T& operator[](size_t i) const;

		//! Returns reference of (i,j) element.
		T& operator()(size_t i, size_t j);

		//! Returns constant reference of (i,j) element.
		const T& operator()(size_t i, size_t j) const;

		//! Returns true if is equal to m.
		template <typename E>
		bool operator==(const MatrixExpression<T, E>& m) const;

		//! Returns true if is not equal to m.
		template <typename E>
		bool operator!=(const MatrixExpression<T, E>& m) const;

		// MARK: Helpers

		//!
		//! \brief Iterates the matrix and invoke given \p func for each index.
		//!
		//! This function iterates the matrix elements and invoke the callback
		//! function \p func. The callback function takes matrix's element as its
		//! input. The order of execution will be the same as the nested for-loop
		//! below:
		//!
		//! \code{.cpp}
		//! MatrixMxN<double> mat(100, 200, 4.0);
		//! for (size_t i = 0; i < mat.rows(); ++i) {
		//!     for (size_t j = 0; j < mat.cols(); ++j) {
		//!         func(mat(i, j));
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! MatrixMxN<double> mat(100, 200, 4.0);
		//! mat.forEach([](double elem) {
		//!     printf("%d\n", elem);
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void forEach(Callback func) const;

		//!
		//! \brief Iterates the matrix and invoke given \p func for each index.
		//!
		//! This function iterates the matrix elements and invoke the callback
		//! function \p func. The callback function takes two parameters which are
		//! the (i, j) indices of the matrix. The order of execution will be the
		//! same as the nested for-loop below:
		//!
		//! \code{.cpp}
		//! MatrixMxN<double> mat(100, 200, 4.0);
		//! for (size_t i = 0; i < mat.rows(); ++i) {
		//!     for (size_t j = 0; j < mat.cols(); ++j) {
		//!         func(i, j);
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! MatrixMxN<double> mat(100, 200, 4.0);
		//! mat.forEachIndex([&](size_t i, size_t j) {
		//!     mat(i, j) = 4.0 * i + 7.0 * j + 1.5;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void forEachIndex(Callback func) const;

		//!
		//! \brief Iterates the matrix and invoke given \p func for each index in
		//!     parallel.
		//!
		//! This function iterates the matrix elements and invoke the callback
		//! function \p func. The callback function takes matrix's element as its
		//! input. The order of execution will be non-deterministic since it runs in
		//! parallel. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! MatrixMxN<double> mat(100, 200, 4.0);
		//! mat.parallelForEach([](double& elem) {
		//!     elem *= 2.0;
		//! });
		//! \endcode
		//!
		//! The parameter type of the callback function doesn't have to be T&, but
		//! const T& or T can be used as well.
		//!
		template <typename Callback>
		void parallelForEach(Callback func);

		//!
		//! \brief Iterates the matrix and invoke given \p func for each index in
		//!     parallel using multi-threading.
		//!
		//! This function iterates the matrix elements and invoke the callback
		//! function \p func in parallel using multi-threading. The callback
		//! function takes two parameters which are the (i, j) indices of the
		//! matrix. The order of execution will be non-deterministic since it runs
		//! in parallel. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! MatrixMxN<double> mat(100, 200, 4.0);
		//! mat.parallelForEachIndex([&](size_t i, size_t j) {
		//!     mat(i, j) *= 2;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void parallelForEachIndex(Callback func) const;

		// MARK: Builders

		//! Makes a m x n matrix with zeros.
		static MatrixConstant<T> makeZero(size_t m, size_t n);

		//! Makes a m x m matrix with all diagonal elements to 1, and other elements
		//! to 0.
		static MatrixIdentity<T> makeIdentity(size_t m);

	private:
		ContainerType _elements;

	};

	//! Float-type M x N matrix.
	typedef MatrixMxN<float> MatrixMxNF;

	//! Double-type M x N matrix.
	typedef MatrixMxN<double> MatrixMxND;

	//! ------------------------------Definition------------------------------

	template <typename T>
	MatrixMxN<T>::MatrixMxN() {}

	template <typename T>
	MatrixMxN<T>::MatrixMxN(size_t m, size_t n, const T& s) { resize(m, n, s); }

	template <typename T>
	MatrixMxN<T>::MatrixMxN(const std::initializer_list<std::initializer_list<T>>& lst) 
	{ _elements.set(lst); }

	template <typename T>
	template <typename E>
	MatrixMxN<T>::MatrixMxN(const MatrixExpression<T, E>& other) { set(other); }

	template <typename T>
	MatrixMxN<T>::MatrixMxN(const MatrixMxN& other) { set(other); }

	template <typename T>
	MatrixMxN<T>::MatrixMxN(MatrixMxN&& other) { (*this) = std::move(other); }

	template <typename T>
	MatrixMxN<T>::MatrixMxN(size_t m, size_t n, const T* arr) { set(m, n, arr); }

	template <typename T>
	void MatrixMxN<T>::resize(size_t m, size_t n, const T& s) 
	{
		// Note that m and n are flipped.
		_elements.resize(n, m, s);
	}

	template <typename T>
	void MatrixMxN<T>::set(const T& s) { _elements.set(s); }

	template <typename T>
	void MatrixMxN<T>::set(const std::initializer_list<std::initializer_list<T>>& lst) 
	{ _elements.set(lst); }

	template <typename T>
	template <typename E>
	void MatrixMxN<T>::set(const MatrixExpression<T, E>& other) 
	{
		resize(other.rows(), other.cols());
		// Parallel evaluation of the expression
		const E& expression = other();
		parallelForEachIndex(
			[&](size_t i, size_t j) { (*this)(i, j) = expression(i, j); });
	}

	template <typename T>
	void MatrixMxN<T>::set(size_t m, size_t n, const T* arr) 
	{
		resize(m, n);
		const size_t sz = m * n;
		for (size_t i = 0; i < sz; ++i) 
			_elements[i] = arr[i];
	}

	template <typename T>
	void MatrixMxN<T>::setDiagonal(const T& s) 
	{
		const size_t l = std::min(rows(), cols());
		for (size_t i = 0; i < l; ++i) 
			(*this)(i, i) = s;
	}

	template <typename T>
	void MatrixMxN<T>::setOffDiagonal(const T& s) 
	{
		parallelForEachIndex([&](size_t i, size_t j)
		{
			if (i != j) 
				(*this)(i, j) = s;
		});
	}

	template <typename T>
	template <typename E>
	void MatrixMxN<T>::setRow(size_t i, const VectorExpression<T, E>& row) 
	{
		assert(cols() == row.size());
		const E& e = row();
		parallelFor(kZeroSize, cols(), [&](size_t j) { (*this)(i, j) = e[j]; });
	}

	template <typename T>
	template <typename E>
	void MatrixMxN<T>::setColumn(size_t j, const VectorExpression<T, E>& col) 
	{
		assert(rows() == col.size());
		const E& e = col();
		parallelFor(kZeroSize, rows(), [&](size_t i) { (*this)(i, j) = e[i]; });
	}

	template <typename T>
	template <typename E>
	bool MatrixMxN<T>::isEqual(const MatrixExpression<T, E>& other) const 
	{
		if (size() != other.size()) 
			return false;
		const E& e = other();
		for (size_t i = 0; i < rows(); ++i) 
			for (size_t j = 0; j < cols(); ++j) 
				if ((*this)(i, j) != e(i, j)) 
					return false;
		return true;
	}

	template <typename T>
	template <typename E>
	bool MatrixMxN<T>::isSimilar(const MatrixExpression<T, E>& other, double tol) const 
	{
		if (size() != other.size()) 
			return false;
		const E& e = other();
		for (size_t i = 0; i < rows(); ++i) 
			for (size_t j = 0; j < cols(); ++j) 
				if (std::fabs((*this)(i, j) - e(i, j)) > tol) 
					return false;
		return true;
	}

	template <typename T>
	bool MatrixMxN<T>::isSquare() const { return rows() == cols(); }

	template <typename T>
	Size2 MatrixMxN<T>::size() const { return Size2(rows(), cols()); }

	template <typename T>
	size_t MatrixMxN<T>::rows() const { return _elements.height(); }

	template <typename T>
	size_t MatrixMxN<T>::cols() const { return _elements.width(); }

	template <typename T>
	T* MatrixMxN<T>::data() { return _elements.data(); }

	template <typename T>
	const T* const MatrixMxN<T>::data() const { return _elements.data(); }

	template <typename T>
	typename MatrixMxN<T>::Iterator MatrixMxN<T>::begin() { return _elements.begin(); }

	template <typename T>
	typename MatrixMxN<T>::ConstIterator MatrixMxN<T>::begin() const { return _elements.begin(); }

	template <typename T>
	typename MatrixMxN<T>::Iterator MatrixMxN<T>::end() { return _elements.end(); }

	template <typename T>
	typename MatrixMxN<T>::ConstIterator MatrixMxN<T>::end() const { return _elements.end(); }

	template <typename T>
	MatrixScalarAdd<T, MatrixMxN<T>> MatrixMxN<T>::add(const T& s) const 
	{ return MatrixScalarAdd<T, MatrixMxN<T>>(*this, s); }

	template <typename T>
	template <typename E>
	MatrixAdd<T, MatrixMxN<T>, E> MatrixMxN<T>::add(const E& m) const 
	{ return MatrixAdd<T, MatrixMxN, E>(*this, m); }

	template <typename T>
	MatrixScalarSub<T, MatrixMxN<T>> MatrixMxN<T>::sub(const T& s) const 
	{ return MatrixScalarSub<T, MatrixMxN<T>>(*this, s); }

	template <typename T>
	template <typename E>
	MatrixSub<T, MatrixMxN<T>, E> MatrixMxN<T>::sub(const E& m) const 
	{ return MatrixSub<T, MatrixMxN, E>(*this, m); }

	template <typename T>
	MatrixScalarMul<T, MatrixMxN<T>> MatrixMxN<T>::mul(const T& s) const 
	{ return MatrixScalarMul<T, MatrixMxN>(*this, s); }

	template <typename T>
	template <typename VE>
	MatrixVectorMul<T, MatrixMxN<T>, VE> MatrixMxN<T>::mul(const VectorExpression<T, VE>& v) const 
	{ return MatrixVectorMul<T, MatrixMxN<T>, VE>(*this, v()); }

	template <typename T>
	template <typename E>
	MatrixMul<T, MatrixMxN<T>, E> MatrixMxN<T>::mul(const E& m) const 
	{ return MatrixMul<T, MatrixMxN, E>(*this, m); }

	template <typename T>
	MatrixScalarDiv<T, MatrixMxN<T>> MatrixMxN<T>::div(const T& s) const 
	{ return MatrixScalarDiv<T, MatrixMxN>(*this, s); }

	template <typename T>
	MatrixScalarAdd<T, MatrixMxN<T>> MatrixMxN<T>::radd(const T& s) const 
	{ return MatrixScalarAdd<T, MatrixMxN<T>>(*this, s); }

	template <typename T>
	template <typename E>
	MatrixAdd<T, MatrixMxN<T>, E> MatrixMxN<T>::radd(const E& m) const 
	{ return MatrixAdd<T, MatrixMxN<T>, E>(m, *this); }

	template <typename T>
	MatrixScalarRSub<T, MatrixMxN<T>> MatrixMxN<T>::rsub(const T& s) const 
	{ return MatrixScalarRSub<T, MatrixMxN<T>>(*this, s); }

	template <typename T>
	template <typename E>
	MatrixSub<T, MatrixMxN<T>, E> MatrixMxN<T>::rsub(const E& m) const 
	{ return MatrixSub<T, MatrixMxN<T>, E>(m, *this); }

	template <typename T>
	MatrixScalarMul<T, MatrixMxN<T>> MatrixMxN<T>::rmul(const T& s) const 
	{ return MatrixScalarMul<T, MatrixMxN<T>>(*this, s); }

	template <typename T>
	template <typename E>
	MatrixMul<T, E, MatrixMxN<T>> MatrixMxN<T>::rmul(const E& m) const 
	{ return MatrixMul<T, E, MatrixMxN<T>>(m, *this); }

	template <typename T>
	MatrixScalarRDiv<T, MatrixMxN<T>> MatrixMxN<T>::rdiv(const T& s) const 
	{ return MatrixScalarRDiv<T, MatrixMxN<T>>(*this, s); }

	template <typename T>
	void MatrixMxN<T>::iadd(const T& s) { set(add(s)); }

	template <typename T>
	template <typename E>
	void MatrixMxN<T>::iadd(const E& m) { set(add(m)); }

	template <typename T>
	void MatrixMxN<T>::isub(const T& s) { set(sub(s)); }

	template <typename T>
	template <typename E>
	void MatrixMxN<T>::isub(const E& m) { set(sub(m)); }

	template <typename T>
	void MatrixMxN<T>::imul(const T& s) { set(mul(s)); }

	template <typename T>
	template <typename E>
	void MatrixMxN<T>::imul(const E& m) { MatrixMxN tmp = mul(m); set(tmp); }

	template <typename T>
	void MatrixMxN<T>::idiv(const T& s) { set(div(s)); }

	template <typename T>
	void MatrixMxN<T>::transpose() { set(transposed()); }

	template <typename T>
	void MatrixMxN<T>::invert() 
	{
		assert(isSquare());
		// Computes inverse matrix using Gaussian elimination method.
		// https://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/
		size_t n = rows();
		MatrixMxN& a = *this;
		MatrixMxN rhs = makeIdentity(n);
		for (size_t i = 0; i < n; ++i) 
		{
			// Search for maximum in this column
			T maxEl = std::fabs(a(i, i));
			size_t maxRow = i;
			for (size_t k = i + 1; k < n; ++k) 
			{
				if (std::fabs(a(k, i)) > maxEl) 
				{
					maxEl = std::fabs(a(k, i));
					maxRow = k;
				}
			}
			// Swap maximum row with current row (column by column)
			if (maxRow != i) 
			{
				for (size_t k = i; k < n; ++k) 
				{
					std::swap(a(maxRow, k), a(i, k));
					std::swap(rhs(maxRow, k), rhs(i, k));
				}
			}
			// Make all rows except this one 0 in current column
			for (size_t k = 0; k < n; ++k) 
			{
				if (k == i) 
					continue;
				T c = -a(k, i) / a(i, i);
				for (size_t j = 0; j < n; ++j) 
				{
					rhs(k, j) += c * rhs(i, j);
					if (i == j) 
						a(k, j) = 0;
					else if (i < j) 
						a(k, j) += c * a(i, j);
				}
			}
			// Scale
			for (size_t k = 0; k < n; ++k) 
			{
				T c = 1 / a(k, k);
				for (size_t j = 0; j < n; ++j) 
				{
					a(k, j) *= c;
					rhs(k, j) *= c;
				}
			}
		}
		set(rhs);
	}

	template <typename T>
	T MatrixMxN<T>::sum() const 
	{
		return parallelReduce(kZeroSize, rows() * cols(), T(0),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result += _elements[i];
			return result; }, std::plus<T>());
	}

	template <typename T>
	T MatrixMxN<T>::avg() const { return sum() / (rows() * cols()); }

	template <typename T>
	T MatrixMxN<T>::min() const 
	{
		const T& (*_min)(const T&, const T&) = std::min<T>;
		return parallelReduce(kZeroSize, rows() * cols(),
			std::numeric_limits<T>::max(),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result = std::min(result, _elements[i]);
			return result; }, _min);
	}

	template <typename T>
	T MatrixMxN<T>::max() const 
	{
		const T& (*_max)(const T&, const T&) = std::max<T>;
		return parallelReduce(kZeroSize, rows() * cols(),
			std::numeric_limits<T>::min(),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result = std::max(result, _elements[i]);
			return result; }, _max);
	}

	template <typename T>
	T MatrixMxN<T>::absmin() const 
	{
		return parallelReduce(kZeroSize, rows() * cols(),
			std::numeric_limits<T>::max(),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result = Engine::absmin(result, _elements[i]);
			return result; }, Engine::absmin<T>);
	}

	template <typename T>
	T MatrixMxN<T>::absmax() const 
	{
		return parallelReduce(kZeroSize, rows() * cols(), T(0),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result = Engine::absmax(result, _elements[i]);
			return result; }, Engine::absmax<T>);
	}

	template <typename T>
	T MatrixMxN<T>::trace() const 
	{
		assert(isSquare());
		return parallelReduce(kZeroSize, rows(), T(0),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result += _elements(i, i);
			return result; }, std::plus<T>());
	}

	template <typename T>
	T MatrixMxN<T>::determinant() const 
	{
		assert(isSquare());
		// Computes inverse matrix using Gaussian elimination method.
		// https://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/
		size_t n = rows();
		MatrixMxN a(*this);
		T result = 1;
		for (size_t i = 0; i < n; ++i) 
		{
			// Search for maximum in this column
			T maxEl = std::fabs(a(i, i));
			size_t maxRow = i;
			for (size_t k = i + 1; k < n; ++k) 
			{
				if (std::fabs(a(k, i)) > maxEl) 
				{
					maxEl = std::fabs(a(k, i));
					maxRow = k;
				}
			}
			// Swap maximum row with current row (column by column)
			if (maxRow != i) 
			{
				for (size_t k = i; k < n; ++k) 
					std::swap(a(maxRow, k), a(i, k));
				result *= -1;
			}

			// Make all rows below this one 0 in current column
			for (size_t k = i + 1; k < n; ++k) 
			{
				T c = -a(k, i) / a(i, i);
				for (size_t j = i; j < n; ++j) 
				{
					if (i == j) 
						a(k, j) = 0;
					else 
						a(k, j) += c * a(i, j);
				}
			}
		}
		for (size_t i = 0; i < n; ++i) 
			result *= a(i, i);
		return result;
	}

	template <typename T>
	MatrixDiagonal<T, MatrixMxN<T>> MatrixMxN<T>::diagonal() const 
	{ return MatrixDiagonal<T, MatrixMxN>(*this, true); }

	template <typename T>
	MatrixDiagonal<T, MatrixMxN<T>> MatrixMxN<T>::offDiagonal() const 
	{ return MatrixDiagonal<T, MatrixMxN>(*this, false); }

	template <typename T>
	MatrixTriangular<T, MatrixMxN<T>> MatrixMxN<T>::strictLowerTri() const 
	{ return MatrixTriangular<T, MatrixMxN<T>>(*this, false, true); }

	template <typename T>
	MatrixTriangular<T, MatrixMxN<T>> MatrixMxN<T>::strictUpperTri() const 
	{ return MatrixTriangular<T, MatrixMxN<T>>(*this, true, true); }

	template <typename T>
	MatrixTriangular<T, MatrixMxN<T>> MatrixMxN<T>::lowerTri() const 
	{ return MatrixTriangular<T, MatrixMxN<T>>(*this, false, false); }

	template <typename T>
	MatrixTriangular<T, MatrixMxN<T>> MatrixMxN<T>::upperTri() const 
	{ return MatrixTriangular<T, MatrixMxN<T>>(*this, true, false); }

	template <typename T>
	MatrixMxN<T> MatrixMxN<T>::transposed() const 
	{
		MatrixMxN mt(cols(), rows());
		parallelForEachIndex([&](size_t i, size_t j) { mt(j, i) = (*this)(i, j); });
		return mt;
	}

	template <typename T>
	MatrixMxN<T> MatrixMxN<T>::inverse() const { MatrixMxN mInv(*this); mInv.invert(); return mInv; }

	template <typename T>
	template <typename U>
	MatrixTypeCast<U, MatrixMxN<T>, T> MatrixMxN<T>::castTo() const 
	{ return MatrixTypeCast<U, MatrixMxN, T>(*this); }

	template <typename T>
	template <typename E>
	MatrixMxN<T>& MatrixMxN<T>::operator=(const E& m) { set(m); return *this; }

	template <typename T>
	MatrixMxN<T>& MatrixMxN<T>::operator=(const MatrixMxN& other) { set(other); return *this; }

	template <typename T>
	MatrixMxN<T>& MatrixMxN<T>::operator=(MatrixMxN&& other) 
	{
		_elements = std::move(other._elements);
		return *this;
	}

	template <typename T>
	MatrixMxN<T>& MatrixMxN<T>::operator+=(const T& s) { iadd(s); return *this; }

	template <typename T>
	template <typename E>
	MatrixMxN<T>& MatrixMxN<T>::operator+=(const E& m) { iadd(m); return *this; }

	template <typename T>
	MatrixMxN<T>& MatrixMxN<T>::operator-=(const T& s) { isub(s); return *this; }

	template <typename T>
	template <typename E>
	MatrixMxN<T>& MatrixMxN<T>::operator-=(const E& m) { isub(m); return *this; }

	template <typename T>
	MatrixMxN<T>& MatrixMxN<T>::operator*=(const T& s) { imul(s); return *this; }

	template <typename T>
	template <typename E>
	MatrixMxN<T>& MatrixMxN<T>::operator*=(const E& m) { imul(m); return *this; }

	template <typename T>
	MatrixMxN<T>& MatrixMxN<T>::operator/=(const T& s) { idiv(s); return *this; }

	template <typename T>
	T& MatrixMxN<T>::operator[](size_t i) { return _elements[i]; }

	template <typename T>
	const T& MatrixMxN<T>::operator[](size_t i) const { return _elements[i]; }

	template <typename T>
	T& MatrixMxN<T>::operator()(size_t i, size_t j) { return _elements(j, i); }

	template <typename T>
	const T& MatrixMxN<T>::operator()(size_t i, size_t j) const { return _elements(j, i); }

	template <typename T>
	template <typename E>
	bool MatrixMxN<T>::operator==(const MatrixExpression<T, E>& m) const { return isEqual(m); }

	template <typename T>
	template <typename E>
	bool MatrixMxN<T>::operator!=(const MatrixExpression<T, E>& m) const { return !isEqual(m); }

	template <typename T>
	template <typename Callback>
	void MatrixMxN<T>::forEach(Callback func) const 
	{
		for (size_t i = 0; i < rows(); ++i) 
			for (size_t j = 0; j < cols(); ++j) 
				func((*this)(i, j));
	}

	template <typename T>
	template <typename Callback>
	void MatrixMxN<T>::forEachIndex(Callback func) const 
	{
		for (size_t i = 0; i < rows(); ++i) 
			for (size_t j = 0; j < cols(); ++j) 
				func(i, j);
	}

	template <typename T>
	template <typename Callback>
	void MatrixMxN<T>::parallelForEach(Callback func) 
	{
		parallelFor(kZeroSize, cols(), kZeroSize, rows(),
			[&](size_t j, size_t i) { func((*this)(i, j)); });
	}

	template <typename T>
	template <typename Callback>
	void MatrixMxN<T>::parallelForEachIndex(Callback func) const 
	{
		parallelFor(kZeroSize, cols(), kZeroSize, rows(),
			[&](size_t j, size_t i) { func(i, j); });
	}

	// MARK: Builders

	template <typename T>
	MatrixConstant<T> MatrixMxN<T>::makeZero(size_t m, size_t n) 
	{ return MatrixConstant<T>(m, n, 0); }

	template <typename T>
	MatrixIdentity<T> MatrixMxN<T>::makeIdentity(size_t m) 
	{ return MatrixIdentity<T>(m); }

}