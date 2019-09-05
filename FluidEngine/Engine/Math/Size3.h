#pragma once

#include "Size2.h"

namespace Engine
{
	//!
	//! \brief 3-D size class.
	//!
	//! This class defines simple 3-D size data.
	//!
	class Size3
	{
	public:
		//! X (or the first) component of the size.
		size_t x;
		//! Y (or the second) component of the size.
		size_t y;
		//! Z (or the third) component of the size.
		size_t z;

		// MARK: Constructors
		
		//! Constructs default size (0, 0, 0).
		constexpr Size3() : x(0), y(0), z(0) {}

		//! Constructs size with given parameters \p x_, \p y_, and \p z_.
		constexpr Size3(size_t x_, size_t y_, size_t z_) : x(x_), y(y_), z(z_) {}

		//! Constructs size with a 2-D size and a scalar.
		constexpr Size3(const Size2& v, size_t z_) : x(v.x), y(v.y), z(z_) {}

		//! Constructs size with initializer list.
		template <typename U>
		Size3(const std::initializer_list<U>& lst);

		//! Copy constructor.
		constexpr Size3(const Size3& v) : x(v.x), y(v.y), z(v.z) {}

		// MARK: Basic setters
		
		//! Set all x, y, and z components to \p s.
		void set(size_t s);

		//! Set x, y, and z components with given parameters.
		void set(size_t x, size_t y, size_t z);

		//! Set x, y, and z components with given \p sz.x, \p sz.y, and \p z.
		void set(const Size2& sz, size_t z);

		//! Set x, y, and z components with given initializer list.
		template <typename U>
		void set(const std::initializer_list<U>& lst);

		//! Set x, y, and z with other size \p pt.
		void set(const Size3& v);

		//! Set both x, y, and z to zero.
		void setZero();

		// MARK: Binary operations: new instance = this (+) v
		
		//! Computes this + (v, v, v).
		Size3 add(size_t v) const;

		//! Computes this + (v.x, v.y, v.z).
		Size3 add(const Size3& v) const;

		//! Computes this - (v, v, v).
		Size3 sub(size_t v) const;

		//! Computes this - (v.x, v.y, v.z).
		Size3 sub(const Size3& v) const;

		//! Computes this * (v, v, v).
		Size3 mul(size_t v) const;

		//! Computes this * (v.x, v.y, v.z).
		Size3 mul(const Size3& v) const;
		//! Computes this / (v, v, v).
		Size3 div(size_t v) const;

		//! Computes this / (v.x, v.y, v.z).
		Size3 div(const Size3& v) const;

		// MARK: Binary operations: new instance = v (+) this
		
		//! Computes (v, v, v) - this.
		Size3 rsub(size_t v) const;

		//! Computes (v.x, v.y, v.z) - this.
		Size3 rsub(const Size3& v) const;

		//! Computes (v, v, v) / this.
		Size3 rdiv(size_t v) const;

		//! Computes (v.x, v.y, v.z) / this.
		Size3 rdiv(const Size3& v) const;

		// MARK: Augmented operations: this (+)= v
		
		//! Computes this += (v, v, v).
		void iadd(size_t v);

		//! Computes this += (v.x, v.y, v.z).
		void iadd(const Size3& v);

		//! Computes this -= (v, v, v).
		void isub(size_t v);

		//! Computes this -= (v.x, v.y, v.z).
		void isub(const Size3& v);

		//! Computes this *= (v, v, v).
		void imul(size_t v);

		//! Computes this *= (v.x, v.y, v.z).
		void imul(const Size3& v);

		//! Computes this /= (v, v, v).
		void idiv(size_t v);

		//! Computes this /= (v.x, v.y, v.z).
		void idiv(const Size3& v);

		// MARK: Basic getters
		
		//! Returns const reference to the \p i -th element of the size.
		const size_t& at(size_t i) const;

		//! Returns reference to the \p i -th element of the size.
		size_t& at(size_t i);

		//! Returns the sum of all the components (i.e. x + y).
		size_t sum() const;

		//! Returns the minimum value among x, y, and z.
		size_t min() const;

		//! Returns the maximum value among x, y, and z.
		size_t max() const;

		//! Returns the absolute minimum value among x, y, and z.
		size_t absmin() const;

		//! Returns the absolute maximum value among x, y, and z.
		size_t absmax() const;

		//! Returns the index of the dominant axis.
		size_t dominantAxis() const;

		//! Returns the index of the subminant axis.
		size_t subminantAxis() const;

		//! Returns true if \p other is the same as this size.
		bool isEqual(const Size3& other) const;

		// MARK: Operators
		
		//! Returns reference to the \p i -th element of the size.
		size_t& operator[](size_t i);

		//! Returns const reference to the \p i -th element of the size.
		const size_t& operator[](size_t i) const;

		//! Set x, y, and z components with given initializer list.
		template <typename U>
		Size3& operator=(const std::initializer_list<U>& lst);

		//! Set x, y, and z with other size \p pt.
		Size3& operator=(const Size3& v);

		//! Computes this += (v, v, v)
		Size3& operator+=(size_t v);

		//! Computes this += (v.x, v.y, v.z)
		Size3& operator+=(const Size3& v);

		//! Computes this -= (v, v, v)
		Size3& operator-=(size_t v);

		//! Computes this -= (v.x, v.y, v.z)
		Size3& operator-=(const Size3& v);

		//! Computes this *= (v, v, v)
		Size3& operator*=(size_t v);

		//! Computes this *= (v.x, v.y, v.z)
		Size3& operator*=(const Size3& v);

		//! Computes this /= (v, v, v)
		Size3& operator/=(size_t v);

		//! Computes this /= (v.x, v.y, v.z)
		Size3& operator/=(const Size3& v);

		//! Returns true if \p other is the same as this size.
		bool operator==(const Size3& v) const;

		//! Returns true if \p other is the not same as this size.
		bool operator!=(const Size3& v) const;

	};

	//! Positive sign operator.
	Size3 operator+(const Size3& a);

	//! Negative sign operator.
	Size3 operator-(const Size3& a);

	//! Computes (a, a, a) + (b.x, b.y, b.z).
	Size3 operator+(size_t a, const Size3& b);

	//! Computes (a.x, a.y, a.z) + (b.x, b.y, b.z).
	Size3 operator+(const Size3& a, const Size3& b);

	//! Computes (a.x, a.y, a.z) - (b, b, b).
	Size3 operator-(const Size3& a, size_t b);

	//! Computes (a, a, a) - (b.x, b.y, b.z).
	Size3 operator-(size_t a, const Size3& b);

	//! Computes (a.x, a.y, a.z) - (b.x, b.y, b.z).
	Size3 operator-(const Size3& a, const Size3& b);

	//! Computes (a.x, a.y, a.z) * (b, b, b).
	Size3 operator*(const Size3& a, size_t b);

	//! Computes (a, a, a) * (b.x, b.y, b.z).
	Size3 operator*(size_t a, const Size3& b);

	//! Computes (a.x, a.y, a.z) * (b.x, b.y, b.z).
	Size3 operator*(const Size3& a, const Size3& b);

	//! Computes (a.x, a.y, a.z) / (b, b, b).
	Size3 operator/(const Size3& a, size_t b);

	//! Computes (a, a, a) / (b.x, b.y, b.z).
	Size3 operator/(size_t a, const Size3& b);

	//! Computes (a.x, a.y, a.z) / (b.x, b.y, b.z).
	Size3 operator/(const Size3& a, const Size3& b);

	//! Returns element-wise min size.
	Size3 min(const Size3& a, const Size3& b);

	//! Returns element-wise max size.
	Size3 max(const Size3& a, const Size3& b);

	//! Returns element-wise clamped size.
	Size3 clamp(const Size3& v, const Size3& low, const Size3& high);

	//! Returns element-wise ceiled size.
	Size3 ceil(const Size3& a);

	//! Returns element-wise floored size.
	Size3 floor(const Size3& a);

	// Constructors
	template <typename U>
	inline Size3::Size3(const std::initializer_list<U>& lst) { set(lst); }

	// Basic setters
	inline void Size3::set(size_t newX, size_t newY, size_t newZ) { x = newX; y = newY; z = newZ; }

	inline void Size3::set(const Size2& sz, size_t newZ) { x = sz.x; y = sz.y; z = newZ; }

	template <typename U>
	inline void Size3::set(const std::initializer_list<U>& lst) 
	{
		assert(lst.size() >= 3);
		auto inputElem = lst.begin();
		x = static_cast<U>(*inputElem);
		y = static_cast<U>(*(++inputElem));
		z = static_cast<U>(*(++inputElem));
	}

	inline void Size3::set(const Size3& v) { x = v.x; y = v.y; z = v.z; }

	inline void Size3::setZero() { x = y = z = 0; }
		
	// Binary operators: new instance = this (+) v
	inline Size3 Size3::add(size_t v) const { return Size3(x + v, y + v, z + v); }

	inline Size3 Size3::add(const Size3& v) const { return Size3(x + v.x, y + v.y, z + v.z); }

	inline Size3 Size3::sub(size_t v) const { return Size3(x - v, y - v, z - v); }

	inline Size3 Size3::sub(const Size3& v) const { return Size3(x - v.x, y - v.y, z - v.z); }

	inline Size3 Size3::mul(size_t v) const { return Size3(x * v, y * v, z * v); }

	inline Size3 Size3::mul(const Size3& v) const { return Size3(x * v.x, y * v.y, z * v.z); }

	inline Size3 Size3::div(size_t v) const { return Size3(x / v, y / v, z / v); }

	inline Size3 Size3::div(const Size3& v) const { return Size3(x / v.x, y / v.y, z / v.z); }

	// Binary operators: new instance = v (+) this
	inline Size3 Size3::rsub(size_t v) const { return Size3(v - x, v - y, v - z); }

	inline Size3 Size3::rsub(const Size3& v) const { return Size3(v.x - x, v.y - y, v.z - z); }

	inline Size3 Size3::rdiv(size_t v) const { return Size3(v / x, v / y, v / z); }

	inline Size3 Size3::rdiv(const Size3& v) const { return Size3(v.x / x, v.y / y, v.z / z); }

	// Augmented operators: this (+)= v
	inline void Size3::iadd(size_t v) { x += v; y += v; z += v; }

	inline void Size3::iadd(const Size3& v) { x += v.x; y += v.y; z += v.z; }

	inline void Size3::isub(size_t v) { x -= v; y -= v; z -= v; }

	inline void Size3::isub(const Size3& v) { x -= v.x; y -= v.y; z -= v.z; }

	inline void Size3::imul(size_t v) { x *= v; y *= v; z *= v; }

	inline void Size3::imul(const Size3& v) { x *= v.x; y *= v.y; z *= v.z; }

	inline void Size3::idiv(size_t v) { x /= v; y /= v; z /= v; }

	inline void Size3::idiv(const Size3& v) { x /= v.x; y /= v.y; z /= v.z; }

	// Basic getters
	inline const size_t& Size3::at(size_t i) const { assert(i < 3); return (&x)[i]; }

	inline size_t& Size3::at(size_t i) { assert(i < 3); return (&x)[i]; }

	inline size_t Size3::sum() const { return x + y + z; }

	inline size_t Size3::min() const { return std::min(std::min(x, y), z); }

	inline size_t Size3::max() const { return std::max(std::max(x, y), z); }

	inline size_t Size3::dominantAxis() const { return (x > y) ? ((x > z) ? 0 : 2) : ((y > z) ? 1 : 2); }

	inline size_t Size3::subminantAxis() const { return (x < y) ? ((x < z) ? 0 : 2) : ((y < z) ? 1 : 2); }

	inline bool Size3::isEqual(const Size3& other) const { return (x == other.x && y == other.y && z == other.z); }

	// Operators
	inline size_t& Size3::operator[](size_t i) { assert(i < 3); return (&x)[i]; }

	inline const size_t& Size3::operator[](size_t i) const { assert(i < 3); return (&x)[i]; }

	inline Size3& Size3::operator=(const Size3& v) { set(v); return (*this); }

	inline Size3& Size3::operator+=(size_t v) { iadd(v); return (*this); }

	inline Size3& Size3::operator+=(const Size3& v) { iadd(v); return (*this); }

	inline Size3& Size3::operator-=(size_t v) { isub(v); return (*this); }

	inline Size3& Size3::operator-=(const Size3& v) { isub(v); return (*this); }

	inline Size3& Size3::operator*=(size_t v) { imul(v); return (*this); }

	inline Size3& Size3::operator*=(const Size3& v) { imul(v); return (*this); }

	inline Size3& Size3::operator/=(size_t v) { idiv(v); return (*this); }

	inline Size3& Size3::operator/=(const Size3& v) { idiv(v); return (*this); }

	inline bool Size3::operator==(const Size3& v) const { return isEqual(v); }

	inline bool Size3::operator!=(const Size3& v) const { return !isEqual(v); }

	inline Size3 operator+(const Size3& a) { return a; }

	inline Size3 operator+(const Size3& a, size_t b) { return a.add(b); }

	inline Size3 operator+(size_t a, const Size3& b) { return b.add(a); }

	inline Size3 operator+(const Size3& a, const Size3& b) { return a.add(b); }

	inline Size3 operator-(const Size3& a, size_t b) { return a.sub(b); }

	inline Size3 operator-(size_t a, const Size3& b) { return b.rsub(a); }

	inline Size3 operator-(const Size3& a, const Size3& b) { return a.sub(b); }

	inline Size3 operator*(const Size3& a, size_t b) { return a.mul(b); }

	inline Size3 operator*(size_t a, const Size3& b) { return b.mul(a); }

	inline Size3 operator*(const Size3& a, const Size3& b) { return a.mul(b); }

	inline Size3 operator/(const Size3& a, size_t b) { return a.div(b); }

	inline Size3 operator/(size_t a, const Size3& b) { return b.rdiv(a); }

	inline Size3 operator/(const Size3& a, const Size3& b) { return a.div(b); }

	inline Size3 min(const Size3& a, const Size3& b) 
	{
		return Size3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
	}

	inline Size3 max(const Size3& a, const Size3& b) 
	{
		return Size3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
	}

	inline Size3 clamp(const Size3& v, const Size3& low, const Size3& high) 
	{
		return Size3(
			clamp(v.x, low.x, high.x),
			clamp(v.y, low.y, high.y),
			clamp(v.z, low.z, high.z));
	}


}