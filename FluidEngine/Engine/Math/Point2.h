#pragma once

#include <algorithm>

#include "Point.h"
#include "../Utils/Macros.h"
#include "../Utils/MathUtils.h"

namespace Engine
{
	//!
	//! \brief 2-D point class.
	//!
	//! This class defines simple 2-D point data.
	//!
	//! \tparam T - Type of the element
	//!
	template <typename T>
	class Point<T, 2>
	{
	public:
		static_assert(std::is_arithmetic<T>::value,
			"Point only can be instantiated with arithmetic types");

		//! X (or the first) component of the point.
		T x;
		//! Y (or the second) component of the point.
		T y;

		// MARK: Constructors

		//! Constructs default point (0, 0).
		constexpr Point() : x(0), y(0) {}

		//! Constructs point with given parameters \p x_ and \p y_.
		constexpr Point(T x_, T y_) : x(x_), y(y_) {}

		//! Constructs point with initializer list.
		template <typename U>
		Point(const std::initializer_list<U>& lst);

		//! Copy constructor.
		constexpr Point(const Point& v) : x(v.x), y(v.y) {}

		// MARK: Basic setters
		
		//! Set both x and y components to \p s.
		void set(T s);

		//! Set x and y components with given parameters.
		void set(T x, T y);

		//! Set x and y components with given initializer list.
		template <typename U>
		void set(const std::initializer_list<U>& lst);

		//! Set x and y with other point \p pt.
		void set(const Point& pt);

		//! Set both x and y to zero.
		void setZero();

		// MARK: Binary operations: new instance = this (+) v
		
		//! Computes this + (v, v).
		Point add(T v) const;

		//! Computes this + (v.x, v.y).
		Point add(const Point& v) const;

		//! Computes this - (v, v).
		Point sub(T v) const;

		//! Computes this - (v.x, v.y).
		Point sub(const Point& v) const;

		//! Computes this * (v, v).
		Point mul(T v) const;

		//! Computes this * (v.x, v.y).
		Point mul(const Point& v) const;

		//! Computes this / (v, v).
		Point div(T v) const;

		//! Computes this / (v.x, v.y).
		Point div(const Point& v) const;

		// MARK: Binary operations: new instance = v (+) this
		
		//! Computes (v, v) - this.
		Point rsub(T v) const;

		//! Computes (v.x, v.y) - this.
		Point rsub(const Point& v) const;

		//! Computes (v, v) / this.
		Point rdiv(T v) const;

		//! Computes (v.x, v.y) / this.
		Point rdiv(const Point& v) const;

		// MARK: Augmented operations: this (+)= v
		
		//! Computes this += (v, v).
		void iadd(T v);

		//! Computes this += (v.x, v.y).
		void iadd(const Point& v);

		//! Computes this -= (v, v).
		void isub(T v);

		//! Computes this -= (v.x, v.y).
		void isub(const Point& v);

		//! Computes this *= (v, v).
		void imul(T v);

		//! Computes this *= (v.x, v.y).
		void imul(const Point& v);

		//! Computes this /= (v, v).
		void idiv(T v);

		//! Computes this /= (v.x, v.y).
		void idiv(const Point& v);

		// MARK: Basic getters
		
		//! Returns const reference to the \p i -th element of the point.
		const T& at(size_t i) const;

		//! Returns reference to the \p i -th element of the point.
		T& at(size_t i);

		//! Returns the sum of all the components (i.e. x + y).
		T sum() const;

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

		//! Returns a point with different value type.
		template <typename U>
		Point<U, 2> castTo() const;

		//! Returns true if \p other is the same as this point.
		bool isEqual(const Point& other) const;

		// MARK: Operators
		//! Returns reference to the \p i -th element of the point.
		T& operator[](size_t i);

		//! Returns const reference to the \p i -th element of the point.
		const T& operator[](size_t i) const;

		//! Set x and y components with given initializer list.
		Point& operator=(const std::initializer_list<T>& lst);

		//! Set x and y with other point \p pt.
		Point& operator=(const Point& v);

		//! Computes this += (v, v)
		Point& operator+=(T v);

		//! Computes this += (v.x, v.y)
		Point& operator+=(const Point& v);

		//! Computes this -= (v, v)
		Point& operator-=(T v);

		//! Computes this -= (v.x, v.y)
		Point& operator-=(const Point& v);

		//! Computes this *= (v, v)
		Point& operator*=(T v);

		//! Computes this *= (v.x, v.y)
		Point& operator*=(const Point& v);

		//! Computes this /= (v, v)
		Point& operator/=(T v);

		//! Computes this /= (v.x, v.y)
		Point& operator/=(const Point& v);

		//! Returns true if \p other is the same as this point.
		bool operator==(const Point& v) const;

		//! Returns true if \p other is the not same as this point.
		bool operator!=(const Point& v) const;
	};

	//! Type alias for two dimensional point.
	template <typename T>
	using Point2 = Point<T, 2>;

	//! Positive sign operator.
	template <typename T>
	Point<T, 2> operator+(const Point<T, 2>& a);

	//! Negative sign operator.
	template <typename T>
	Point2<T> operator-(const Point2<T>& a);

	//! Computes (a, a) + (b.x, b.y).
	template <typename T>
	Point2<T> operator+(T a, const Point2<T>& b);

	//! Computes (a.x, a.y) + (b.x, b.y).
	template <typename T>
	Point2<T> operator+(const Point2<T>& a, const Point2<T>& b);

	//! Computes (a.x, a.y) - (b, b).
	template <typename T>
	Point2<T> operator-(const Point2<T>& a, T b);

	//! Computes (a, a) - (b.x, b.y).
	template <typename T>
	Point2<T> operator-(T a, const Point2<T>& b);

	//! Computes (a.x, a.y) - (b.x, b.y).
	template <typename T>
	Point2<T> operator-(const Point2<T>& a, const Point2<T>& b);

	//! Computes (a.x, a.y) * (b, b).
	template <typename T>
	Point2<T> operator*(const Point2<T>& a, T b);

	//! Computes (a, a) * (b.x, b.y).
	template <typename T>
	Point2<T> operator*(T a, const Point2<T>& b);

	//! Computes (a.x, a.y) * (b.x, b.y).
	template <typename T>
	Point2<T> operator*(const Point2<T>& a, const Point2<T>& b);

	//! Computes (a.x, a.y) / (b, b).
	template <typename T>
	Point2<T> operator/(const Point2<T>& a, T b);

	//! Computes (a, a) / (b.x, b.y).
	template <typename T>
	Point2<T> operator/(T a, const Point2<T>& b);

	//! Computes (a.x, a.y) / (b.x, b.y).
	template <typename T>
	Point2<T> operator/(const Point2<T>& a, const Point2<T>& b);

	//! Returns element-wise min point: (min(a.x, b.x), min(a.y, b.y)).
	template <typename T>
	Point2<T> min(const Point2<T>& a, const Point2<T>& b);

	//! Returns element-wise max point: (max(a.x, b.x), max(a.y, b.y)).
	template <typename T>
	Point2<T> max(const Point2<T>& a, const Point2<T>& b);

	//! Returns element-wise clamped point.
	template <typename T>
	Point2<T> clamp(const Point2<T>& v, const Point2<T>& low,
		const Point2<T>& high);

	//! Returns element-wise ceiled point.
	template <typename T>
	Point2<T> ceil(const Point2<T>& a);

	//! Returns element-wise floored point.
	template <typename T>
	Point2<T> floor(const Point2<T>& a);

	//! Float-type 2D point.
	typedef Point2<float> Point2F;

	//! Double-type 2D point.
	typedef Point2<double> Point2D;

	//! Integer-type 2D point.
	typedef Point2<ssize_t> Point2I;

	//! Unsigned integer-type 2D point.
	typedef Point2<size_t> Point2UI;

	// Constructors
	template <typename T>
	template <typename U>
	Point<T, 2>::Point(const std::initializer_list<U>& lst) { set(lst); }

	// Basic setters
	template <typename T>
	void Point<T, 2>::set(T s) { x = s; y = s; }

	template <typename T>
	void Point<T, 2>::set(T newX, T newY) { x = newX; y = newY; }

	template <typename T>
	template <typename U>
	void Point<T, 2>::set(const std::initializer_list<U>& lst) 
	{
		assert(lst.size() >= 2);
		auto inputElem = lst.begin();
		x = static_cast<T>(*inputElem);
		y = static_cast<T>(*(++inputElem));
	}

	template <typename T>
	void Point<T, 2>::set(const Point& v) { x = v.x; y = v.y; }

	template <typename T>
	void Point<T, 2>::setZero() { x = y = 0; }

	// Binary operators: new instance = this (+) v
	template <typename T>
	Point<T, 2> Point<T, 2>::add(T v) const { return Point(x + v, y + v); }

	template <typename T>
	Point<T, 2> Point<T, 2>::add(const Point& v) const { return Point(x + v.x, y + v.y); }

	template <typename T>
	Point<T, 2> Point<T, 2>::sub(T v) const { return Point(x - v, y - v); }

	template <typename T>
	Point<T, 2> Point<T, 2>::sub(const Point& v) const { return Point(x - v.x, y - v.y); }

	template <typename T>
	Point<T, 2> Point<T, 2>::mul(T v) const { return Point(x * v, y * v); }

	template <typename T>
	Point<T, 2> Point<T, 2>::mul(const Point& v) const { return Point(x * v.x, y * v.y); }

	template <typename T>
	Point<T, 2> Point<T, 2>::div(T v) const { return Point(x / v, y / v); }

	template <typename T>
	Point<T, 2> Point<T, 2>::div(const Point& v) const { return Point(x / v.x, y / v.y); }

	// Binary operators: new instance = v (+) this
	template <typename T>
	Point<T, 2> Point<T, 2>::rsub(T v) const { return Point(v - x, v - y); }

	template <typename T>
	Point<T, 2> Point<T, 2>::rsub(const Point& v) const { return Point(v.x - x, v.y - y); }

	template <typename T>
	Point<T, 2> Point<T, 2>::rdiv(T v) const { return Point(v / x, v / y); }

	template <typename T>
	Point<T, 2> Point<T, 2>::rdiv(const Point& v) const { return Point(v.x / x, v.y / y); }

	// Augmented operators: this (+)= v
	template <typename T>
	void Point<T, 2>::iadd(T v) { x += v; y += v; }

	template <typename T>
	void Point<T, 2>::iadd(const Point& v) { x += v.x; y += v.y; }

	template <typename T>
	void Point<T, 2>::isub(T v) { x -= v; y -= v; }

	template <typename T>
	void Point<T, 2>::isub(const Point& v) { x -= v.x; y -= v.y; }

	template <typename T>
	void Point<T, 2>::imul(T v) { x *= v; y *= v; }

	template <typename T>
	void Point<T, 2>::imul(const Point& v) { x *= v.x; y *= v.y; }

	template <typename T>
	void Point<T, 2>::idiv(T v) { x /= v; y /= v; }

	template <typename T>
	void Point<T, 2>::idiv(const Point& v) { x /= v.x; y /= v.y; }

	// Basic getters
	template <typename T>
	const T& Point<T, 2>::at(size_t i) const { assert(i < 2); return (&x)[i]; }

	template <typename T>
	T& Point<T, 2>::at(size_t i) { assert(i < 2); return (&x)[i]; }

	template <typename T>
	T Point<T, 2>::sum() const { return x + y; }

	template <typename T>
	T Point<T, 2>::min() const { return std::min(x, y); }

	template <typename T>
	T Point<T, 2>::max() const { return std::max(x, y); }

	template <typename T>
	T Point<T, 2>::absmin() const { return Engine::absmin(x, y); }

	template <typename T>
	T Point<T, 2>::absmax() const { return Engine::absmax(x, y); }

	template <typename T>
	size_t Point<T, 2>::dominantAxis() const { return (std::fabs(x) > std::fabs(y)) ? 0 : 1; }

	template <typename T>
	size_t Point<T, 2>::subminantAxis() const { return (std::fabs(x) < std::fabs(y)) ? 0 : 1; }

	template <typename T>
	template <typename U>
	Point2<U> Point<T, 2>::castTo() const { return Point2<U>(static_cast<U>(x), static_cast<U>(y)); }

	template <typename T>
	bool Point<T, 2>::isEqual(const Point& other) const { return (x == other.x && y == other.y); }

	// Operators
	template <typename T>
	T& Point<T, 2>::operator[](size_t i) { assert(i < 2); return (&x)[i]; }

	template <typename T>
	const T& Point<T, 2>::operator[](size_t i) const { assert(i < 2); return (&x)[i]; }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator=(const std::initializer_list<T>& lst) { set(lst); return (*this); }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator=(const Point& v) { set(v); return (*this); }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator+=(T v) { iadd(v); return (*this); }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator+=(const Point& v) { iadd(v); return (*this); }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator-=(T v) { isub(v); return (*this); }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator-=(const Point& v) { isub(v); return (*this); }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator*=(T v) { imul(v); return (*this); }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator*=(const Point& v) { imul(v); return (*this); }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator/=(T v) { idiv(v); return (*this); }

	template <typename T>
	Point<T, 2>& Point<T, 2>::operator/=(const Point& v) { idiv(v); return (*this); }

	template <typename T>
	bool Point<T, 2>::operator==(const Point& v) const { return isEqual(v); }

	template <typename T>
	bool Point<T, 2>::operator!=(const Point& v) const { return !isEqual(v); }

	// Math functions
	template <typename T>
	Point<T, 2> operator+(const Point<T, 2>& a) { return a; }

	template <typename T>
	Point<T, 2> operator-(const Point<T, 2>& a) { return Point<T, 2>(-a.x, -a.y); }

	template <typename T>
	Point<T, 2> operator+(const Point<T, 2>& a, T b) { return a.add(b); }

	template <typename T>
	Point<T, 2> operator+(T a, const Point<T, 2>& b) { return b.radd(a); }

	template <typename T>
	Point<T, 2> operator+(const Point<T, 2>& a, const Point<T, 2>& b) { return a.add(b); }

	template <typename T>
	Point<T, 2> operator-(const Point<T, 2>& a, T b) { return a.sub(b); }

	template <typename T>
	Point<T, 2> operator-(T a, const Point<T, 2>& b) { return b.rsub(a); }

	template <typename T>
	Point<T, 2> operator-(const Point<T, 2>& a, const Point<T, 2>& b) { return a.sub(b); }

	template <typename T>
	Point<T, 2> operator*(const Point<T, 2>& a, T b) { return a.mul(b); }

	template <typename T>
	Point<T, 2> operator*(T a, const Point<T, 2>& b) { return b.rmul(a); }

	template <typename T>
	Point<T, 2> operator*(const Point<T, 2>& a, const Point<T, 2>& b) { return a.mul(b); }

	template <typename T>
	Point<T, 2> operator/(const Point<T, 2>& a, T b) { return a.div(b); }

	template <typename T>
	Point<T, 2> operator/(T a, const Point<T, 2>& b) { return b.rdiv(a); }

	template <typename T>
	Point<T, 2> operator/(const Point<T, 2>& a, const Point<T, 2>& b) { return a.div(b); }

	template <typename T>
	Point<T, 2> min(const Point<T, 2>& a, const Point<T, 2>& b) { return Point<T, 2>(std::min(a.x, b.x), std::min(a.y, b.y)); }

	template <typename T>
	Point<T, 2> max(const Point<T, 2>& a, const Point<T, 2>& b) { return Point<T, 2>(std::max(a.x, b.x), std::max(a.y, b.y)); }

	template <typename T>
	Point<T, 2> clamp(const Point<T, 2>& v, const Point<T, 2>& low, const Point<T, 2>& high) 
	{
		return Point<T, 2>(Engine::clamp(v.x, low.x, high.x), Engine::clamp(v.y, low.y, high.y));
	}

	template <typename T>
	Point<T, 2> ceil(const Point<T, 2>& a) { return Point<T, 2>(std::ceil(a.x), std::ceil(a.y)); }

	template <typename T>
	Point<T, 2> floor(const Point<T, 2>& a) { return Point<T, 2>(std::floor(a.x), std::floor(a.y)); }

}