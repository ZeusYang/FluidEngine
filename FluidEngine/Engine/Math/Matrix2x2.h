#pragma once

#include "Vector2.h"
#include "Matrix.h"

#include <array>
#include <limits>
#include <algorithm>
#include <cstring>
#include <utility>

namespace Engine
{
	//!
	//! \brief 2-D matrix class.
	//!
	//! This class is a row-major 2-D matrix class, which means each element of
	//! the matrix is stored in order of (0, 0), (0, 1), (1, 0) and (1, 1).
	//! \tparam T - Type of the element.
	//!
	template <typename T>
	class Matrix<T, 2, 2>
	{
	public:
		static_assert(std::is_floating_point<T>::value,
			"Matrix only can be instantiated with floating point types");

		// MARK: Constructors

		//! Constructs identity matrix.
		Matrix();

		//! Constructs constant value matrix.
		explicit Matrix(T s);

		//! Constructs a matrix with input elements.
		//! \warning Ordering of the input elements is row-major.
		Matrix(T m00, T m01, T m10, T m11);

		//!
		//! \brief Constructs a matrix with given initializer list \p lst.
		//!
		//! This constructor will build a matrix with given initializer list \p lst
		//! such as
		//!
		//! \code{.cpp}
		//! Matrix<float, 2, 2> arr = {
		//!     {1.f, 2.f},
		//!     {9.f, 3.f}
		//! };
		//! \endcode
		//!
		//! Note the initializer also has 2x2 structure.
		//!
		//! \param lst Initializer list that should be copy to the new matrix.
		//!
		template <typename U>
		Matrix(const std::initializer_list<std::initializer_list<U>>& lst);

		//! Constructs a matrix with input matrix.
		Matrix(const Matrix& m);

		//! Constructs a matrix with input array.
		//! \warning Ordering of the input elements is row-major.
		explicit Matrix(const T* arr);

		// MARK: Basic setters

		//! Sets whole matrix with input scalar.
		void set(T s);

		//! Sets this matrix with input elements.
		//! \warning Ordering of the input elements is row-major.
		void set(T m00, T m01, T m10, T m11);

		//!
		//! \brief Sets this matrix with given initializer list \p lst.
		//!
		//! This function will fill the matrix with given initializer list \p lst
		//! such as
		//!
		//! \code{.cpp}
		//! Matrix<float, 2, 2> arr;
		//! arr.set({
		//!     {1, 2},
		//!     {9, 3}
		//! });
		//! \endcode
		//!
		//! Note the initializer also has 2x2 structure.
		//!
		//! \param lst Initializer list that should be copy to the matrix.
		//!
		template <typename U>
		void set(const std::initializer_list<std::initializer_list<U>>& lst);

		//! Copies from input matrix.
		void set(const Matrix& m);

		//! Copies from input array.
		//! \warning Ordering of the input elements is row-major.
		void set(const T* arr);

		//! Sets diagonal elements with input scalar.
		void setDiagonal(T s);

		//! Sets off-diagonal elements with input scalar.
		void setOffDiagonal(T s);

		//! Sets i-th row with input vector.
		void setRow(size_t i, const Vector2<T>& row);

		//! Sets i-th column with input vector.
		void setColumn(size_t i, const Vector2<T>& col);

		// MARK: Basic getters

		//! Returns true if this matrix is similar to the input matrix within the
		//! given tolerance.
		bool isSimilar(const Matrix& m,
			double tol = std::numeric_limits<double>::epsilon()) const;

		//! Returns true if this matrix is a square matrix.
		bool isSquare() const;

		//! Returns number of rows of this matrix.
		size_t rows() const;

		//! Returns number of columns of this matrix.
		size_t cols() const;

		//! Returns data pointer of this matrix.
		T* data();

		//! Returns constant pointer of this matrix.
		const T* data() const;

		// MARK: Binary operator methods - new instance = this instance (+) input
		//! Returns this matrix + input scalar.
		Matrix add(T s) const;

		//! Returns this matrix + input matrix (element-wise).
		Matrix add(const Matrix& m) const;

		//! Returns this matrix - input scalar.
		Matrix sub(T s) const;

		//! Returns this matrix - input matrix (element-wise).
		Matrix sub(const Matrix& m) const;

		//! Returns this matrix * input scalar.
		Matrix mul(T s) const;

		//! Returns this matrix * input vector.
		Vector2<T> mul(const Vector2<T>& v) const;

		//! Returns this matrix * input matrix.
		Matrix mul(const Matrix& m) const;

		//! Returns this matrix / input scalar.
		Matrix div(T s) const;

		// MARK: Binary operator methods - new instance = input (+) this instance
		//! Returns input scalar + this matrix.
		Matrix radd(T s) const;

		//! Returns input matrix + this matrix (element-wise).
		Matrix radd(const Matrix& m) const;

		//! Returns input scalar - this matrix.
		Matrix rsub(T s) const;

		//! Returns input matrix - this matrix (element-wise).
		Matrix rsub(const Matrix& m) const;

		//! Returns input scalar * this matrix.
		Matrix rmul(T s) const;

		//! Returns input matrix * this matrix.
		Matrix rmul(const Matrix& m) const;

		//! Returns input scalar / this matrix.
		Matrix rdiv(T s) const;

		// MARK: Augmented operator methods - this instance (+)= input
		//! Adds input scalar to this matrix.
		void iadd(T s);

		//! Adds input matrix to this matrix (element-wise).
		void iadd(const Matrix& m);

		//! Subtracts input scalar from this matrix.
		void isub(T s);

		//! Subtracts input matrix from this matrix (element-wise).
		void isub(const Matrix& m);

		//! Multiplies input scalar to this matrix.
		void imul(T s);

		//! Multiplies input matrix to this matrix.
		void imul(const Matrix& m);

		//! Divides this matrix with input scalar.
		void idiv(T s);

		// MARK: Modifiers
		//! Transposes this matrix.
		void transpose();

		//! Inverts this matrix.
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
		T trace() const;

		//! Returns determinant of this matrix.
		T determinant() const;

		//! Returns diagonal part of this matrix.
		Matrix diagonal() const;

		//! Returns off-diagonal part of this matrix.
		Matrix offDiagonal() const;

		//! Returns strictly lower triangle part of this matrix.
		Matrix strictLowerTri() const;

		//! Returns strictly upper triangle part of this matrix.
		Matrix strictUpperTri() const;

		//! Returns lower triangle part of this matrix (including the diagonal).
		Matrix lowerTri() const;

		//! Returns upper triangle part of this matrix (including the diagonal).
		Matrix upperTri() const;

		//! Returns transposed matrix.
		Matrix transposed() const;

		//! Returns inverse matrix.
		Matrix inverse() const;

		//! Returns Frobenius norm.
		T frobeniusNorm() const;

		template <typename U>
		Matrix<U, 2, 2> castTo() const;

		// MARK: Setter operators
		//! Assigns input matrix.
		Matrix& operator=(const Matrix& m);

		//! Addition assignment with input scalar.
		Matrix& operator+=(T s);

		//! Addition assignment with input matrix (element-wise).
		Matrix& operator+=(const Matrix& m);

		//! Subtraction assignment with input scalar.
		Matrix& operator-=(T s);

		//! Subtraction assignment with input matrix (element-wise).
		Matrix& operator-=(const Matrix& m);

		//! Multiplication assignment with input scalar.
		Matrix& operator*=(T s);

		//! Multiplication assignment with input matrix.
		Matrix& operator*=(const Matrix& m);

		//! Division assignment with input scalar.
		Matrix& operator/=(T s);

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
		bool operator==(const Matrix& m) const;

		//! Returns true if is not equal to m.
		bool operator!=(const Matrix& m) const;

		// MARK: Helpers
		//! Sets all matrix entries to zero.
		static Matrix makeZero();

		//! Makes all diagonal elements to 1, and other elements to 0.
		static Matrix makeIdentity();

		//! Makes scale matrix.
		static Matrix makeScaleMatrix(T sx, T sy);

		//! Makes scale matrix.
		static Matrix makeScaleMatrix(const Vector2<T>& s);

		//! Makes rotation matrix.
		//! \warning Input angle should be radian.
		static Matrix makeRotationMatrix(const T& rad);

	private:
		std::array<T, 4> _elements;

	};

	//! Type alias for 2x2 matrix.
	template <typename T>
	using Matrix2x2 = Matrix<T, 2, 2>;

	// MARK: Operator overloadings
	//! Returns a matrix with opposite sign.
	template <typename T>
	Matrix2x2<T> operator-(const Matrix2x2<T>& a);

	//! Returns a + b (element-size).
	template <typename T>
	Matrix2x2<T> operator+(const Matrix2x2<T>& a, const Matrix2x2<T>& b);

	//! Returns a + b', where every element of matrix b' is b.
	template <typename T>
	Matrix2x2<T> operator+(const Matrix2x2<T>& a, const T& b);

	//! Returns a' + b, where every element of matrix a' is a.
	template <typename T>
	Matrix2x2<T> operator+(const T& a, const Matrix2x2<T>& b);

	//! Returns a - b (element-size).
	template <typename T>
	Matrix2x2<T> operator-(const Matrix2x2<T>& a, const Matrix2x2<T>& b);

	//! Returns a - b', where every element of matrix b' is b.
	template <typename T>
	Matrix2x2<T> operator-(const Matrix2x2<T>& a, T b);

	//! Returns a' - b, where every element of matrix a' is a.
	template <typename T>
	Matrix2x2<T> operator-(T a, const Matrix2x2<T>& b);

	//! Returns a * b', where every element of matrix b' is b.
	template <typename T>
	Matrix2x2<T> operator*(const Matrix2x2<T>& a, T b);

	//! Returns a' * b, where every element of matrix a' is a.
	template <typename T>
	Matrix2x2<T> operator*(T a, const Matrix2x2<T>& b);

	//! Returns a * b.
	template <typename T>
	Vector2<T> operator*(const Matrix2x2<T>& a, const Vector2<T>& b);

	//! Returns a * b.
	template <typename T>
	Matrix2x2<T> operator*(const Matrix2x2<T>& a, const Matrix2x2<T>& b);

	//! Returns a' / b, where every element of matrix a' is a.
	template <typename T>
	Matrix2x2<T> operator/(const Matrix2x2<T>& a, T b);

	//! Returns a / b', where every element of matrix b' is b.
	template <typename T>
	Matrix2x2<T> operator/(const T& a, const Matrix2x2<T>& b);

	//! Float-type 2x2 matrix.
	typedef Matrix2x2<float> Matrix2x2F;

	//! Double-type 2x2 matrix.
	typedef Matrix2x2<double> Matrix2x2D;

	//! -------------------------Definition-----------------------------

	// MARK: CTOR/DTOR
	template <typename T>
	Matrix<T, 2, 2>::Matrix() { set(1, 0, 0, 1); }

	template <typename T>
	Matrix<T, 2, 2>::Matrix(T s) { set(s); }

	template <typename T>
	Matrix<T, 2, 2>::Matrix(T m00, T m01, T m10, T m11) { set(m00, m01, m10, m11); }

	template <typename T>
	template <typename U>
	Matrix<T, 2, 2>::Matrix(const std::initializer_list<std::initializer_list<U>>& lst) { set(lst); }

	template <typename T>
	Matrix<T, 2, 2>::Matrix(const Matrix& m) { set(m); }

	template <typename T>
	Matrix<T, 2, 2>::Matrix(const T* arr) { set(arr); }

	// MARK: Basic setters
	template <typename T>
	void Matrix<T, 2, 2>::set(T s) { _elements[0] = _elements[1] = _elements[2] = _elements[3] = s;}

	template <typename T>
	void Matrix<T, 2, 2>::set(T m00, T m01, T m10, T m11) 
	{
		_elements[0] = m00; _elements[1] = m01;
		_elements[2] = m10; _elements[3] = m11;
	}

	template <typename T>
	template <typename U>
	void Matrix<T, 2, 2>::set(const std::initializer_list<std::initializer_list<U>>& lst) 
	{
		size_t height = lst.size();
		size_t width = (height > 0) ? lst.begin()->size() : 0;
		assert(width == 2);
		assert(height == 2);
		auto rowIter = lst.begin();
		for (size_t i = 0; i < height; ++i) 
		{
			assert(width == rowIter->size());
			auto colIter = rowIter->begin();
			for (size_t j = 0; j < width; ++j) 
			{
				(*this)(i, j) = static_cast<T>(*colIter);
				++colIter;
			}
			++rowIter;
		}
	}

	template <typename T>
	void Matrix<T, 2, 2>::set(const Matrix& m) { memcpy(_elements.data(), m._elements.data(), sizeof(T) * 4); }

	template <typename T>
	void Matrix<T, 2, 2>::set(const T* arr) { memcpy(_elements.data(), arr, sizeof(T) * 4); }

	template <typename T>
	void Matrix<T, 2, 2>::setDiagonal(T s) { _elements[0] = _elements[3] = s; }

	template <typename T>
	void Matrix<T, 2, 2>::setOffDiagonal(T s) { _elements[1] = _elements[2] = s; }

	template <typename T>
	void Matrix<T, 2, 2>::setRow(size_t i, const Vector<T, 2>& row) { _elements[2 * i] = row.x; _elements[2 * i + 1] = row.y; }

	template <typename T>
	void Matrix<T, 2, 2>::setColumn(size_t j, const Vector<T, 2>& col) { _elements[j] = col.x; _elements[j + 2] = col.y; }

	// MARK: Basic getters
	template <typename T>
	bool Matrix<T, 2, 2>::isSimilar(const Matrix& m, double tol) const 
	{
		return (std::fabs(_elements[0] - m._elements[0]) < tol) &&
			(std::fabs(_elements[1] - m._elements[1]) < tol) &&
			(std::fabs(_elements[2] - m._elements[2]) < tol) &&
			(std::fabs(_elements[3] - m._elements[3]) < tol);
	}

	template <typename T>
	bool Matrix<T, 2, 2>::isSquare() const { return true; }

	template <typename T>
	size_t Matrix<T, 2, 2>::rows() const { return 2; }

	template <typename T>
	size_t Matrix<T, 2, 2>::cols() const { return 2; }

	template <typename T>
	T* Matrix<T, 2, 2>::data() { return _elements.data(); }

	template <typename T>
	const T* Matrix<T, 2, 2>::data() const { return _elements.data(); }

	// MARK: Binary operator methods - new instance = this instance (+) input
	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::add(T s) const 
	{
		return Matrix(_elements[0] + s, _elements[1] + s, _elements[2] + s, _elements[3] + s);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::add(const Matrix& m) const 
	{
		return Matrix(_elements[0] + m._elements[0], _elements[1] + m._elements[1],
			_elements[2] + m._elements[2], _elements[3] + m._elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::sub(T s) const 
	{
		return Matrix(_elements[0] - s, _elements[1] - s, _elements[2] - s, _elements[3] - s);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::sub(const Matrix& m) const {
		return Matrix(_elements[0] - m._elements[0], _elements[1] - m._elements[1],
			_elements[2] - m._elements[2], _elements[3] - m._elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::mul(T s) const 
	{
		return Matrix(_elements[0] * s, _elements[1] * s, _elements[2] * s, _elements[3] * s);
	}

	template <typename T>
	Vector<T, 2> Matrix<T, 2, 2>::mul(const Vector<T, 2>& v) const 
	{
		return Vector<T, 2>(_elements[0] * v.x + _elements[1] * v.y, _elements[2] * v.x + _elements[3] * v.y);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::mul(const Matrix& m) const 
	{
		return Matrix(
			_elements[0] * m._elements[0] + _elements[1] * m._elements[2],
			_elements[0] * m._elements[1] + _elements[1] * m._elements[3],
			_elements[2] * m._elements[0] + _elements[3] * m._elements[2],
			_elements[2] * m._elements[1] + _elements[3] * m._elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::div(T s) const 
	{
		return Matrix(_elements[0] / s, _elements[1] / s, _elements[2] / s, _elements[3] / s);
	}

	// MARK: Binary operator methods - new instance = input (+) this instance
	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::radd(T s) const 
	{
		return Matrix(s + _elements[0], s + _elements[1], s + _elements[2], s + _elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::radd(const Matrix& m) const 
	{
		return Matrix(m._elements[0] + _elements[0], m._elements[1] + _elements[1],
			m._elements[2] + _elements[2], m._elements[3] + _elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::rsub(T s) const 
	{
		return Matrix(s - _elements[0], s - _elements[1], s - _elements[2], s - _elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::rsub(const Matrix& m) const 
	{
		return Matrix(m._elements[0] - _elements[0], m._elements[1] - _elements[1],
			m._elements[2] - _elements[2], m._elements[3] - _elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::rmul(T s) const 
	{
		return Matrix(s * _elements[0], s * _elements[1], s * _elements[2],
			s * _elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::rmul(const Matrix& m) const { return m.mul(*this); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::rdiv(T s) const 
	{
		return Matrix(s / _elements[0], s / _elements[1], s / _elements[2], s / _elements[3]);
	}

	// MARK: Augmented operator methods - this instance (+)= input
	template <typename T>
	void Matrix<T, 2, 2>::iadd(T s) 
	{
		_elements[0] += s; _elements[1] += s;
		_elements[2] += s; _elements[3] += s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::iadd(const Matrix& m) 
	{
		_elements[0] += m._elements[0]; _elements[1] += m._elements[1];
		_elements[2] += m._elements[2]; _elements[3] += m._elements[3];
	}

	template <typename T>
	void Matrix<T, 2, 2>::isub(T s) 
	{
		_elements[0] -= s; _elements[1] -= s;
		_elements[2] -= s; _elements[3] -= s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::isub(const Matrix& m) 
	{
		_elements[0] -= m._elements[0]; _elements[1] -= m._elements[1];
		_elements[2] -= m._elements[2]; _elements[3] -= m._elements[3];
	}

	template <typename T>
	void Matrix<T, 2, 2>::imul(T s) 
	{
		_elements[0] *= s; _elements[1] *= s;
		_elements[2] *= s; _elements[3] *= s;
	}

	template <typename T>
	void Matrix<T, 2, 2>::imul(const Matrix& m) { set(mul(m)); }

	template <typename T>
	void Matrix<T, 2, 2>::idiv(T s) 
	{
		_elements[0] /= s; _elements[1] /= s;
		_elements[2] /= s; _elements[3] /= s;
	}

	// MARK: Modifiers
	template <typename T>
	void Matrix<T, 2, 2>::transpose() { std::swap(_elements[1], _elements[2]); }

	template <typename T>
	void Matrix<T, 2, 2>::invert() 
	{
		T d = determinant();
		Matrix m;
		m._elements[0] = _elements[3];
		m._elements[1] = -_elements[1];
		m._elements[2] = -_elements[2];
		m._elements[3] = _elements[0];
		m.idiv(d);
		set(m);
	}

	// MARK: Complex getters
	template <typename T>
	T Matrix<T, 2, 2>::sum() const 
	{
		T s = 0;
		for (int i = 0; i < 4; ++i) 
			s += _elements[i];
		return s;
	}

	template <typename T>
	T Matrix<T, 2, 2>::avg() const { return sum() / 4; }

	template <typename T>
	T Matrix<T, 2, 2>::min() const 
	{
		return std::min(std::min(_elements[0], _elements[1]), std::min(_elements[2], _elements[3]));
	}

	template <typename T>
	T Matrix<T, 2, 2>::max() const 
	{
		return std::max(std::max(_elements[0], _elements[1]), std::max(_elements[2], _elements[3]));
	}

	template <typename T>
	T Matrix<T, 2, 2>::absmin() const 
	{
		return Engine::absmin(Engine::absmin(_elements[0], _elements[1]), Engine::absmin(_elements[2], _elements[3]));
	}

	template <typename T>
	T Matrix<T, 2, 2>::absmax() const 
	{
		return Engine::absmax(Engine::absmax(_elements[0], _elements[1]), Engine::absmax(_elements[2], _elements[3]));
	}

	template <typename T>
	T Matrix<T, 2, 2>::trace() const { return _elements[0] + _elements[3]; }

	template <typename T>
	T Matrix<T, 2, 2>::determinant() const { return _elements[0] * _elements[3] - _elements[1] * _elements[2]; }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::diagonal() const { return Matrix(_elements[0], 0, 0, _elements[3]); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::offDiagonal() const { return Matrix(0, _elements[1], _elements[2], 0); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::strictLowerTri() const { return Matrix(0, 0, _elements[2], 0); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::strictUpperTri() const { return Matrix(0, _elements[1], 0, 0); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::lowerTri() const { return Matrix(_elements[0], 0, _elements[2], _elements[3]); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::upperTri() const { return Matrix(_elements[0], _elements[1], 0, _elements[3]); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::transposed() const 
	{
		return Matrix(_elements[0], _elements[2], _elements[1], _elements[3]);
	}

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::inverse() const { Matrix m(*this); m.invert(); return m; }

	template <typename T>
	T Matrix<T, 2, 2>::frobeniusNorm() const 
	{
		return std::sqrt(_elements[0] * _elements[0] + _elements[1] * _elements[1] +
			_elements[2] * _elements[2] + _elements[3] * _elements[3]);
	}

	template <typename T>
	template <typename U>
	Matrix<U, 2, 2> Matrix<T, 2, 2>::castTo() const 
	{
		return Matrix<U, 2, 2>(
			static_cast<U>(_elements[0]), static_cast<U>(_elements[1]),
			static_cast<U>(_elements[2]), static_cast<U>(_elements[3]));
	}

	// MARK: Setter operators
	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator=(const Matrix& m) { set(m); return *this; }

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator+=(T s) { iadd(s); return *this; }

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator+=(const Matrix& m) { iadd(m); return *this; }

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator-=(T s) { isub(s); return *this; }

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator-=(const Matrix& m) { isub(m); return *this; }

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator*=(T s) { imul(s); return *this; }

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator*=(const Matrix& m) { imul(m); return *this; }

	template <typename T>
	Matrix<T, 2, 2>& Matrix<T, 2, 2>::operator/=(T s) { idiv(s); return *this; }

	template <typename T>
	bool Matrix<T, 2, 2>::operator==(const Matrix& m) const 
	{
		return _elements[0] == m._elements[0] && _elements[1] == m._elements[1] &&
			_elements[2] == m._elements[2] && _elements[3] == m._elements[3];
	}

	template <typename T>
	bool Matrix<T, 2, 2>::operator!=(const Matrix& m) const 
	{
		return _elements[0] != m._elements[0] || _elements[1] != m._elements[1] ||
			_elements[2] != m._elements[2] || _elements[3] != m._elements[3];
	}

	// MARK: Getter operators
	template <typename T>
	T& Matrix<T, 2, 2>::operator[](size_t i) { return _elements[i]; }

	template <typename T>
	const T& Matrix<T, 2, 2>::operator[](size_t i) const { return _elements[i]; }

	template <typename T>
	T& Matrix<T, 2, 2>::operator()(size_t i, size_t j) { return _elements[2 * i + j]; }

	template <typename T>
	const T& Matrix<T, 2, 2>::operator()(size_t i, size_t j) const { return _elements[2 * i + j]; }

	// MARK: Helpers
	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::makeZero() { return Matrix(0, 0, 0, 0); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::makeIdentity() { return Matrix(1, 0, 0, 1); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::makeScaleMatrix(T sx, T sy) { return Matrix(sx, 0, 0, sy); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::makeScaleMatrix(const Vector<T, 2>& s) { return makeScaleMatrix(s.x, s.y); }

	template <typename T>
	Matrix<T, 2, 2> Matrix<T, 2, 2>::makeRotationMatrix(const T& rad) 
	{
		return Matrix(std::cos(rad), -std::sin(rad), std::sin(rad), std::cos(rad));
	}

	// MARK: Operator overloadings
	template <typename T>
	Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2>& a) { return a.mul(-1); }

	template <typename T>
	Matrix<T, 2, 2> operator+(const Matrix<T, 2, 2>& a, const Matrix<T, 2, 2>& b) { return a.add(b); }

	template <typename T>
	Matrix<T, 2, 2> operator+(const Matrix<T, 2, 2>& a, T b) { return a.add(b); }

	template <typename T>
	Matrix<T, 2, 2> operator+(T a, const Matrix<T, 2, 2>& b) { return b.radd(a); }

	template <typename T>
	Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2>& a, const Matrix<T, 2, 2>& b) { return a.sub(b); }

	template <typename T>
	Matrix<T, 2, 2> operator-(const Matrix<T, 2, 2>& a, T b) { return a.sub(b); }

	template <typename T>
	Matrix<T, 2, 2> operator-(T a, const Matrix<T, 2, 2>& b) { return b.rsub(a); }

	template <typename T>
	Matrix<T, 2, 2> operator*(const Matrix<T, 2, 2>& a, T b) { return a.mul(b); }

	template <typename T>
	Matrix<T, 2, 2> operator*(T a, const Matrix<T, 2, 2>& b) { return b.rmul(a); }

	template <typename T>
	Vector<T, 3> operator*(const Matrix<T, 2, 2>& a, const Vector<T, 3>& b) { return a.mul(b); }

	template <typename T>
	Vector<T, 2> operator*(const Matrix<T, 2, 2>& a, const Vector<T, 2>& b) { return a.mul(b); }

	template <typename T>
	Matrix<T, 2, 2> operator*(const Matrix<T, 2, 2>& a, const Matrix<T, 2, 2>& b) { return a.mul(b); }

	template <typename T>
	Matrix<T, 2, 2> operator/(const Matrix<T, 2, 2>& a, T b) { return a.div(b); }

	template <typename T>
	Matrix<T, 2, 2> operator/(T a, const Matrix<T, 2, 2>& b) { return b.rdiv(a); }

}