#pragma once

#include <tuple>
#include <limits>
#include <algorithm>

#include "Vector2.h"

namespace Engine
{
	//!
	//! \brief 3-D vector class.
	//!
	//! This class defines simple 3-D vector data.
	//!
	//! \tparam T - Type of the element
	//!
	template <typename T>
	class Vector<T, 3> final
	{
	public:
		static_assert(std::is_floating_point<T>::value,
			"Vector only can be instantiated with floating point types");

		//! X (or the first) component of the vector.
		T x;
		//! Y (or the second) component of the vector.
		T y;
		//! Z (or the third) component of the vector.
		T z;

		// MARK: Constructors

		//! Constructs default vector (0, 0, 0).
		constexpr Vector() : x(0), y(0), z(0) {}

		//! Constructs vector with given parameters \p x_, \p y_, and \p z_.
		constexpr Vector(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

		//! Constructs vector with a 2-D vector and a scalar.
		constexpr Vector(const Vector2<T>& v, T z_) : x(v.x), y(v.y), z(z_) {}

		//! Constructs vector with initializer list.
		template <typename U>
		Vector(const std::initializer_list<U>& lst);

		//! Copy constructor.
		constexpr Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}

		// MARK: Basic setters

		//! Set all x, y, and z components to \p s.
		void set(T s);

		//! Set x, y, and z components with given parameters.
		void set(T x, T y, T z);

		//! Set x, y, and z components with given \p pt.x, \p pt.y, and \p z.
		void set(const Vector2<T>& pt, T z);

		//! Set x, y, and z components with given initializer list.
		template <typename U>
		void set(const std::initializer_list<U>& lst);

		//! Set x, y, and z with other vector \p v.
		void set(const Vector& v);

		//! Set all x, y, and z to zero.
		void setZero();

		//! Normalizes this vector.
		void normalize();

		// MARK: Binary operations: new instance = this (+) v

		//! Computes this + (v, v, v).
		Vector add(T v) const;

		//! Computes this + (v.x, v.y, v.z).
		Vector add(const Vector& v) const;

		//! Computes this - (v, v, v).
		Vector sub(T v) const;

		//! Computes this - (v.x, v.y, v.z).
		Vector sub(const Vector& v) const;

		//! Computes this * (v, v, v).
		Vector mul(T v) const;

		//! Computes this * (v.x, v.y, v.z).
		Vector mul(const Vector& v) const;

		//! Computes this / (v, v, v).
		Vector div(T v) const;

		//! Computes this / (v.x, v.y, v.z).
		Vector div(const Vector& v) const;

		//! Computes dot product.
		T dot(const Vector& v) const;

		//! Comptues cross product.
		Vector cross(const Vector& v) const;

		// MARK: Binary operations: new instance = v (+) this

		//! Computes (v, v, v) - this.
		Vector rsub(T v) const;

		//! Computes (v.x, v.y, v.z) - this.
		Vector rsub(const Vector& v) const;

		//! Computes (v, v, v) / this.
		Vector rdiv(T v) const;

		//! Computes (v.x, v.y, v.z) / this.
		Vector rdiv(const Vector& v) const;

		//! Computes \p v cross this.
		Vector rcross(const Vector& v) const;

		// MARK: Augmented operations: this (+)= v

		//! Computes this += (v, v, v).
		void iadd(T v);

		//! Computes this += (v.x, v.y, v.z).
		void iadd(const Vector& v);

		//! Computes this -= (v, v, v).
		void isub(T v);

		//! Computes this -= (v.x, v.y, v.z).
		void isub(const Vector& v);

		//! Computes this *= (v, v, v).
		void imul(T v);

		//! Computes this *= (v.x, v.y, v.z).
		void imul(const Vector& v);

		//! Computes this /= (v, v, v).
		void idiv(T v);

		//! Computes this /= (v.x, v.y, v.z).
		void idiv(const Vector& v);

		// MARK: Basic getters

		//! Returns const reference to the \p i -th element of the vector.
		const T& at(size_t i) const;

		//! Returns reference to the \p i -th element of the vector.
		T& at(size_t i);

		//! Returns the sum of all the components (i.e. x + y + z).
		T sum() const;

		//! Returns the average of all the components.
		T avg() const;

		//! Returns the minimum value among x, y, and z.
		T min() const;

		//! Returns the maximum value among x, y, and z.
		T max() const;

		//! Returns the absolute minimum value among x, y, and z.
		T absmin() const;

		//! Returns the absolute maximum value among x, y, and z.
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
		std::tuple<Vector, Vector> tangential() const;

		//! Returns a vector with different value type.
		template <typename U>
		Vector<U, 3> castTo() const;

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

		//! Computes this += (v, v, v)
		Vector& operator+=(T v);

		//! Computes this += (v.x, v.y, v.z)
		Vector& operator+=(const Vector& v);

		//! Computes this -= (v, v, v)
		Vector& operator-=(T v);

		//! Computes this -= (v.x, v.y, v.z)
		Vector& operator-=(const Vector& v);

		//! Computes this *= (v, v, v)
		Vector& operator*=(T v);

		//! Computes this *= (v.x, v.y, v.z)
		Vector& operator*=(const Vector& v);

		//! Computes this /= (v, v, v)
		Vector& operator/=(T v);

		//! Computes this /= (v.x, v.y, v.z)
		Vector& operator/=(const Vector& v);

		//! Returns true if \p other is the same as this vector.
		bool operator==(const Vector& v) const;

		//! Returns true if \p other is the not same as this vector.
		bool operator!=(const Vector& v) const;
	};

	//! Type alias for three dimensional vector.
	template <typename T>
	using Vector3 = Vector<T, 3>;

	using Vector3F = Vector3<float>;
	using Vector3D = Vector3<double>;

	//! Positive sign operator.
	template <typename T>
	Vector3<T> operator+(const Vector3<T>& a);

	//! Negative sign operator.
	template <typename T>
	Vector3<T> operator-(const Vector3<T>& a);

	//! Computes (a, a, a) + (b.x, b.y, b.z).
	template <typename T>
	Vector3<T> operator+(T a, const Vector3<T>& b);

	//! Computes (a.x, a.y, a.z) + (b.x, b.y, b.z).
	template <typename T>
	Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b);

	//! Computes (a.x, a.y, a.z) - (b, b, b).
	template <typename T>
	Vector3<T> operator-(const Vector3<T>& a, T b);

	//! Computes (a, a, a) - (b.x, b.y, b.z).
	template <typename T>
	Vector3<T> operator-(T a, const Vector3<T>& b);

	//! Computes (a.x, a.y, a.z) - (b.x, b.y, b.z).
	template <typename T>
	Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b);

	//! Computes (a.x, a.y, a.z) * (b, b, b).
	template <typename T>
	Vector3<T> operator*(const Vector3<T>& a, T b);

	//! Computes (a, a, a) * (b.x, b.y, b.z).
	template <typename T>
	Vector3<T> operator*(T a, const Vector3<T>& b);

	//! Computes (a.x, a.y, a.z) * (b.x, b.y, b.z).
	template <typename T>
	Vector3<T> operator*(const Vector3<T>& a, const Vector3<T>& b);

	//! Computes (a.x, a.y, a.z) / (b, b, b).
	template <typename T>
	Vector3<T> operator/(const Vector3<T>& a, T b);

	//! Computes (a, a, a) / (b.x, b.y, b.z).
	template <typename T>
	Vector3<T> operator/(T a, const Vector3<T>& b);

	//! Computes (a.x, a.y, a.z) / (b.x, b.y, b.z).
	template <typename T>
	Vector3<T> operator/(const Vector3<T>& a, const Vector3<T>& b);

	//! Returns element-wise min vector.
	template <typename T>
	Vector3<T> min(const Vector3<T>& a, const Vector3<T>& b);

	//! Returns element-wise max vector.
	template <typename T>
	Vector3<T> max(const Vector3<T>& a, const Vector3<T>& b);

	//! Returns element-wise clamped vector.
	template <typename T>
	Vector3<T> clamp(const Vector3<T>& v, const Vector3<T>& low,
		const Vector3<T>& high);

	//! Returns element-wise ceiled vector.
	template <typename T>
	Vector3<T> ceil(const Vector3<T>& a);

	//! Returns element-wise floored vector.
	template <typename T>
	Vector3<T> floor(const Vector3<T>& a);

	//! Float-type 3D vector.
	typedef Vector3<float> Vector3F;

	//! Double-type 3D vector.
	typedef Vector3<double> Vector3D;

	// MARK: Extensions

	//! Returns float-type zero vector.
	template <>
	constexpr Vector3F zero<Vector3F>() { return Vector3F(0.f, 0.f, 0.f); }

	//! Returns double-type zero vector.
	template <>
	constexpr Vector3D zero<Vector3D>() { return Vector3D(0.0, 0.0, 0.0); }

	//! Returns the type of the value itself.
	template <typename T>
	struct ScalarType<Vector3<T>> 
	{
		typedef T value;
	};

	//! Computes monotonic Catmull-Rom interpolation.
	template <typename T>
	Vector3<T> monotonicCatmullRom(const Vector3<T>& v0, const Vector3<T>& v1,
		const Vector3<T>& v2, const Vector3<T>& v3, T f);


	//! ---------------------------Definition-------------------------------------

	// Constructors
	template <typename T>
	template <typename U>
	Vector<T, 3>::Vector(const std::initializer_list<U>& lst) { set(lst); }

	// Basic setters
	template <typename T>
	void Vector<T, 3>::set(T s) { x = s; y = s; z = s; }

	template <typename T>
	void Vector<T, 3>::set(T newX, T newY, T newZ) { x = newX; y = newY; z = newZ; }

	template <typename T>
	void Vector<T, 3>::set(const Vector2<T>& pt, T newZ) { x = pt.x; y = pt.y; z = newZ; }

	template <typename T>
	template <typename U>
	void Vector<T, 3>::set(const std::initializer_list<U>& lst) 
	{
		assert(lst.size() >= 3);
		auto inputElem = lst.begin();
		x = static_cast<T>(*inputElem);
		y = static_cast<T>(*(++inputElem));
		z = static_cast<T>(*(++inputElem));
	}

	template <typename T>
	void Vector<T, 3>::set(const Vector& v) { x = v.x; y = v.y; z = v.z; }

	template <typename T>
	void Vector<T, 3>::setZero() { x = y = z = 0; }

	template <typename T>
	void Vector<T, 3>::normalize() { T l = length(); x /= l; y /= l; z /= l; }

	// Binary operators: new instance = this (+) v
	template <typename T>
	Vector<T, 3> Vector<T, 3>::add(T v) const { return Vector(x + v, y + v, z + v); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::add(const Vector& v) const { return Vector(x + v.x, y + v.y, z + v.z); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::sub(T v) const { return Vector(x - v, y - v, z - v); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::sub(const Vector& v) const { return Vector(x - v.x, y - v.y, z - v.z); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::mul(T v) const { return Vector(x * v, y * v, z * v); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::mul(const Vector& v) const { return Vector(x * v.x, y * v.y, z * v.z); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::div(T v) const { return Vector(x / v, y / v, z / v); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::div(const Vector& v) const { return Vector(x / v.x, y / v.y, z / v.z); }

	template <typename T>
	T Vector<T, 3>::dot(const Vector& v) const { return x * v.x + y * v.y + z * v.z; }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::cross(const Vector& v) const { return Vector(y * v.z - v.y * z, z * v.x - v.z * x, x * v.y - v.x * y); }

	// Binary operators: new instance = v (+) this
	template <typename T>
	Vector<T, 3> Vector<T, 3>::rsub(T v) const { return Vector(v - x, v - y, v - z); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::rsub(const Vector& v) const { return Vector(v.x - x, v.y - y, v.z - z); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::rdiv(T v) const { return Vector(v / x, v / y, v / z); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::rdiv(const Vector& v) const { return Vector(v.x / x, v.y / y, v.z / z); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::rcross(const Vector& v) const { return Vector(v.y * z - y * v.z, v.z * x - z * v.x, v.x * y - x * v.y); }

	// Augmented operators: this (+)= v
	template <typename T>
	void Vector<T, 3>::iadd(T v) { x += v; y += v; z += v; }

	template <typename T>
	void Vector<T, 3>::iadd(const Vector& v) { x += v.x; y += v.y; z += v.z; }

	template <typename T>
	void Vector<T, 3>::isub(T v) { x -= v; y -= v; z -= v; }

	template <typename T>
	void Vector<T, 3>::isub(const Vector& v) { x -= v.x; y -= v.y; z -= v.z; }

	template <typename T>
	void Vector<T, 3>::imul(T v) { x *= v; y *= v; z *= v; }

	template <typename T>
	void Vector<T, 3>::imul(const Vector& v) { x *= v.x; y *= v.y; z *= v.z; }

	template <typename T>
	void Vector<T, 3>::idiv(T v) { x /= v; y /= v; z /= v; }

	template <typename T>
	void Vector<T, 3>::idiv(const Vector& v) { x /= v.x; y /= v.y; z /= v.z; }

	// Basic getters
	template <typename T>
	const T& Vector<T, 3>::at(size_t i) const { assert(i < 3); return (&x)[i]; }

	template <typename T>
	T& Vector<T, 3>::at(size_t i) { assert(i < 3); return (&x)[i]; }

	template <typename T>
	T Vector<T, 3>::sum() const { return x + y + z; }

	template <typename T>
	T Vector<T, 3>::avg() const { return (x + y + z) / 3; }

	template <typename T>
	T Vector<T, 3>::min() const { return std::min(std::min(x, y), z); }

	template <typename T>
	T Vector<T, 3>::max() const { return std::max(std::max(x, y), z); }

	template <typename T>
	T Vector<T, 3>::absmin() const { return Engine::absmin(Engine::absmin(x, y), z); }

	template <typename T>
	T Vector<T, 3>::absmax() const { return Engine::absmax(Engine::absmax(x, y), z); }

	template <typename T>
	size_t Vector<T, 3>::dominantAxis() const 
	{
		return (std::fabs(x) > std::fabs(y))
			? ((std::fabs(x) > std::fabs(z)) ? 0 : 2)
			: ((std::fabs(y) > std::fabs(z)) ? 1 : 2);
	}

	template <typename T>
	size_t Vector<T, 3>::subminantAxis() const 
	{
		return (std::fabs(x) < std::fabs(y))
			? ((std::fabs(x) < std::fabs(z)) ? 0 : 2)
			: ((std::fabs(y) < std::fabs(z)) ? 1 : 2);
	}

	template <typename T>
	Vector<T, 3> Vector<T, 3>::normalized() const { T l = length(); return Vector(x / l, y / l, z / l); }

	template <typename T>
	T Vector<T, 3>::length() const { return std::sqrt(x * x + y * y + z * z); }

	template <typename T>
	T Vector<T, 3>::lengthSquared() const { return x * x + y * y + z * z; }

	template <typename T>
	T Vector<T, 3>::distanceTo(const Vector<T, 3>& other) const { return sub(other).length(); }

	template <typename T>
	T Vector<T, 3>::distanceSquaredTo(const Vector<T, 3>& other) const { return sub(other).lengthSquared(); }

	template <typename T>
	Vector<T, 3> Vector<T, 3>::reflected(const Vector<T, 3>& normal) const 
	{
		// this - 2(this.n)n
		return sub(normal.mul(2 * dot(normal)));
	}

	template <typename T>
	Vector<T, 3> Vector<T, 3>::projected(const Vector<T, 3>& normal) const 
	{
		// this - this.n n
		return sub(normal.mul(dot(normal)));
	}

	template <typename T>
	std::tuple<Vector<T, 3>, Vector<T, 3>> Vector<T, 3>::tangential() const 
	{
		Vector<T, 3> a =
			((std::fabs(y) > 0 || std::fabs(z) > 0) ? Vector<T, 3>(1, 0, 0)
				: Vector<T, 3>(0, 1, 0))
			.cross(*this)
			.normalized();
		Vector<T, 3> b = cross(a);
		return std::make_tuple(a, b);
	}

	template <typename T>
	template <typename U>
	Vector<U, 3> Vector<T, 3>::castTo() const 
	{
		return Vector<U, 3>(static_cast<U>(x), static_cast<U>(y), static_cast<U>(z));
	}

	template <typename T>
	bool Vector<T, 3>::isEqual(const Vector& other) const { return x == other.x && y == other.y && z == other.z; }

	template <typename T>
	bool Vector<T, 3>::isSimilar(const Vector& other, T epsilon) const 
	{
		return (std::fabs(x - other.x) < epsilon) && (std::fabs(y - other.y) < epsilon) &&
			(std::fabs(z - other.z) < epsilon);
	}

	// Operators
	template <typename T>
	T& Vector<T, 3>::operator[](size_t i) { assert(i < 3); return (&x)[i]; }

	template <typename T>
	const T& Vector<T, 3>::operator[](size_t i) const { assert(i < 3); return (&x)[i]; }

	template <typename T>
	template <typename U>
	Vector<T, 3>& Vector<T, 3>::operator=(const std::initializer_list<U>& lst) { set(lst); return (*this); }

	template <typename T>
	Vector<T, 3>& Vector<T, 3>::operator=(const Vector& v) { set(v); return (*this); }

	template <typename T>
	Vector<T, 3>& Vector<T, 3>::operator+=(T v) { iadd(v); return (*this); }

	template <typename T>
	Vector<T, 3>& Vector<T, 3>::operator+=(const Vector& v) { iadd(v); return (*this); }

	template <typename T>
	Vector<T, 3>& Vector<T, 3>::operator-=(T v) { isub(v); return (*this); }

	template <typename T>
	Vector<T, 3>& Vector<T, 3>::operator-=(const Vector& v) { isub(v);  return (*this); }

	template <typename T>
	Vector<T, 3>& Vector<T, 3>::operator*=(T v) { imul(v); return (*this); }

	template <typename T>
	Vector<T, 3>& Vector<T, 3>::operator*=(const Vector& v) { imul(v); return (*this); }

	template <typename T>
	Vector<T, 3>& Vector<T, 3>::operator/=(T v) { idiv(v); return (*this); }

	template <typename T>
	Vector<T, 3>& Vector<T, 3>::operator/=(const Vector& v) { idiv(v); return (*this); }

	template <typename T>
	bool Vector<T, 3>::operator==(const Vector& v) const { return isEqual(v); }

	template <typename T>
	bool Vector<T, 3>::operator!=(const Vector& v) const { return !isEqual(v); }

	template <typename T>
	Vector<T, 3> operator+(const Vector<T, 3>& a) { return a; }

	template <typename T>
	Vector<T, 3> operator-(const Vector<T, 3>& a) { return Vector<T, 3>(-a.x, -a.y, -a.z); }

	template <typename T>
	Vector<T, 3> operator+(const Vector<T, 3>& a, T b) { return a.add(b); }

	template <typename T>
	Vector<T, 3> operator+(T a, const Vector<T, 3>& b) { return b.add(a); }

	template <typename T>
	Vector<T, 3> operator+(const Vector<T, 3>& a, const Vector<T, 3>& b) { return a.add(b); }

	template <typename T>
	Vector<T, 3> operator-(const Vector<T, 3>& a, T b) { return a.sub(b); }

	template <typename T>
	Vector<T, 3> operator-(T a, const Vector<T, 3>& b) { return b.rsub(a); }

	template <typename T>
	Vector<T, 3> operator-(const Vector<T, 3>& a, const Vector<T, 3>& b) { return a.sub(b); }

	template <typename T>
	Vector<T, 3> operator*(const Vector<T, 3>& a, T b) { return a.mul(b); }

	template <typename T>
	Vector<T, 3> operator*(T a, const Vector<T, 3>& b) { return b.mul(a); }

	template <typename T>
	Vector<T, 3> operator*(const Vector<T, 3>& a, const Vector<T, 3>& b) { return a.mul(b); }

	template <typename T>
	Vector<T, 3> operator/(const Vector<T, 3>& a, T b) { return a.div(b); }

	template <typename T>
	Vector<T, 3> operator/(T a, const Vector<T, 3>& b) { return b.rdiv(a); }

	template <typename T>
	Vector<T, 3> operator/(const Vector<T, 3>& a, const Vector<T, 3>& b) { return a.div(b); }

	template <typename T>
	Vector<T, 3> min(const Vector<T, 3>& a, const Vector<T, 3>& b) 
	{
		return Vector<T, 3>(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
	}

	template <typename T>
	Vector<T, 3> max(const Vector<T, 3>& a, const Vector<T, 3>& b) 
	{
		return Vector<T, 3>(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
	}

	template <typename T>
	Vector<T, 3> clamp(const Vector<T, 3>& v, const Vector<T, 3>& low,
		const Vector<T, 3>& high) 
	{
		return Vector<T, 3>(clamp(v.x, low.x, high.x), clamp(v.y, low.y, high.y),
			clamp(v.z, low.z, high.z));
	}

	template <typename T>
	Vector<T, 3> ceil(const Vector<T, 3>& a) 
	{
		return Vector<T, 3>(std::ceil(a.x), std::ceil(a.y), std::ceil(a.z));
	}

	template <typename T>
	Vector<T, 3> floor(const Vector<T, 3>& a) 
	{
		return Vector<T, 3>(std::floor(a.x), std::floor(a.y), std::floor(a.z));
	}

	// Extensions
	template <typename T>
	Vector<T, 3> monotonicCatmullRom(const Vector<T, 3>& v0, const Vector<T, 3>& v1,
		const Vector<T, 3>& v2, const Vector<T, 3>& v3, T f) 
	{
		static const T two = static_cast<T>(2);
		static const T three = static_cast<T>(3);
		Vector<T, 3> d1 = (v2 - v0) / two;
		Vector<T, 3> d2 = (v3 - v1) / two;
		Vector<T, 3> D1 = v2 - v1;

		if (std::fabs(D1.x) < std::numeric_limits<float>::epsilon() ||
			sign(D1.x) != sign(d1.x) || sign(D1.x) != sign(d2.x)) 
			d1.x = d2.x = 0;

		if (std::fabs(D1.y) < std::numeric_limits<float>::epsilon() ||
			sign(D1.y) != sign(d1.y) || sign(D1.y) != sign(d2.y)) 
			d1.y = d2.y = 0;

		if (std::fabs(D1.z) < std::numeric_limits<float>::epsilon() ||
			sign(D1.z) != sign(d1.z) || sign(D1.z) != sign(d2.z)) 
			d1.z = d2.z = 0;

		Vector<T, 3> a3 = d1 + d2 - two * D1;
		Vector<T, 3> a2 = three * D1 - two * d1 - d2;
		Vector<T, 3> a1 = d1;
		Vector<T, 3> a0 = v1;
		return a3 * cubic(f) + a2 * square(f) + a1 * f + a0;
	}

}