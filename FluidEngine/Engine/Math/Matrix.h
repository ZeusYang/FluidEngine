#pragma once

#include <array>
#include <type_traits>

#include "../Utils/Macros.h"
#include "MatrixExpression.h"

namespace Engine
{
	//!
	//! \brief Static-sized M x N matrix class.
	//!
	//! This class defines M x N row-major matrix data where its size is determined
	//! statically at compile time.
	//!
	//! \tparam T - Real number type.
	//! \tparam M - Number of rows.
	//! \tparam N - Number of columns.
	//!
	template <typename T, size_t M, size_t N>
	class Matrix final : public MatrixExpression<T, Matrix<T, M, N>>
	{
	public:
		static_assert(
			M > 0,
			"Number of rows for static-sized matrix should be greater than zero.");
		static_assert(
			N > 0,
			"Number of columns for static-sized matrix should be greater than "
			"zero.");
		static_assert(!(M == 2 && N == 2) && !(M == 3 && N == 3) &&
			!(M == 4 && N == 4),
			"Use specialized matrix for 2z2, 3x3, and 4x4 matricies.");
		static_assert(std::is_floating_point<T>::value,
			"Matrix only can be instantiated with floating point types");

		typedef std::array<T, M * N> ContainerType;
		typedef typename ContainerType::iterator Iterator;
		typedef typename ContainerType::const_iterator ConstIterator;

		//! Default constructor.
		//! \warning This constructor will create zero matrix.
		Matrix();

		//! Constructs matrix instance with parameters.
		template <typename... Params>
		explicit Matrix(Params... params);

		//!
		//! \brief Constructs a matrix with given initializer list \p lst.
		//!
		//! This constructor will build a matrix with given initializer list \p lst
		//! such as
		//!
		//! \code{.cpp}
		//! Matrix<float, 3, 4> mat = {
		//!     {1.f, 2.f, 4.f, 3.f},
		//!     {9.f, 3.f, 5.f, 1.f},
		//!     {4.f, 8.f, 1.f, 5.f}
		//! };
		//! \endcode
		//!
		//! \param lst Initializer list that should be copy to the new matrix.
		//!
		Matrix(const std::initializer_list<std::initializer_list<T>>& lst);

		//! Constructs a matrix with expression template.
		template <typename E>
		Matrix(const MatrixExpression<T, E>& other);

		//! Copy constructor.
		Matrix(const Matrix& other);

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
		//! Matrix<float, 3, 4> mat;
		//! mat.set({
		//!     {1.f, 2.f, 4.f, 3.f},
		//!     {9.f, 3.f, 5.f, 1.f},
		//!     {4.f, 8.f, 1.f, 5.f}
		//! });
		//! \endcode
		//!
		//! \param lst Initializer list that should be copy to the new matrix.
		//!
		void set(const std::initializer_list<std::initializer_list<T>>& lst);

		//! Copies from input matrix expression.
		template <typename E>
		void set(const MatrixExpression<T, E>& other);

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
		constexpr bool isSquare() const;

		//! Returns the size of this matrix.
		constexpr Size2 size() const;

		//! Returns number of rows of this matrix.
		constexpr size_t rows() const;

		//! Returns number of columns of this matrix.
		constexpr size_t cols() const;

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
		MatrixScalarAdd<T, Matrix> add(const T& s) const;

		//! Returns this matrix + input matrix (element-wise).
		template <typename E>
		MatrixAdd<T, Matrix, E> add(const E& m) const;

		//! Returns this matrix - input scalar.
		MatrixScalarSub<T, Matrix> sub(const T& s) const;

		//! Returns this matrix - input matrix (element-wise).
		template <typename E>
		MatrixSub<T, Matrix, E> sub(const E& m) const;

		//! Returns this matrix * input scalar.
		MatrixScalarMul<T, Matrix> mul(const T& s) const;

		//! Returns this matrix * input vector.
		template <typename VE>
		MatrixVectorMul<T, Matrix, VE> mul(const VectorExpression<T, VE>& v) const;

		//! Returns this matrix * input matrix.
		template <size_t L>
		MatrixMul<T, Matrix, Matrix<T, N, L>> mul(const Matrix<T, N, L>& m) const;

		//! Returns this matrix / input scalar.
		MatrixScalarDiv<T, Matrix> div(const T& s) const;

		// MARK: Binary operator methods - new instance = input (+) this instance
		//! Returns input scalar + this matrix.
		MatrixScalarAdd<T, Matrix> radd(const T& s) const;

		//! Returns input matrix + this matrix (element-wise).
		template <typename E>
		MatrixAdd<T, Matrix, E> radd(const E& m) const;

		//! Returns input scalar - this matrix.
		MatrixScalarRSub<T, Matrix> rsub(const T& s) const;

		//! Returns input matrix - this matrix (element-wise).
		template <typename E>
		MatrixSub<T, Matrix, E> rsub(const E& m) const;

		//! Returns input scalar * this matrix.
		MatrixScalarMul<T, Matrix> rmul(const T& s) const;

		//! Returns input matrix * this matrix.
		template <size_t L>
		MatrixMul<T, Matrix<T, N, L>, Matrix> rmul(const Matrix<T, N, L>& m) const;

		//! Returns input matrix / this scalar.
		MatrixScalarRDiv<T, Matrix> rdiv(const T& s) const;

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
		MatrixDiagonal<T, Matrix> diagonal() const;

		//! Returns off-diagonal part of this matrix.
		MatrixDiagonal<T, Matrix> offDiagonal() const;

		//! Returns strictly lower triangle part of this matrix.
		MatrixTriangular<T, Matrix> strictLowerTri() const;

		//! Returns strictly upper triangle part of this matrix.
		MatrixTriangular<T, Matrix> strictUpperTri() const;

		//! Returns lower triangle part of this matrix (including the diagonal).
		MatrixTriangular<T, Matrix> lowerTri() const;

		//! Returns upper triangle part of this matrix (including the diagonal).
		MatrixTriangular<T, Matrix> upperTri() const;

		//! Returns transposed matrix.
		Matrix<T, N, M> transposed() const;

		//! Returns inverse matrix.
		Matrix inverse() const;

		template <typename U>
		MatrixTypeCast<U, Matrix, T> castTo() const;

		// MARK: Setter operators

		//! Assigns input matrix.
		template <typename E>
		Matrix& operator=(const E& m);

		//! Copies to this matrix.
		Matrix& operator=(const Matrix& other);

		//! Addition assignment with input scalar.
		Matrix& operator+=(const T& s);

		//! Addition assignment with input matrix (element-wise).
		template <typename E>
		Matrix& operator+=(const E& m);

		//! Subtraction assignment with input scalar.
		Matrix& operator-=(const T& s);

		//! Subtraction assignment with input matrix (element-wise).
		template <typename E>
		Matrix& operator-=(const E& m);

		//! Multiplication assignment with input scalar.
		Matrix& operator*=(const T& s);

		//! Multiplication assignment with input matrix.
		template <typename E>
		Matrix& operator*=(const E& m);

		//! Division assignment with input scalar.
		Matrix& operator/=(const T& s);

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

		// MARK: Builders

		//! Makes a M x N matrix with zeros.
		static MatrixConstant<T> makeZero();

		//! Makes a M x N matrix with all diagonal elements to 1, and other elements
		//! to 0.
		static MatrixIdentity<T> makeIdentity();

	private:
		ContainerType _elements;

		template <typename... Params>
		void setRowAt(size_t i, T v, Params... params);
		void setRowAt(size_t i, T v);

	};



	//! ----------------------------------------------Definition----------------------------------------

	template <typename T, size_t M, size_t N>
	Matrix<T, M, N>::Matrix() 
	{
		for (auto& elem : _elements) 
			elem = 0;
	}

	template <typename T, size_t M, size_t N>
	template <typename... Params>
	Matrix<T, M, N>::Matrix(Params... params) 
	{
		static_assert(sizeof...(params) == M * N, "Invalid number of elements.");
		setRowAt(0, params...);
	}

	template <typename T, size_t M, size_t N>
	Matrix<T, M, N>::Matrix(const std::initializer_list<std::initializer_list<T>>& lst) { set(lst); }

	template <typename T, size_t M, size_t N>
	template <typename E>
	Matrix<T, M, N>::Matrix(const MatrixExpression<T, E>& other) { set(other); }

	template <typename T, size_t M, size_t N>
	Matrix<T, M, N>::Matrix(const Matrix& other) { set(other); }

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::set(const T& s) { _elements.fill(s); }

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::set(const std::initializer_list<std::initializer_list<T>>& lst) 
	{
		size_t rows = lst.size();
		size_t cols = (rows > 0) ? lst.begin()->size() : 0;
		assert(rows == M);
		assert(cols == N);

		auto rowIter = lst.begin();
		for (size_t i = 0; i < rows; ++i) 
		{
			assert(cols == rowIter->size());
			auto colIter = rowIter->begin();
			for (size_t j = 0; j < cols; ++j) 
			{
				(*this)(i, j) = *colIter;
				++colIter;
			}
			++rowIter;
		}
	}

	template <typename T, size_t M, size_t N>
	template <typename E>
	void Matrix<T, M, N>::set(const MatrixExpression<T, E>& other) 
	{
		const E& expression = other();
		forEachIndex([&](size_t i, size_t j) { (*this)(i, j) = expression(i, j); });
	}

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::setDiagonal(const T& s) 
	{
		const size_t l = std::min(rows(), cols());
		for (size_t i = 0; i < l; ++i) 
			(*this)(i, i) = s;
	}

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::setOffDiagonal(const T& s) 
	{
		forEachIndex([&](size_t i, size_t j) { if (i != j)  (*this)(i, j) = s;});
	}

	template <typename T, size_t M, size_t N>
	template <typename E>
	void Matrix<T, M, N>::setRow(size_t i, const VectorExpression<T, E>& row) 
	{
		assert(cols() == row.size());
		const E& e = row();
		for (size_t j = 0; j < N; ++j) 
			(*this)(i, j) = e[j];
	}

	template <typename T, size_t M, size_t N>
	template <typename E>
	void Matrix<T, M, N>::setColumn(size_t j, const VectorExpression<T, E>& col) 
	{
		assert(rows() == col.size());
		const E& e = col();
		for (size_t i = 0; i < M; ++i) 
			(*this)(i, j) = e[j];
	}

	template <typename T, size_t M, size_t N>
	template <typename E>
	bool Matrix<T, M, N>::isEqual(const MatrixExpression<T, E>& other) const 
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

	template <typename T, size_t M, size_t N>
	template <typename E>
	bool Matrix<T, M, N>::isSimilar(const MatrixExpression<T, E>& other, double tol) const 
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

	template <typename T, size_t M, size_t N>
	constexpr bool Matrix<T, M, N>::isSquare() const { return M == N; }

	template <typename T, size_t M, size_t N>
	constexpr Size2 Matrix<T, M, N>::size() const { return Size2(M, N); }

	template <typename T, size_t M, size_t N>
	constexpr size_t Matrix<T, M, N>::rows() const { return M; }

	template <typename T, size_t M, size_t N>
	constexpr size_t Matrix<T, M, N>::cols() const { return N; }

	template <typename T, size_t M, size_t N>
	T* Matrix<T, M, N>::data() { return _elements.data(); }

	template <typename T, size_t M, size_t N>
	const T* const Matrix<T, M, N>::data() const { return _elements.data(); }

	template <typename T, size_t M, size_t N>
	typename Matrix<T, M, N>::Iterator Matrix<T, M, N>::begin() { return _elements.begin(); }

	template <typename T, size_t M, size_t N>
	typename Matrix<T, M, N>::ConstIterator Matrix<T, M, N>::begin() const { return _elements.begin(); }

	template <typename T, size_t M, size_t N>
	typename Matrix<T, M, N>::Iterator Matrix<T, M, N>::end() { return _elements.end(); }

	template <typename T, size_t M, size_t N>
	typename Matrix<T, M, N>::ConstIterator Matrix<T, M, N>::end() const { return _elements.end(); }

	template <typename T, size_t M, size_t N>
	MatrixScalarAdd<T, Matrix<T, M, N>> Matrix<T, M, N>::add(const T& s) const { return MatrixScalarAdd<T, Matrix<T, M, N>>(*this, s); }

	template <typename T, size_t M, size_t N>
	template <typename E>
	MatrixAdd<T, Matrix<T, M, N>, E> Matrix<T, M, N>::add(const E& m) const 
	{
		return MatrixAdd<T, Matrix, E>(*this, m);
	}

	template <typename T, size_t M, size_t N>
	MatrixScalarSub<T, Matrix<T, M, N>> Matrix<T, M, N>::sub(const T& s) const 
	{
		return MatrixScalarSub<T, Matrix<T, M, N>>(*this, s);
	}

	template <typename T, size_t M, size_t N>
	template <typename E>
	MatrixSub<T, Matrix<T, M, N>, E> Matrix<T, M, N>::sub(const E& m) const 
	{
		return MatrixSub<T, Matrix, E>(*this, m);
	}

	template <typename T, size_t M, size_t N>
	MatrixScalarMul<T, Matrix<T, M, N>> Matrix<T, M, N>::mul(const T& s) const 
	{
		return MatrixScalarMul<T, Matrix>(*this, s);
	}

	template <typename T, size_t M, size_t N>
	template <typename VE>
	MatrixVectorMul<T, Matrix<T, M, N>, VE> Matrix<T, M, N>::mul(const VectorExpression<T, VE>& v) const 
	{
		return MatrixVectorMul<T, Matrix<T, M, N>, VE>(*this, v());
	}

	template <typename T, size_t M, size_t N>
	template <size_t L>
	MatrixMul<T, Matrix<T, M, N>, Matrix<T, N, L>> Matrix<T, M, N>::mul(const Matrix<T, N, L>& m) const 
	{
		return MatrixMul<T, Matrix, Matrix<T, N, L>>(*this, m);
	}

	template <typename T, size_t M, size_t N>
	MatrixScalarDiv<T, Matrix<T, M, N>> Matrix<T, M, N>::div(const T& s) const 
	{
		return MatrixScalarDiv<T, Matrix>(*this, s);
	}

	template <typename T, size_t M, size_t N>
	MatrixScalarAdd<T, Matrix<T, M, N>> Matrix<T, M, N>::radd(const T& s) const 
	{
		return MatrixScalarAdd<T, Matrix<T, M, N>>(*this, s);
	}

	template <typename T, size_t M, size_t N>
	template <typename E>
	MatrixAdd<T, Matrix<T, M, N>, E> Matrix<T, M, N>::radd(const E& m) const 
	{
		return MatrixAdd<T, Matrix<T, M, N>, E>(m, *this);
	}

	template <typename T, size_t M, size_t N>
	MatrixScalarRSub<T, Matrix<T, M, N>> Matrix<T, M, N>::rsub(const T& s) const 
	{
		return MatrixScalarRSub<T, Matrix<T, M, N>>(*this, s);
	}

	template <typename T, size_t M, size_t N>
	template <typename E>
	MatrixSub<T, Matrix<T, M, N>, E> Matrix<T, M, N>::rsub(const E& m) const 
	{
		return MatrixSub<T, Matrix<T, M, N>, E>(m, *this);
	}

	template <typename T, size_t M, size_t N>
	MatrixScalarMul<T, Matrix<T, M, N>> Matrix<T, M, N>::rmul(const T& s) const 
	{
		return MatrixScalarMul<T, Matrix<T, M, N>>(*this, s);
	}

	template <typename T, size_t M, size_t N>
	template <size_t L>
	MatrixMul<T, Matrix<T, N, L>, Matrix<T, M, N>> Matrix<T, M, N>::rmul(const Matrix<T, N, L>& m) const 
	{
		return MatrixMul<T, Matrix<T, N, L>, Matrix>(m, *this);
	}

	template <typename T, size_t M, size_t N>
	MatrixScalarRDiv<T, Matrix<T, M, N>> Matrix<T, M, N>::rdiv(const T& s) const 
	{
		return MatrixScalarRDiv<T, Matrix<T, M, N>>(*this, s);
	}

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::iadd(const T& s) { set(add(s)); }

	template <typename T, size_t M, size_t N>
	template <typename E>
	void Matrix<T, M, N>::iadd(const E& m) { set(add(m)); }

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::isub(const T& s) { set(sub(s)); }

	template <typename T, size_t M, size_t N>
	template <typename E>
	void Matrix<T, M, N>::isub(const E& m) { set(sub(m)); }

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::imul(const T& s) { set(mul(s)); }

	template <typename T, size_t M, size_t N>
	template <typename E>
	void Matrix<T, M, N>::imul(const E& m) { Matrix tmp = mul(m); set(tmp); }

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::idiv(const T& s) { set(div(s)); }

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::transpose() { set(transposed()); }

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::invert() 
	{
		assert(isSquare());
		// Computes inverse matrix using Gaussian elimination method.
		// https://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/
		size_t n = rows();
		Matrix& a = *this;
		Matrix rhs = makeIdentity();
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
				for (size_t k = 0; k < n; ++k) 
					std::swap(rhs(maxRow, k), rhs(i, k));
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

	template <typename T, size_t M, size_t N>
	T Matrix<T, M, N>::sum() const 
	{
		T ret = 0;
		for (auto v : _elements) 
			ret += v;
		return ret;
	}

	template <typename T, size_t M, size_t N>
	T Matrix<T, M, N>::avg() const { return sum() / (rows() * cols()); }

	template <typename T, size_t M, size_t N>
	T Matrix<T, M, N>::min() const 
	{
		T ret = _elements.front();
		for (auto v : _elements) 
			ret = std::min(ret, v);
		return ret;
	}

	template <typename T, size_t M, size_t N>
	T Matrix<T, M, N>::max() const 
	{
		T ret = _elements.front();
		for (auto v : _elements) 
			ret = std::max(ret, v);
		return ret;
	}

	template <typename T, size_t M, size_t N>
	T Matrix<T, M, N>::absmin() const 
	{
		T ret = _elements.front();
		for (auto v : _elements) 
			ret = Engine::absmin(ret, v);
		return ret;
	}

	template <typename T, size_t M, size_t N>
	T Matrix<T, M, N>::absmax() const 
	{
		T ret = _elements.front();
		for (auto v : _elements) 
			ret = Engine::absmax(ret, v);
		return ret;
	}

	template <typename T, size_t M, size_t N>
	T Matrix<T, M, N>::trace() const 
	{
		assert(isSquare());
		T ret = 0;
		for (size_t i = 0; i < M; ++i) 
			ret += (*this)(i, i);
		return ret;
	}

	template <typename T, size_t M, size_t N>
	T Matrix<T, M, N>::determinant() const {
		assert(isSquare());
		// Computes inverse matrix using Gaussian elimination method.
		// https://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/
		size_t n = rows();
		Matrix a(*this);
		T result = 1;
		for (size_t i = 0; i < n; ++i) {
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

	template <typename T, size_t M, size_t N>
	MatrixDiagonal<T, Matrix<T, M, N>> Matrix<T, M, N>::diagonal() const 
	{
		return MatrixDiagonal<T, Matrix>(*this, true);
	}

	template <typename T, size_t M, size_t N>
	MatrixDiagonal<T, Matrix<T, M, N>> Matrix<T, M, N>::offDiagonal() const 
	{
		return MatrixDiagonal<T, Matrix>(*this, false);
	}

	template <typename T, size_t M, size_t N>
	MatrixTriangular<T, Matrix<T, M, N>> Matrix<T, M, N>::strictLowerTri() const 
	{
		return MatrixTriangular<T, Matrix<T, M, N>>(*this, false, true);
	}

	template <typename T, size_t M, size_t N>
	MatrixTriangular<T, Matrix<T, M, N>> Matrix<T, M, N>::strictUpperTri() const 
	{
		return MatrixTriangular<T, Matrix<T, M, N>>(*this, true, true);
	}

	template <typename T, size_t M, size_t N>
	MatrixTriangular<T, Matrix<T, M, N>> Matrix<T, M, N>::lowerTri() const 
	{
		return MatrixTriangular<T, Matrix<T, M, N>>(*this, false, false);
	}

	template <typename T, size_t M, size_t N>
	MatrixTriangular<T, Matrix<T, M, N>> Matrix<T, M, N>::upperTri() const 
	{
		return MatrixTriangular<T, Matrix<T, M, N>>(*this, true, false);
	}

	template <typename T, size_t M, size_t N>
	Matrix<T, N, M> Matrix<T, M, N>::transposed() const 
	{
		Matrix<T, N, M> mt;
		forEachIndex([&](size_t i, size_t j) { mt(j, i) = (*this)(i, j); });
		return mt;
	}

	template <typename T, size_t M, size_t N>
	Matrix<T, M, N> Matrix<T, M, N>::inverse() const { Matrix mInv(*this); mInv.invert(); return mInv; }

	template <typename T, size_t M, size_t N>
	template <typename U>
	MatrixTypeCast<U, Matrix<T, M, N>, T> Matrix<T, M, N>::castTo() const 
	{
		return MatrixTypeCast<U, Matrix, T>(*this);
	}

	template <typename T, size_t M, size_t N>
	template <typename E>
	Matrix<T, M, N>& Matrix<T, M, N>::operator=(const E& m) { set(m); return *this; }

	template <typename T, size_t M, size_t N>
	Matrix<T, M, N>& Matrix<T, M, N>::operator=(const Matrix& other) { set(other); return *this; }

	template <typename T, size_t M, size_t N>
	Matrix<T, M, N>& Matrix<T, M, N>::operator+=(const T& s) { iadd(s); return *this; }

	template <typename T, size_t M, size_t N>
	template <typename E>
	Matrix<T, M, N>& Matrix<T, M, N>::operator+=(const E& m) { iadd(m); return *this; }

	template <typename T, size_t M, size_t N>
	Matrix<T, M, N>& Matrix<T, M, N>::operator-=(const T& s) { isub(s); return *this; }

	template <typename T, size_t M, size_t N>
	template <typename E>
	Matrix<T, M, N>& Matrix<T, M, N>::operator-=(const E& m) { isub(m); return *this; }

	template <typename T, size_t M, size_t N>
	Matrix<T, M, N>& Matrix<T, M, N>::operator*=(const T& s) { imul(s); return *this; }

	template <typename T, size_t M, size_t N>
	template <typename E>
	Matrix<T, M, N>& Matrix<T, M, N>::operator*=(const E& m) { imul(m); return *this; }

	template <typename T, size_t M, size_t N>
	Matrix<T, M, N>& Matrix<T, M, N>::operator/=(const T& s) { idiv(s); return *this; }

	template <typename T, size_t M, size_t N>
	T& Matrix<T, M, N>::operator[](size_t i) { return _elements[i]; }

	template <typename T, size_t M, size_t N>
	const T& Matrix<T, M, N>::operator[](size_t i) const { return _elements[i]; }

	template <typename T, size_t M, size_t N>
	T& Matrix<T, M, N>::operator()(size_t i, size_t j) { return _elements[i * N + j]; }

	template <typename T, size_t M, size_t N>
	const T& Matrix<T, M, N>::operator()(size_t i, size_t j) const { return _elements[i * N + j]; }

	template <typename T, size_t M, size_t N>
	template <typename E>
	bool Matrix<T, M, N>::operator==(const MatrixExpression<T, E>& m) const { return isEqual(m); }

	template <typename T, size_t M, size_t N>
	template <typename E>
	bool Matrix<T, M, N>::operator!=(const MatrixExpression<T, E>& m) const { return !isEqual(m); }

	template <typename T, size_t M, size_t N>
	template <typename Callback>
	void Matrix<T, M, N>::forEach(Callback func) const 
	{
		for (size_t i = 0; i < rows(); ++i) 
			for (size_t j = 0; j < cols(); ++j) 
				func((*this)(i, j));
	}

	template <typename T, size_t M, size_t N>
	template <typename Callback>
	void Matrix<T, M, N>::forEachIndex(Callback func) const 
	{
		for (size_t i = 0; i < rows(); ++i) 
			for (size_t j = 0; j < cols(); ++j) 
				func(i, j);
	}

	template <typename T, size_t M, size_t N>
	MatrixConstant<T> Matrix<T, M, N>::makeZero() 
	{
		return MatrixConstant<T>(M, N, 0);
	}

	template <typename T, size_t M, size_t N>
	MatrixIdentity<T> Matrix<T, M, N>::makeIdentity() 
	{
		static_assert(M == N, "Should be a square matrix.");
		return MatrixIdentity<T>(M);
	}

	template <typename T, size_t M, size_t N>
	template <typename... Params>
	void Matrix<T, M, N>::setRowAt(size_t i, T v, Params... params) 
	{
		_elements[i] = v;
		setRowAt(i + 1, params...);
	}

	template <typename T, size_t M, size_t N>
	void Matrix<T, M, N>::setRowAt(size_t i, T v) { _elements[i] = v; }

}