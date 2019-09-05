#pragma once

#include "Matrix.h"
#include "Vector3.h"
#include "../Utils/MathUtils.h"

#include <array>
#include <limits>
#include <cstring>
#include <utility>
#include <algorithm>

namespace Engine
{
	//!
	//! \brief 3-D matrix class.
	//!
	//! This class is a row-major 3-D matrix class, which means each element of
	//! the matrix is stored in order of (0, 0), (0, 1), (0, 2), (1, 0), (1, 1),
	//! (1, 2), (2, 0), (2, 1), and (2, 2).
	//!
	//! \tparam T - Type of the element.
	//!
	template <typename T>
	class Matrix<T, 3, 3>
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
		Matrix(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22);

		//!
		//! \brief Constructs a matrix with given initializer list \p lst.
		//!
		//! This constructor will build a matrix with given initializer list \p lst
		//! such as
		//!
		//! \code{.cpp}
		//! Matrix<float, 3, 3> arr = {
		//!     {1.f, 2.f, 4.f},
		//!     {9.f, 3.f, 5.f},
		//!     {4.f, 8.f, 1.f}
		//! };
		//! \endcode
		//!
		//! Note the initializer also has 3x3 structure.
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
		void set(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22);

		//!
		//! \brief Sets a matrix with given initializer list \p lst.
		//!
		//! This function will fill the matrix with given initializer list \p lst
		//! such as
		//!
		//! \code{.cpp}
		//! Matrix<float, 3, 3> arr;
		//! arr.set({
		//!     {1.f, 2.f, 4.f},
		//!     {9.f, 3.f, 5.f},
		//!     {4.f, 8.f, 1.f}
		//! });
		//! \endcode
		//!
		//! Note the initializer also has 3x3 structure.
		//!
		//! \param lst Initializer list that should be copy to the new matrix.
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
		void setRow(size_t i, const Vector3<T>& row);

		//! Sets i-th column with input vector.
		void setColumn(size_t i, const Vector3<T>& col);

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
		Vector3<T> mul(const Vector3<T>& v) const;

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
		Matrix<U, 3, 3> castTo() const;

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
		static Matrix makeScaleMatrix(T sx, T sy, T sz);

		//! Makes scale matrix.
		static Matrix makeScaleMatrix(const Vector3<T>& s);

		//! Makes rotation matrix.
		//! \warning Input angle should be radian.
		static Matrix makeRotationMatrix(const Vector3<T>& axis, T rad);

	private:
		std::array<T, 9> _elements;
	};

	//! Type alias for 3x3 matrix.
	template <typename T>
	using Matrix3x3 = Matrix<T, 3, 3>;

	// Operator overloadings
	//! Returns a matrix with opposite sign.
	template <typename T>
	Matrix3x3<T> operator-(const Matrix3x3<T>& a);

	//! Returns a + b (element-size).
	template <typename T>
	Matrix3x3<T> operator+(const Matrix3x3<T>& a, const Matrix3x3<T>& b);

	//! Returns a + b', where every element of matrix b' is b.
	template <typename T>
	Matrix3x3<T> operator+(const Matrix3x3<T>& a, T b);

	//! Returns a' + b, where every element of matrix a' is a.
	template <typename T>
	Matrix3x3<T> operator+(T a, const Matrix3x3<T>& b);

	//! Returns a - b (element-size).
	template <typename T>
	Matrix3x3<T> operator-(const Matrix3x3<T>& a, const Matrix3x3<T>& b);

	//! Returns a - b', where every element of matrix b' is b.
	template <typename T>
	Matrix3x3<T> operator-(const Matrix3x3<T>& a, T b);

	//! Returns a' - b, where every element of matrix a' is a.
	template <typename T>
	Matrix3x3<T> operator-(T a, const Matrix3x3<T>& b);

	//! Returns a * b', where every element of matrix b' is b.
	template <typename T>
	Matrix3x3<T> operator*(const Matrix3x3<T>& a, T b);

	//! Returns a' * b, where every element of matrix a' is a.
	template <typename T>
	Matrix3x3<T> operator*(T a, const Matrix3x3<T>& b);

	//! Returns a * b.
	template <typename T>
	Vector3<T> operator*(const Matrix3x3<T>& a, const Vector3<T>& b);

	//! Returns a * b.
	template <typename T>
	Matrix3x3<T> operator*(const Matrix3x3<T>& a, const Matrix3x3<T>& b);

	//! Returns a' / b, where every element of matrix a' is a.
	template <typename T>
	Matrix3x3<T> operator/(const Matrix3x3<T>& a, T b);

	//! Returns a / b', where every element of matrix b' is b.
	template <typename T>
	Matrix3x3<T> operator/(T a, const Matrix3x3<T>& b);

	//! Float-type 3x3 matrix.
	typedef Matrix3x3<float> Matrix3x3F;

	//! Double-type 3x3 matrix.
	typedef Matrix3x3<double> Matrix3x3D;
	
	//! -------------------------Definition---------------------------------

	// MARK: CTOR/DTOR
	template <typename T>
	Matrix<T, 3, 3>::Matrix() { set(1, 0, 0, 0, 1, 0, 0, 0, 1); }

	template <typename T>
	Matrix<T, 3, 3>::Matrix(T s) { set(s); }

	template <typename T>
	Matrix<T, 3, 3>::Matrix(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) 
	{
		set(m00, m01, m02, m10, m11, m12, m20, m21, m22);
	}

	template <typename T>
	template <typename U>
	Matrix<T, 3, 3>::Matrix(const std::initializer_list<std::initializer_list<U>>& lst) { set(lst); }

	template <typename T>
	Matrix<T, 3, 3>::Matrix(const Matrix& m) { set(m); }

	template <typename T>
	Matrix<T, 3, 3>::Matrix(const T* arr) { set(arr); }

	// MARK: Basic setters
	template <typename T>
	void Matrix<T, 3, 3>::set(T s) 
	{
		_elements[0] = _elements[3] = _elements[6] = _elements[1] = _elements[4] =
			_elements[7] = _elements[2] = _elements[5] = _elements[8] = s;
	}

	template <typename T>
	void Matrix<T, 3, 3>::set(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) 
	{
		_elements[0] = m00; _elements[1] = m01; _elements[2] = m02;
		_elements[3] = m10; _elements[4] = m11; _elements[5] = m12;
		_elements[6] = m20; _elements[7] = m21; _elements[8] = m22;
	}

	template <typename T>
	template <typename U>
	void Matrix<T, 3, 3>::set(const std::initializer_list<std::initializer_list<U>>& lst) 
	{
		size_t height = lst.size();
		size_t width = (height > 0) ? lst.begin()->size() : 0;
		assert(width == 3);
		assert(height == 3);
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
	void Matrix<T, 3, 3>::set(const Matrix& m) { memcpy(_elements.data(), m._elements.data(), sizeof(T) * 9); }

	template <typename T>
	void Matrix<T, 3, 3>::set(const T* arr) { memcpy(_elements.data(), arr, sizeof(T) * 9); }

	template <typename T>
	void Matrix<T, 3, 3>::setDiagonal(T s) { _elements[0] = _elements[4] = _elements[8] = s; }

	template <typename T>
	void Matrix<T, 3, 3>::setOffDiagonal(T s) 
	{
		_elements[1] = _elements[2] = _elements[3] = _elements[5] = _elements[6] = _elements[7] = s;
	}

	template <typename T>
	void Matrix<T, 3, 3>::setRow(size_t i, const Vector<T, 3>& row) 
	{
		_elements[3 * i] = row.x; _elements[3 * i + 1] = row.y; _elements[3 * i + 2] = row.z;
	}

	template <typename T>
	void Matrix<T, 3, 3>::setColumn(size_t j, const Vector<T, 3>& col) 
	{
		_elements[j] = col.x; _elements[j + 3] = col.y; _elements[j + 6] = col.z;
	}

	// MARK: Basic getters
	template <typename T>
	bool Matrix<T, 3, 3>::isSimilar(const Matrix& m, double tol) const 
	{
		return std::fabs(_elements[0] - m._elements[0]) < tol &&
			std::fabs(_elements[1] - m._elements[1]) < tol &&
			std::fabs(_elements[2] - m._elements[2]) < tol &&
			std::fabs(_elements[3] - m._elements[3]) < tol &&
			std::fabs(_elements[4] - m._elements[4]) < tol &&
			std::fabs(_elements[5] - m._elements[5]) < tol &&
			std::fabs(_elements[6] - m._elements[6]) < tol &&
			std::fabs(_elements[7] - m._elements[7]) < tol &&
			std::fabs(_elements[8] - m._elements[8]) < tol;
	}

	template <typename T>
	bool Matrix<T, 3, 3>::isSquare() const { return true; }

	template <typename T>
	size_t Matrix<T, 3, 3>::rows() const { return 3; }

	template <typename T>
	size_t Matrix<T, 3, 3>::cols() const { return 3; }

	template <typename T>
	T* Matrix<T, 3, 3>::data() { return _elements.data(); }

	template <typename T>
	const T* Matrix<T, 3, 3>::data() const { return _elements.data(); }

	// MARK: Binary operator methods - new instance = this instance (+) input
	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::add(T s) const 
	{
		return Matrix(_elements[0] + s, _elements[1] + s, _elements[2] + s,
			_elements[3] + s, _elements[4] + s, _elements[5] + s,
			_elements[6] + s, _elements[7] + s, _elements[8] + s);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::add(const Matrix& m) const 
	{
		return Matrix(_elements[0] + m._elements[0], _elements[1] + m._elements[1],
			_elements[2] + m._elements[2], _elements[3] + m._elements[3],
			_elements[4] + m._elements[4], _elements[5] + m._elements[5],
			_elements[6] + m._elements[6], _elements[7] + m._elements[7],
			_elements[8] + m._elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::sub(T s) const 
	{
		return Matrix(_elements[0] - s, _elements[1] - s, _elements[2] - s,
			_elements[3] - s, _elements[4] - s, _elements[5] - s,
			_elements[6] - s, _elements[7] - s, _elements[8] - s);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::sub(const Matrix& m) const 
	{
		return Matrix(_elements[0] - m._elements[0], _elements[1] - m._elements[1],
			_elements[2] - m._elements[2], _elements[3] - m._elements[3],
			_elements[4] - m._elements[4], _elements[5] - m._elements[5],
			_elements[6] - m._elements[6], _elements[7] - m._elements[7],
			_elements[8] - m._elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::mul(T s) const 
	{
		return Matrix(_elements[0] * s, _elements[1] * s, _elements[2] * s,
			_elements[3] * s, _elements[4] * s, _elements[5] * s,
			_elements[6] * s, _elements[7] * s, _elements[8] * s);
	}

	template <typename T>
	Vector<T, 3> Matrix<T, 3, 3>::mul(const Vector<T, 3>& v) const 
	{
		return Vector<T, 3>(_elements[0] * v.x + _elements[1] * v.y + _elements[2] * v.z,
			_elements[3] * v.x + _elements[4] * v.y + _elements[5] * v.z,
			_elements[6] * v.x + _elements[7] * v.y + _elements[8] * v.z);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::mul(const Matrix& m) const 
	{
		return Matrix(
			_elements[0] * m._elements[0] + _elements[1] * m._elements[3] +
			_elements[2] * m._elements[6],
			_elements[0] * m._elements[1] + _elements[1] * m._elements[4] +
			_elements[2] * m._elements[7],
			_elements[0] * m._elements[2] + _elements[1] * m._elements[5] +
			_elements[2] * m._elements[8],

			_elements[3] * m._elements[0] + _elements[4] * m._elements[3] +
			_elements[5] * m._elements[6],
			_elements[3] * m._elements[1] + _elements[4] * m._elements[4] +
			_elements[5] * m._elements[7],
			_elements[3] * m._elements[2] + _elements[4] * m._elements[5] +
			_elements[5] * m._elements[8],

			_elements[6] * m._elements[0] + _elements[7] * m._elements[3] +
			_elements[8] * m._elements[6],
			_elements[6] * m._elements[1] + _elements[7] * m._elements[4] +
			_elements[8] * m._elements[7],
			_elements[6] * m._elements[2] + _elements[7] * m._elements[5] +
			_elements[8] * m._elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::div(T s) const 
	{
		return Matrix(_elements[0] / s, _elements[1] / s, _elements[2] / s,
			_elements[3] / s, _elements[4] / s, _elements[5] / s,
			_elements[6] / s, _elements[7] / s, _elements[8] / s);
	}

	// MARK: Binary operator methods - new instance = input (+) this instance
	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::radd(T s) const 
	{
		return Matrix(s + _elements[0], s + _elements[1], s + _elements[2],
			s + _elements[3], s + _elements[4], s + _elements[5],
			s + _elements[6], s + _elements[7], s + _elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::radd(const Matrix& m) const 
	{
		return Matrix(m._elements[0] + _elements[0], m._elements[1] + _elements[1],
			m._elements[2] + _elements[2], m._elements[3] + _elements[3],
			m._elements[4] + _elements[4], m._elements[5] + _elements[5],
			m._elements[6] + _elements[6], m._elements[7] + _elements[7],
			m._elements[8] + _elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::rsub(T s) const 
	{
		return Matrix(s - _elements[0], s - _elements[1], s - _elements[2],
			s - _elements[3], s - _elements[4], s - _elements[5],
			s - _elements[6], s - _elements[7], s - _elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::rsub(const Matrix& m) const 
	{
		return Matrix(m._elements[0] - _elements[0], m._elements[1] - _elements[1],
			m._elements[2] - _elements[2], m._elements[3] - _elements[3],
			m._elements[4] - _elements[4], m._elements[5] - _elements[5],
			m._elements[6] - _elements[6], m._elements[7] - _elements[7],
			m._elements[8] - _elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::rmul(T s) const 
	{
		return Matrix(s * _elements[0], s * _elements[1], s * _elements[2],
			s * _elements[3], s * _elements[4], s * _elements[5],
			s * _elements[6], s * _elements[7], s * _elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::rmul(const Matrix& m) const { return m.mul(*this); }

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::rdiv(T s) const 
	{
		return Matrix(s / _elements[0], s / _elements[1], s / _elements[2],
			s / _elements[3], s / _elements[4], s / _elements[5],
			s / _elements[6], s / _elements[7], s / _elements[8]);
	}

	// MARK: Augmented operator methods - this instance (+)= input
	template <typename T>
	void Matrix<T, 3, 3>::iadd(T s) 
	{
		_elements[0] += s; _elements[1] += s; _elements[2] += s;
		_elements[3] += s; _elements[4] += s; _elements[5] += s;
		_elements[6] += s; _elements[7] += s; _elements[8] += s;
	}

	template <typename T>
	void Matrix<T, 3, 3>::iadd(const Matrix& m) 
	{
		_elements[0] += m._elements[0]; _elements[1] += m._elements[1]; _elements[2] += m._elements[2];
		_elements[3] += m._elements[3]; _elements[4] += m._elements[4]; _elements[5] += m._elements[5];
		_elements[6] += m._elements[6]; _elements[7] += m._elements[7]; _elements[8] += m._elements[8];
	}

	template <typename T>
	void Matrix<T, 3, 3>::isub(T s) 
	{
		_elements[0] -= s; _elements[1] -= s; _elements[2] -= s;
		_elements[3] -= s; _elements[4] -= s; _elements[5] -= s;
		_elements[6] -= s; _elements[7] -= s; _elements[8] -= s;
	}

	template <typename T>
	void Matrix<T, 3, 3>::isub(const Matrix& m) 
	{
		_elements[0] -= m._elements[0]; _elements[1] -= m._elements[1]; _elements[2] -= m._elements[2];
		_elements[3] -= m._elements[3]; _elements[4] -= m._elements[4]; _elements[5] -= m._elements[5];
		_elements[6] -= m._elements[6]; _elements[7] -= m._elements[7]; _elements[8] -= m._elements[8];
	}

	template <typename T>
	void Matrix<T, 3, 3>::imul(T s) 
	{
		_elements[0] *= s; _elements[1] *= s; _elements[2] *= s;
		_elements[3] *= s; _elements[4] *= s; _elements[5] *= s;
		_elements[6] *= s; _elements[7] *= s; _elements[8] *= s;
	}

	template <typename T>
	void Matrix<T, 3, 3>::imul(const Matrix& m) { set(mul(m)); }

	template <typename T>
	void Matrix<T, 3, 3>::idiv(T s) 
	{
		_elements[0] /= s; _elements[1] /= s; _elements[2] /= s;
		_elements[3] /= s; _elements[4] /= s; _elements[5] /= s;
		_elements[6] /= s; _elements[7] /= s; _elements[8] /= s;
	}

	// MARK: Modifiers
	template <typename T>
	void Matrix<T, 3, 3>::transpose() 
	{
		std::swap(_elements[1], _elements[3]);
		std::swap(_elements[2], _elements[6]);
		std::swap(_elements[5], _elements[7]);
	}

	template <typename T>
	void Matrix<T, 3, 3>::invert() 
	{
		T d = determinant();
		Matrix m;
		m._elements[0] = _elements[4] * _elements[8] - _elements[5] * _elements[7];
		m._elements[1] = _elements[2] * _elements[7] - _elements[1] * _elements[8];
		m._elements[2] = _elements[1] * _elements[5] - _elements[2] * _elements[4];
		m._elements[3] = _elements[5] * _elements[6] - _elements[3] * _elements[8];
		m._elements[4] = _elements[0] * _elements[8] - _elements[2] * _elements[6];
		m._elements[5] = _elements[2] * _elements[3] - _elements[0] * _elements[5];
		m._elements[6] = _elements[3] * _elements[7] - _elements[4] * _elements[6];
		m._elements[7] = _elements[1] * _elements[6] - _elements[0] * _elements[7];
		m._elements[8] = _elements[0] * _elements[4] - _elements[1] * _elements[3];
		m.idiv(d);
		set(m);
	}

	// MARK: Complex getters
	template <typename T>
	T Matrix<T, 3, 3>::sum() const 
	{
		T s = 0;
		for (int i = 0; i < 9; ++i) 
			s += _elements[i];
		return s;
	}

	template <typename T>
	T Matrix<T, 3, 3>::avg() const { return sum() / 9; }

	template <typename T>
	T Matrix<T, 3, 3>::min() const { return minn(data(), 9); }

	template <typename T>
	T Matrix<T, 3, 3>::max() const { return maxn(data(), 9); }

	template <typename T>
	T Matrix<T, 3, 3>::absmin() const { return absminn(data(), 9); }

	template <typename T>
	T Matrix<T, 3, 3>::absmax() const { return absmaxn(data(), 9); }

	template <typename T>
	T Matrix<T, 3, 3>::trace() const { return _elements[0] + _elements[4] + _elements[8]; }

	template <typename T>
	T Matrix<T, 3, 3>::determinant() const 
	{
		return _elements[0] * _elements[4] * _elements[8] -
			_elements[0] * _elements[5] * _elements[7] +
			_elements[1] * _elements[5] * _elements[6] -
			_elements[1] * _elements[3] * _elements[8] +
			_elements[2] * _elements[3] * _elements[7] -
			_elements[2] * _elements[4] * _elements[6];
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::diagonal() const 
	{
		return Matrix(_elements[0], 0, 0, 0, _elements[4], 0, 0, 0, _elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::offDiagonal() const 
	{
		return Matrix(0, _elements[1], _elements[2], _elements[3], 0, _elements[5],
			_elements[6], _elements[7], 0);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::strictLowerTri() const 
	{
		return Matrix(0, 0, 0, _elements[3], 0, 0, _elements[6], _elements[7], 0);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::strictUpperTri() const 
	{
		return Matrix(0, _elements[1], _elements[2], 0, 0, _elements[5], 0, 0, 0);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::lowerTri() const 
	{
		return Matrix(_elements[0], 0, 0, _elements[3], _elements[4], 0,
			_elements[6], _elements[7], _elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::upperTri() const 
	{
		return Matrix(_elements[0], _elements[1], _elements[2], 0, _elements[4],
			_elements[5], 0, 0, _elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::transposed() const 
	{
		return Matrix(_elements[0], _elements[3], _elements[6], _elements[1],
			_elements[4], _elements[7], _elements[2], _elements[5], _elements[8]);
	}

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::inverse() const { Matrix m(*this); m.invert(); return m; }

	template <typename T>
	T Matrix<T, 3, 3>::frobeniusNorm() const 
	{
		return std::sqrt(_elements[0] * _elements[0] + _elements[1] * _elements[1] +
			_elements[2] * _elements[2] + _elements[3] * _elements[3] +
			_elements[4] * _elements[4] + _elements[5] * _elements[5] +
			_elements[6] * _elements[6] + _elements[7] * _elements[7] +
			_elements[8] * _elements[8]);
	}

	template <typename T>
	template <typename U>
	Matrix<U, 3, 3> Matrix<T, 3, 3>::castTo() const 
	{
		return Matrix<U, 3, 3>(
			static_cast<U>(_elements[0]), static_cast<U>(_elements[1]),
			static_cast<U>(_elements[2]), static_cast<U>(_elements[3]),
			static_cast<U>(_elements[4]), static_cast<U>(_elements[5]),
			static_cast<U>(_elements[6]), static_cast<U>(_elements[7]),
			static_cast<U>(_elements[8]));
	}

	// MARK: Setter operators
	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator=(const Matrix& m) { set(m); return *this; }

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator+=(T s) { iadd(s); return *this; }

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator+=(const Matrix& m) { iadd(m); return *this; }

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator-=(T s) { isub(s); return *this; }

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator-=(const Matrix& m) { isub(m); return *this; }

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator*=(T s) { imul(s); return *this; }

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator*=(const Matrix& m) { imul(m); return *this; }

	template <typename T>
	Matrix<T, 3, 3>& Matrix<T, 3, 3>::operator/=(T s) { idiv(s); return *this; }

	template <typename T>
	bool Matrix<T, 3, 3>::operator==(const Matrix& m) const 
	{
		return _elements[0] == m._elements[0] && _elements[1] == m._elements[1] &&
			_elements[2] == m._elements[2] && _elements[3] == m._elements[3] &&
			_elements[4] == m._elements[4] && _elements[5] == m._elements[5] &&
			_elements[6] == m._elements[6] && _elements[7] == m._elements[7] &&
			_elements[8] == m._elements[8];
	}

	template <typename T>
	bool Matrix<T, 3, 3>::operator!=(const Matrix& m) const 
	{
		return _elements[0] != m._elements[0] || _elements[1] != m._elements[1] ||
			_elements[2] != m._elements[2] || _elements[3] != m._elements[3] ||
			_elements[4] != m._elements[4] || _elements[5] != m._elements[5] ||
			_elements[6] != m._elements[6] || _elements[7] != m._elements[7] ||
			_elements[8] != m._elements[8];
	}

	// MARK: Getter operators
	template <typename T>
	T& Matrix<T, 3, 3>::operator[](size_t i) { return _elements[i]; }

	template <typename T>
	const T& Matrix<T, 3, 3>::operator[](size_t i) const { return _elements[i]; }

	template <typename T>
	T& Matrix<T, 3, 3>::operator()(size_t i, size_t j) { return _elements[3 * i + j]; }

	template <typename T>
	const T& Matrix<T, 3, 3>::operator()(size_t i, size_t j) const { return _elements[3 * i + j]; }

	// MARK: Helpers
	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::makeZero() { return Matrix(0, 0, 0, 0, 0, 0, 0, 0, 0); }

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::makeIdentity() { return Matrix(1, 0, 0, 0, 1, 0, 0, 0, 1); }

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::makeScaleMatrix(T sx, T sy, T sz) { return Matrix(sx, 0, 0, 0, sy, 0, 0, 0, sz); }

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::makeScaleMatrix(const Vector<T, 3>& s) { return makeScaleMatrix(s.x, s.y, s.z); }

	template <typename T>
	Matrix<T, 3, 3> Matrix<T, 3, 3>::makeRotationMatrix(const Vector<T, 3>& axis, T rad) 
	{
		return Matrix(
			1 + (1 - std::cos(rad)) * (axis.x * axis.x - 1),
			-axis.z * std::sin(rad) + (1 - std::cos(rad)) * axis.x * axis.y,
			axis.y * std::sin(rad) + (1 - std::cos(rad)) * axis.x * axis.z,

			axis.z * std::sin(rad) + (1 - std::cos(rad)) * axis.x * axis.y,
			1 + (1 - std::cos(rad)) * (axis.y * axis.y - 1),
			-axis.x * std::sin(rad) + (1 - std::cos(rad)) * axis.y * axis.z,

			-axis.y * std::sin(rad) + (1 - std::cos(rad)) * axis.x * axis.z,
			axis.x * std::sin(rad) + (1 - std::cos(rad)) * axis.y * axis.z,
			1 + (1 - std::cos(rad)) * (axis.z * axis.z - 1));
	}

	// MARK: Operator overloadings
	template <typename T>
	Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3>& a) { return a.mul(-1); }

	template <typename T>
	Matrix<T, 3, 3> operator+(const Matrix<T, 3, 3>& a, const Matrix<T, 3, 3>& b) { return a.add(b); }

	template <typename T>
	Matrix<T, 3, 3> operator+(const Matrix<T, 3, 3>& a, T b) { return a.add(b); }

	template <typename T>
	Matrix<T, 3, 3> operator+(T a, const Matrix<T, 3, 3>& b) { return b.radd(a); }

	template <typename T>
	Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3>& a, const Matrix<T, 3, 3>& b) { return a.sub(b); }

	template <typename T>
	Matrix<T, 3, 3> operator-(const Matrix<T, 3, 3>& a, T b) { return a.sub(b); }

	template <typename T>
	Matrix<T, 3, 3> operator-(T a, const Matrix<T, 3, 3>& b) { return b.rsub(a); }

	template <typename T>
	Matrix<T, 3, 3> operator*(const Matrix<T, 3, 3>& a, T b) { return a.mul(b); }

	template <typename T>
	Matrix<T, 3, 3> operator*(T a, const Matrix<T, 3, 3>& b) { return b.rmul(a); }

	template <typename T>
	Vector<T, 3> operator*(const Matrix<T, 3, 3>& a, const Vector<T, 3>& b) { return a.mul(b); }

	template <typename T>
	Matrix<T, 3, 3> operator*(const Matrix<T, 3, 3>& a, const Matrix<T, 3, 3>& b) { return a.mul(b); }

	template <typename T>
	Matrix<T, 3, 3> operator/(const Matrix<T, 3, 3>& a, T b) { return a.div(b); }

	template <typename T>
	Matrix<T, 3, 3> operator/(T a, const Matrix<T, 3, 3>& b) { return b.rdiv(a); }

}