#pragma once

#include <limits>
#include <algorithm>

#include "Vector.h"

namespace Engine
{
	//!
	//! \brief 2-D vector class.
	//!
	//! This class defines simple 2-D vector data.
	//!
	//! \tparam T - Type of the element
	//!
	template <typename T>
	class Vector<T, 2> final
	{
	public:
		static_assert(std::is_floating_point<T>::value,
			"Vector only can be instantiated with floating point types");

		//! X (or the first) component of the vector.
		T x;
		//! Y (or the second) component of the vector.
		T y;

		// MARK: Constructors

		//! Constructs default vector (0, 0).
		constexpr Vector() : x(0), y(0) {}

		//! Constructs vector with given parameters \p x_ and \p y_.
		constexpr Vector(T x_, T y_) : x(x_), y(y_) {}

		//! Constructs vector with initializer list.
		template <typename U>
		Vector(const std::initializer_list<U>& lst);

		//! Copy constructor.
		constexpr Vector(const Vector& v) : x(v.x), y(v.y) {}

		// MARK: Basic setters

		//! Set both x and y components to \p s.
		void set(T s);

		//! Set x and y components with given parameters.
		void set(T x, T y);

		//! Set x and y components with given initializer list.
		template <typename U>
		void set(const std::initializer_list<U>& lst);

		//! Set x and y with other vector \p pt.
		void set(const Vector& pt);

		//! Set both x and y to zero.
		void setZero();

		//! Normalizes this vector.
		void normalize();

		// MARK: Binary operations: new instance = this (+) v

		//! Computes this + (v, v).
		Vector add(T v) const;

		//! Computes this + (v.x, v.y).
		Vector add(const Vector& v) const;

		//! Computes this - (v, v).
		Vector sub(T v) const;

		//! Computes this - (v.x, v.y).
		Vector sub(const Vector& v) const;

		//! Computes this * (v, v).
		Vector mul(T v) const;

		//! Computes this * (v.x, v.y).
		Vector mul(const Vector& v) const;

		//! Computes this / (v, v).
		Vector div(T v) const;

		//! Computes this / (v.x, v.y).
		Vector div(const Vector& v) const;

		//! Computes dot product.
		T dot(const Vector& v) const;

		//! Comptues cross product.
		T cross(const Vector& v) const;

		// MARK: Binary operations: new instance = v (+) this

		//! Computes (v, v) - this.
		Vector rsub(T v) const;

		//! Computes (v.x, v.y) - this.
		Vector rsub(const Vector& v) const;

		//! Computes (v, v) / this.
		Vector rdiv(T v) const;

		//! Computes (v.x, v.y) / this.
		Vector rdiv(const Vector& v) const;

		//! Computes \p v cross this.
		T rcross(const Vector& v) const;

		// MARK: Augmented operations: this (+)= v

		//! Computes this += (v, v).
		void iadd(T v);

		//! Computes this += (v.x, v.y).
		void iadd(const Vector& v);

		//! Computes this -= (v, v).
		void isub(T v);

		//! Computes this -= (v.x, v.y).
		void isub(const Vector& v);

		//! Computes this *= (v, v).
		void imul(T v);

		//! Computes this *= (v.x, v.y).
		void imul(const Vector& v);

		//! Computes this /= (v, v).
		void idiv(T v);

		//! Computes this /= (v.x, v.y).
		void idiv(const Vector& v);

		// MARK: Basic getters

		//! Returns const reference to the \p i -th element of the vector.
		const T& at(size_t i) const;

		//! Returns reference to the \p i -th element of the vector.
		T& at(size_t i);

		//! Returns the sum of all the components (i.e. x + y).
		T sum() const;

		//! Returns the average of all the components.
		T avg() const;

		//! Returns the minimum value among x and y.
		T min() const;

		//! Returns the maximum value among x and y.
		T max() const;

		//! Returns the absolute minimum value among x and y.
		T absmin() const;

		//! Returns the absolute maximum value among x and y.
		T absmax() const;

		//! Returns the index of the dominant axis.
		size_t dominantAxis() const;

		//! Returns the index of the subminant axis.
		size_t subminantAxis() const;

		//! Returns normalized vector.
		Vector normalized() const;

		//! Returns the length of the vector.
		T length() const;

		//! Returns the squared length of the vector.
		T lengthSquared() const;

		//! Returns the distance to the other vector.
		T distanceTo(const Vector& other) const;

		//! Returns the squared distance to the other vector.
		T distanceSquaredTo(const Vector& other) const;

		//! Returns the reflection vector to the surface with given surface normal.
		Vector reflected(const Vector& normal) const;

		//! Returns the projected vector to the surface with given surface normal.
		Vector projected(const Vector& normal) const;

		//! Returns the tangential vector for this vector.
		Vector tangential() const;

		//! Returns a vector with different value type.
		template <typename U>
		Vector<U, 2> castTo() const;

		//! Returns true if \p other is the same as this vector.
		bool isEqual(const Vector& other) const;

		//! Returns true if \p other is similar to this vector.
		bool isSimilar(const Vector& other,
			T epsilon = std::numeric_limits<T>::epsilon()) const;

		// MARK: Operators

		//! Returns reference to the \p i -th element of the vector.
		T& operator[](size_t i);

		//! Returns const reference to the \p i -th element of the vector.
		const T& operator[](size_t i) const;

		//! Set x and y components with given initializer list.
		template <typename U>
		Vector& operator=(const std::initializer_list<U>& lst);

		//! Set x and y with other vector \p pt.
		Vector& operator=(const Vector& v);

		//! Computes this += (v, v)
		Vector& operator+=(T v);

		//! Computes this += (v.x, v.y)
		Vector& operator+=(const Vector& v);

		//! Computes this -= (v, v)
		Vector& operator-=(T v);

		//! Computes this -= (v.x, v.y)
		Vector& operator-=(const Vector& v);

		//! Computes this *= (v, v)
		Vector& operator*=(T v);

		//! Computes this *= (v.x, v.y)
		Vector& operator*=(const Vector& v);

		//! Computes this /= (v, v)
		Vector& operator/=(T v);

		//! Computes this /= (v.x, v.y)
		Vector& operator/=(const Vector& v);

		//! Returns true if \p other is the same as this vector.
		bool operator==(const Vector& v) const;

		//! Returns true if \p other is the not same as this vector.
		bool operator!=(const Vector& v) const;
	};

	//! Type alias for two dimensional vector.
	template <typename T>
	using Vector2 = Vector<T, 2>;

	using Vector2F = Vector2<float>;
	using Vector2D = Vector2<double>;

	//! Positive sign operator.
	template <typename T>
	Vector2<T> operator+(const Vector2<T>& a);

	//! Negative sign operator.
	template <typename T>
	Vector2<T> operator-(const Vector2<T>& a);

	//! Computes (a, a) + (b.x, b.y).
	template <typename T>
	Vector2<T> operator+(T a, const Vector2<T>& b);

	//! Computes (a.x, a.y) + (b.x, b.y).
	template <typename T>
	Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b);

	//! Computes (a.x, a.y) - (b, b).
	template <typename T>
	Vector2<T> operator-(const Vector2<T>& a, T b);

	//! Computes (a, a) - (b.x, b.y).
	template <typename T>
	Vector2<T> operator-(T a, const Vector2<T>& b);

	//! Computes (a.x, a.y) - (b.x, b.y).
	template <typename T>
	Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b);

	//! Computes (a.x, a.y) * (b, b).
	template <typename T>
	Vector2<T> operator*(const Vector2<T>& a, T b);

	//! Computes (a, a) * (b.x, b.y).
	template <typename T>
	Vector2<T> operator*(T a, const Vector2<T>& b);

	//! Computes (a.x, a.y) * (b.x, b.y).
	template <typename T>
	Vector2<T> operator*(const Vector2<T>& a, const Vector2<T>& b);

	//! Computes (a.x, a.y) / (b, b).
	template <typename T>
	Vector2<T> operator/(const Vector2<T>& a, T b);

	//! Computes (a, a) / (b.x, b.y).
	template <typename T>
	Vector2<T> operator/(T a, const Vector2<T>& b);

	//! Computes (a.x, a.y) / (b.x, b.y).
	template <typename T>
	Vector2<T> operator/(const Vector2<T>& a, const Vector2<T>& b);

	//! Returns element-wise min vector: (min(a.x, b.x), min(a.y, b.y)).
	template <typename T>
	Vector2<T> min(const Vector2<T>& a, const Vector2<T>& b);

	//! Returns element-wise max vector: (max(a.x, b.x), max(a.y, b.y)).
	template <typename T>
	Vector2<T> max(const Vector2<T>& a, const Vector2<T>& b);

	//! Returns element-wise clamped vector.
	template <typename T>
	Vector2<T> clamp(const Vector2<T>& v, const Vector2<T>& low,
		const Vector2<T>& high);

	//! Returns element-wise ceiled vector.
	template <typename T>
	Vector2<T> ceil(const Vector2<T>& a);

	//! Returns element-wise floored vector.
	template <typename T>
	Vector2<T> floor(const Vector2<T>& a);

	//! Float-type 2D vector.
	typedef Vector2<float> Vector2F;

	//! Double-type 2D vector.
	typedef Vector2<double> Vector2D;

	// MARK: Extensions

	//! Returns float-type zero vector.
	template <>
	constexpr Vector2F zero<Vector2F>() {
		return Vector2F(0.f, 0.f);
	}

	//! Returns double-type zero vector.
	template <>
	constexpr Vector2D zero<Vector2D>() {
		return Vector2D(0.0, 0.0);
	}

	//! Returns the type of the value itself.
	template <typename T>
	struct ScalarType<Vector2<T>> {
		typedef T value;
	};

	//! Computes monotonic Catmull-Rom interpolation.
	template <typename T>
	Vector2<T> monotonicCatmullRom(const Vector2<T>& v0, const Vector2<T>& v1,
		const Vector2<T>& v2, const Vector2<T>& v3, T f);

	//! ---------------------Definition--------------------------------

	// Constructors
	template <typename T>
	template <typename U>
	Vector<T, 2>::Vector(const std::initializer_list<U>& lst) { set(lst); }

	// Basic setters
	template <typename T>
	void Vector<T, 2>::set(T s) { x = s; y = s; }

	template <typename T>
	void Vector<T, 2>::set(T newX, T newY) { x = newX; y = newY; }

	template <typename T>
	template <typename U>
	void Vector<T, 2>::set(const std::initializer_list<U>& lst) 
	{
		assert(lst.size() >= 2);
		auto inputElem = lst.begin();
		x = static_cast<T>(*inputElem);
		y = static_cast<T>(*(++inputElem));
	}

	template <typename T>
	void Vector<T, 2>::set(const Vector& v) { x = v.x; y = v.y; }

	template <typename T>
	void Vector<T, 2>::setZero() { x = y = 0; }

	template <typename T>
	void Vector<T, 2>::normalize() { T l = length(); x /= l; y /= l; }

	// Binary operators: new instance = this (+) v
	template <typename T>
	Vector<T, 2> Vector<T, 2>::add(T v) const { return Vector(x + v, y + v); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::add(const Vector& v) const { return Vector(x + v.x, y + v.y); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::sub(T v) const { return Vector(x - v, y - v); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::sub(const Vector& v) const { return Vector(x - v.x, y - v.y); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::mul(T v) const { return Vector(x * v, y * v); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::mul(const Vector& v) const { return Vector(x * v.x, y * v.y); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::div(T v) const { return Vector(x / v, y / v); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::div(const Vector& v) const { return Vector(x / v.x, y / v.y); }

	template <typename T>
	T Vector<T, 2>::dot(const Vector& v) const { return x * v.x + y * v.y; }

	template <typename T>
	T Vector<T, 2>::cross(const Vector& v) const { return x * v.y - v.x * y; }

	// Binary operators: new instance = v (+) this
	template <typename T>
	Vector<T, 2> Vector<T, 2>::rsub(T v) const { return Vector(v - x, v - y); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::rsub(const Vector& v) const { return Vector(v.x - x, v.y - y); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::rdiv(T v) const { return Vector(v / x, v / y); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::rdiv(const Vector& v) const { return Vector(v.x / x, v.y / y); }

	template <typename T>
	T Vector<T, 2>::rcross(const Vector& v) const { return v.x * y - x * v.y; }

	// Augmented operators: this (+)= v
	template <typename T>
	void Vector<T, 2>::iadd(T v) { x += v; y += v; }

	template <typename T>
	void Vector<T, 2>::iadd(const Vector& v) { x += v.x; y += v.y; }

	template <typename T>
	void Vector<T, 2>::isub(T v) { x -= v; y -= v; }

	template <typename T>
	void Vector<T, 2>::isub(const Vector& v) { x -= v.x; y -= v.y; }

	template <typename T>
	void Vector<T, 2>::imul(T v) { x *= v; y *= v; }

	template <typename T>
	void Vector<T, 2>::imul(const Vector& v) { x *= v.x; y *= v.y; }

	template <typename T>
	void Vector<T, 2>::idiv(T v) { x /= v; y /= v; }

	template <typename T>
	void Vector<T, 2>::idiv(const Vector& v) { x /= v.x; y /= v.y; }

	// Basic getters
	template <typename T>
	const T& Vector<T, 2>::at(size_t i) const { assert(i < 2); return (&x)[i]; }

	template <typename T>
	T& Vector<T, 2>::at(size_t i) { assert(i < 2); return (&x)[i]; }

	template <typename T>
	T Vector<T, 2>::sum() const { return x + y; }

	template <typename T>
	T Vector<T, 2>::avg() const { return (x + y) / 2; }

	template <typename T>
	T Vector<T, 2>::min() const { return std::min(x, y); }

	template <typename T>
	T Vector<T, 2>::max() const { return std::max(x, y); }

	template <typename T>
	T Vector<T, 2>::absmin() const { return Engine::absmin(x, y); }

	template <typename T>
	T Vector<T, 2>::absmax() const { return Engine::absmax(x, y); }

	template <typename T>
	size_t Vector<T, 2>::dominantAxis() const { return (std::fabs(x) > std::fabs(y)) ? 0 : 1; }

	template <typename T>
	size_t Vector<T, 2>::subminantAxis() const { return (std::fabs(x) < std::fabs(y)) ? 0 : 1; }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::normalized() const { T l = length(); return Vector(x / l, y / l); }

	template <typename T>
	T Vector<T, 2>::length() const { return std::sqrt(x * x + y * y); }

	template <typename T>
	T Vector<T, 2>::lengthSquared() const { return x * x + y * y; }

	template <typename T>
	T Vector<T, 2>::distanceTo(const Vector<T, 2>& other) const { return sub(other).length(); }

	template <typename T>
	T Vector<T, 2>::distanceSquaredTo(const Vector<T, 2>& other) const { return sub(other).lengthSquared(); }

	template <typename T>
	Vector<T, 2> Vector<T, 2>::reflected(const Vector<T, 2>& normal) const 
	{
		// this - 2(this.n)n
		return sub(normal.mul(2 * dot(normal)));
	}

	template <typename T>
	Vector<T, 2> Vector<T, 2>::projected(const Vector<T, 2>& normal) const 
	{
		// this - this.n n
		return sub(normal.mul(dot(normal)));
	}

	template <typename T>
	Vector<T, 2> Vector<T, 2>::tangential() const 
	{
		// Rotate 90 degrees
		return Vector<T, 2>(-y, x);
	}

	template <typename T>
	template <typename U>
	Vector<U, 2> Vector<T, 2>::castTo() const 
	{
		return Vector<U, 2>(static_cast<U>(x), static_cast<U>(y));
	}

	template <typename T>
	bool Vector<T, 2>::isEqual(const Vector& other) const { return x == other.x && y == other.y; }

	template <typename T>
	bool Vector<T, 2>::isSimilar(const Vector& other, T epsilon) const 
	{
		return (std::fabs(x - other.x) < epsilon) && (std::fabs(y - other.y) < epsilon);
	}

	// Operators
	template <typename T>
	T& Vector<T, 2>::operator[](size_t i) { assert(i < 2); return (&x)[i]; }

	template <typename T>
	const T& Vector<T, 2>::operator[](size_t i) const { assert(i < 2); return (&x)[i]; }

	template <typename T>
	template <typename U>
	Vector<T, 2>& Vector<T, 2>::operator=(const std::initializer_list<U>& lst) { set(lst); return (*this); }

	template <typename T>
	Vector<T, 2>& Vector<T, 2>::operator=(const Vector& v) { set(v); return (*this); }

	template <typename T>
	Vector<T, 2>& Vector<T, 2>::operator+=(T v) { iadd(v); return (*this); }

	template <typename T>
	Vector<T, 2>& Vector<T, 2>::operator+=(const Vector& v) { iadd(v); return (*this); }

	template <typename T>
	Vector<T, 2>& Vector<T, 2>::operator-=(T v) { isub(v); return (*this); }

	template <typename T>
	Vector<T, 2>& Vector<T, 2>::operator-=(const Vector& v) { isub(v); return (*this); }

	template <typename T>
	Vector<T, 2>& Vector<T, 2>::operator*=(T v) { imul(v); return (*this); }

	template <typename T>
	Vector<T, 2>& Vector<T, 2>::operator*=(const Vector& v) { imul(v); return (*this); }

	template <typename T>
	Vector<T, 2>& Vector<T, 2>::operator/=(T v) { idiv(v); return (*this); }

	template <typename T>
	Vector<T, 2>& Vector<T, 2>::operator/=(const Vector& v) { idiv(v); return (*this); }

	template <typename T>
	bool Vector<T, 2>::operator==(const Vector& v) const { return isEqual(v); }

	template <typename T>
	bool Vector<T, 2>::operator!=(const Vector& v) const { return !isEqual(v); }

	// Math functions
	template <typename T>
	Vector<T, 2> operator+(const Vector<T, 2>& a) { return a; }

	template <typename T>
	Vector<T, 2> operator-(const Vector<T, 2>& a) { return Vector<T, 2>(-a.x, -a.y); }

	template <typename T>
	Vector<T, 2> operator+(const Vector<T, 2>& a, T b) { return a.add(b); }

	template <typename T>
	Vector<T, 2> operator+(T a, const Vector<T, 2>& b) { return b.add(a); }

	template <typename T>
	Vector<T, 2> operator+(const Vector<T, 2>& a, const Vector<T, 2>& b) { return a.add(b); }

	template <typename T>
	Vector<T, 2> operator-(const Vector<T, 2>& a, T b) { return a.sub(b); }

	template <typename T>
	Vector<T, 2> operator-(T a, const Vector<T, 2>& b) { return b.rsub(a); }

	template <typename T>
	Vector<T, 2> operator-(const Vector<T, 2>& a, const Vector<T, 2>& b) { return a.sub(b); }

	template <typename T>
	Vector<T, 2> operator*(const Vector<T, 2>& a, T b) { return a.mul(b); }

	template <typename T>
	Vector<T, 2> operator*(T a, const Vector<T, 2>& b) { return b.mul(a); }

	template <typename T>
	Vector<T, 2> operator*(const Vector<T, 2>& a, const Vector<T, 2>& b) { return a.mul(b); }

	template <typename T>
	Vector<T, 2> operator/(const Vector<T, 2>& a, T b) { return a.div(b); }

	template <typename T>
	Vector<T, 2> operator/(T a, const Vector<T, 2>& b) { return b.rdiv(a); }

	template <typename T>
	Vector<T, 2> operator/(const Vector<T, 2>& a, const Vector<T, 2>& b) { return a.div(b); }

	template <typename T>
	Vector<T, 2> min(const Vector<T, 2>& a, const Vector<T, 2>& b) 
	{
		return Vector<T, 2>(std::min(a.x, b.x), std::min(a.y, b.y));
	}

	template <typename T>
	Vector<T, 2> max(const Vector<T, 2>& a, const Vector<T, 2>& b) 
	{
		return Vector<T, 2>(std::max(a.x, b.x), std::max(a.y, b.y));
	}

	template <typename T>
	Vector<T, 2> clamp(const Vector<T, 2>& v, const Vector<T, 2>& low, const Vector<T, 2>& high) 
	{
		return Vector<T, 2>(clamp(v.x, low.x, high.x), clamp(v.y, low.y, high.y));
	}

	template <typename T>
	Vector<T, 2> ceil(const Vector<T, 2>& a) { return Vector<T, 2>(std::ceil(a.x), std::ceil(a.y)); }

	template <typename T>
	Vector<T, 2> floor(const Vector<T, 2>& a) { return Vector<T, 2>(std::floor(a.x), std::floor(a.y)); }

	// Extensions
	template <typename T>
	Vector<T, 2> monotonicCatmullRom(const Vector<T, 2>& v0, const Vector<T, 2>& v1,
		const Vector<T, 2>& v2, const Vector<T, 2>& v3, T f) 
	{
		static const T two = static_cast<T>(2);
		static const T three = static_cast<T>(3);
		Vector<T, 2> d1 = (v2 - v0) / two;
		Vector<T, 2> d2 = (v3 - v1) / two;
		Vector<T, 2> D1 = v2 - v1;

		if (std::fabs(D1.x) < std::numeric_limits<T>::epsilon() ||
			sign(D1.x) != sign(d1.x) || sign(D1.x) != sign(d2.x)) 
			d1.x = d2.x = 0;

		if (std::fabs(D1.y) < std::numeric_limits<T>::epsilon() ||
			sign(D1.y) != sign(d1.y) || sign(D1.y) != sign(d2.y)) 
			d1.y = d2.y = 0;

		Vector<T, 2> a3 = d1 + d2 - two * D1;
		Vector<T, 2> a2 = three * D1 - two * d1 - d2;
		Vector<T, 2> a1 = d1;
		Vector<T, 2> a0 = v1;
		return a3 * cubic(f) + a2 * square(f) + a1 * f + a0;
	}

}