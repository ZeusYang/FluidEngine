#pragma once

#include <algorithm>

#include "Size.h"
#include "../Utils/MathUtils.h"

namespace Engine
{
	//!
	//! \brief 2-D size class.
	//!
	//! This class defines simple 2-D size data.
	//!
	class Size2
	{
	public:
		//! X (or the first) component of the size.
		size_t x;
		//! Y (or the second) component of the size.
		size_t y;

		// MARK: Constructors

		//! Constructs default size (0, 0).
		constexpr Size2() : x(0), y(0) {}

		//! Constructs size with given parameters \p x_ and \p y_.
		constexpr Size2(size_t x_, size_t y_) : x(x_), y(y_) {}

		//! Constructs size with initializer list.
		template <typename U>
		Size2(const std::initializer_list<U>& lst);

		//! Copy constructor.
		constexpr Size2(const Size2& v) : x(v.x), y(v.y) {}

		// MARK: Basic setters
		
		//! Set both x and y components to \p s.
		void set(size_t s);

		//! Set x and y components with given parameters.
		void set(size_t x, size_t y);

		//! Set x and y components with given initializer list.
		template <typename U>
		void set(const std::initializer_list<U>& lst);

		//! Set x and y with other size \p pt.
		void set(const Size2& pt);

		//! Set both x and y to zero.
		void setZero();

		// MARK: Binary operations: new instance = this (+) v
		
		//! Computes this + (v, v).
		Size2 add(size_t v) const;

		//! Computes this + (v.x, v.y).
		Size2 add(const Size2& v) const;

		//! Computes this - (v, v).
		Size2 sub(size_t v) const;

		//! Computes this - (v.x, v.y).
		Size2 sub(const Size2& v) const;

		//! Computes this * (v, v).
		Size2 mul(size_t v) const;

		//! Computes this * (v.x, v.y).
		Size2 mul(const Size2& v) const;

		//! Computes this / (v, v).
		Size2 div(size_t v) const;

		//! Computes this / (v.x, v.y).
		Size2 div(const Size2& v) const;

		// MARK: Binary operations: new instance = v (+) this
		
		//! Computes (v, v) - this.
		Size2 rsub(size_t v) const;

		//! Computes (v.x, v.y) - this.
		Size2 rsub(const Size2& v) const;

		//! Computes (v, v) / this.
		Size2 rdiv(size_t v) const;

		//! Computes (v.x, v.y) / this.
		Size2 rdiv(const Size2& v) const;

		// MARK: Augmented operations: this (+)= v
		
		//! Computes this += (v, v).
		void iadd(size_t v);

		//! Computes this += (v.x, v.y).
		void iadd(const Size2& v);

		//! Computes this -= (v, v).
		void isub(size_t v);

		//! Computes this -= (v.x, v.y).
		void isub(const Size2& v);

		//! Computes this *= (v, v).
		void imul(size_t v);

		//! Computes this *= (v.x, v.y).
		void imul(const Size2& v);

		//! Computes this /= (v, v).
		void idiv(size_t v);

		//! Computes this /= (v.x, v.y).
		void idiv(const Size2& v);

		// MARK: Basic getters
		
		//! Returns const reference to the \p i -th element of the size.
		const size_t& at(size_t i) const;

		//! Returns reference to the \p i -th element of the size.
		size_t& at(size_t i);

		//! Returns the sum of all the components (i.e. x + y).
		size_t sum() const;

		//! Returns the minimum value among x and y.
		size_t min() const;

		//! Returns the maximum value among x and y.
		size_t max() const;

		//! Returns the absolute minimum value among x and y.
		size_t absmin() const;

		//! Returns the absolute maximum value among x and y.
		size_t absmax() const;

		//! Returns the index of the dominant axis.
		size_t dominantAxis() const;

		//! Returns the index of the subminant axis.
		size_t subminantAxis() const;

		//! Returns true if \p other is the same as this size.
		bool isEqual(const Size2& other) const;

		// MARK: Operators
		
		//! Returns reference to the \p i -th element of the size.
		size_t& operator[](size_t i);

		//! Returns const reference to the \p i -th element of the size.
		const size_t& operator[](size_t i) const;

		//! Set x and y components with given initializer list.
		template <typename U>
		Size2& operator=(const std::initializer_list<U>& lst);

		//! Set x and y with other size \p pt.
		Size2& operator=(const Size2& v);

		//! Computes this += (v, v)
		Size2& operator+=(size_t v);

		//! Computes this += (v.x, v.y)
		Size2& operator+=(const Size2& v);

		//! Computes this -= (v, v)
		Size2& operator-=(size_t v);

		//! Computes this -= (v.x, v.y)
		Size2& operator-=(const Size2& v);

		//! Computes this *= (v, v)
		Size2& operator*=(size_t v);

		//! Computes this *= (v.x, v.y)
		Size2& operator*=(const Size2& v);

		//! Computes this /= (v, v)
		Size2& operator/=(size_t v);

		//! Computes this /= (v.x, v.y)
		Size2& operator/=(const Size2& v);

		//! Returns true if \p other is the same as this size.
		bool operator==(const Size2& v) const;

		//! Returns true if \p other is the not same as this size.
		bool operator!=(const Size2& v) const;

	};

	//! Positive sign operator.
	Size2 operator+(const Size2& a);

	//! Negative sign operator.
	Size2 operator-(const Size2& a);

	//! Computes (a, a) + (b.x, b.y).
	Size2 operator+(size_t a, const Size2& b);

	//! Computes (a.x, a.y) + (b.x, b.y).
	Size2 operator+(const Size2& a, const Size2& b);

	//! Computes (a.x, a.y) - (b, b).
	Size2 operator-(const Size2& a, size_t b);

	//! Computes (a, a) - (b.x, b.y).
	Size2 operator-(size_t a, const Size2& b);

	//! Computes (a.x, a.y) - (b.x, b.y).
	Size2 operator-(const Size2& a, const Size2& b);

	//! Computes (a.x, a.y) * (b, b).
	Size2 operator*(const Size2& a, size_t b);

	//! Computes (a, a) * (b.x, b.y).
	Size2 operator*(size_t a, const Size2& b);

	//! Computes (a.x, a.y) * (b.x, b.y).
	Size2 operator*(const Size2& a, const Size2& b);

	//! Computes (a.x, a.y) / (b, b).
	Size2 operator/(const Size2& a, size_t b);

	//! Computes (a, a) / (b.x, b.y).
	Size2 operator/(size_t a, const Size2& b);

	//! Computes (a.x, a.y) / (b.x, b.y).
	Size2 operator/(const Size2& a, const Size2& b);

	//! Returns element-wise min size: (min(a.x, b.x), min(a.y, b.y)).
	Size2 min(const Size2& a, const Size2& b);

	//! Returns element-wise max size: (max(a.x, b.x), max(a.y, b.y)).
	Size2 max(const Size2& a, const Size2& b);

	//! Returns element-wise clamped size.
	Size2 clamp(const Size2& v, const Size2& low, const Size2& high);

	//! Returns element-wise ceiled size.
	Size2 ceil(const Size2& a);

	//! Returns element-wise floored size.
	Size2 floor(const Size2& a);

	// Constructors
	template <typename U>
	inline Size2::Size2(const std::initializer_list<U>& lst) { set(lst); }

	// Basic setters
	inline void Size2::set(size_t newX, size_t newY) { x = newX; y = newY; }

	template <typename U>
	inline void Size2::set(const std::initializer_list<U>& lst) 
	{
		assert(lst.size() >= 2);
		auto inputElem = lst.begin();
		x = static_cast<size_t>(*inputElem);
		y = static_cast<size_t>(*(++inputElem));
	}

	inline void Size2::set(const Size2& v) { x = v.x; y = v.y; }

	inline void Size2::setZero() { x = y = 0; }
	
	// Binary operators: new instance = this (+) v
	inline Size2 Size2::add(size_t v) const { return Size2(x + v, y + v); }

	inline Size2 Size2::add(const Size2& v) const { return Size2(x + v.x, y + v.y); }

	inline Size2 Size2::sub(size_t v) const { return Size2(x - v, y - v); }

	inline Size2 Size2::sub(const Size2& v) const { return Size2(x - v.x, y - v.y); }

	inline Size2 Size2::mul(size_t v) const { return Size2(x * v, y * v); }

	inline Size2 Size2::mul(const Size2& v) const { return Size2(x * v.x, y * v.y); }

	inline Size2 Size2::div(size_t v) const { return Size2(x / v, y / v); }

	inline Size2 Size2::div(const Size2& v) const { return Size2(x / v.x, y / v.y); }

	// Binary operators: new instance = v (+) this
	inline Size2 Size2::rsub(size_t v) const { return Size2(v - x, v - y); }

	inline Size2 Size2::rsub(const Size2& v) const { return Size2(v.x - x, v.y - y); }

	inline Size2 Size2::rdiv(size_t v) const { return Size2(v / x, v / y); }

	inline Size2 Size2::rdiv(const Size2& v) const { return Size2(v.x / x, v.y / y); }

	// Augmented operators: this (+)= v
	inline void Size2::iadd(size_t v) { x += v; y += v; }

	inline void Size2::iadd(const Size2& v) { x += v.x; y += v.y; }

	inline void Size2::isub(size_t v) { x -= v; y -= v; }

	inline void Size2::isub(const Size2& v) { x -= v.x; y -= v.y; }

	inline void Size2::imul(size_t v) { x *= v; y *= v; }

	inline void Size2::imul(const Size2& v) { x *= v.x; y *= v.y; }

	inline void Size2::idiv(size_t v) { x /= v; y /= v; }

	inline void Size2::idiv(const Size2& v) { x /= v.x; y /= v.y; }

	// Basic getters
	inline const size_t& Size2::at(size_t i) const { assert(i < 2); return (&x)[i]; }

	inline size_t& Size2::at(size_t i) { assert(i < 2); return (&x)[i]; }

	inline size_t Size2::sum() const { return x + y; }

	inline size_t Size2::min() const { return std::min(x, y); }

	inline size_t Size2::max() const { return std::max(x, y); }

	inline size_t Size2::dominantAxis() const { return (x > y) ? 0 : 1; }

	inline size_t Size2::subminantAxis() const { return (x < y) ? 0 : 1; }

	inline bool Size2::isEqual(const Size2& other) const { return (x == other.x && y == other.y); }

	// Operators
	inline size_t& Size2::operator[](size_t i) { assert(i < 2); return (&x)[i]; }

	inline const size_t& Size2::operator[](size_t i) const { assert(i < 2); return (&x)[i]; }

	inline Size2& Size2::operator=(const Size2& v) { set(v); return (*this); }

	template <typename U>
	inline Size2& Size2::operator=(const std::initializer_list<U>& lst) { set(lst); return (*this); }

	inline Size2& Size2::operator+=(size_t v) { iadd(v); return (*this); }

	inline Size2& Size2::operator+=(const Size2& v) { iadd(v); return (*this); }

	inline Size2& Size2::operator-=(size_t v) { isub(v); return (*this); }

	inline Size2& Size2::operator-=(const Size2& v) { isub(v); return (*this); }

	inline Size2& Size2::operator*=(size_t v) { imul(v); return (*this); }

	inline Size2& Size2::operator*=(const Size2& v) { imul(v); return (*this); }

	inline Size2& Size2::operator/=(size_t v) { idiv(v); return (*this); }

	inline Size2& Size2::operator/=(const Size2& v) { idiv(v); return (*this); }

	inline bool Size2::operator==(const Size2& v) const { return isEqual(v); }

	inline bool Size2::operator!=(const Size2& v) const { return !isEqual(v); }

	// Math functions
	inline Size2 operator+(const Size2& a) { return a; }

	inline Size2 operator+(const Size2& a, size_t b) { return a.add(b); }

	inline Size2 operator+(size_t a, const Size2& b) { return b.add(a); }

	inline Size2 operator+(const Size2& a, const Size2& b) { return a.add(b); }

	inline Size2 operator-(const Size2& a, size_t b) { return a.sub(b); }

	inline Size2 operator-(size_t a, const Size2& b) { return b.rsub(a); }

	inline Size2 operator-(const Size2& a, const Size2& b) { return a.sub(b); }

	inline Size2 operator*(const Size2& a, size_t b) { return a.mul(b); }

	inline Size2 operator*(size_t a, const Size2& b) { return b.mul(a); }

	inline Size2 operator*(const Size2& a, const Size2& b) { return a.mul(b); }

	inline Size2 operator/(const Size2& a, size_t b) { return a.div(b); }

	inline Size2 operator/(size_t a, const Size2& b) { return b.rdiv(a); }

	inline Size2 operator/(const Size2& a, const Size2& b) { return a.div(b); }

	inline Size2 min(const Size2& a, const Size2& b) { return Size2(std::min(a.x, b.x), std::min(a.y, b.y)); }

	inline Size2 max(const Size2& a, const Size2& b) { return Size2(std::max(a.x, b.x), std::max(a.y, b.y)); }

	inline Size2 clamp(const Size2& v, const Size2& low, const Size2& high) { return Size2(clamp(v.x, low.x, high.x), clamp(v.y, low.y, high.y)); }

}