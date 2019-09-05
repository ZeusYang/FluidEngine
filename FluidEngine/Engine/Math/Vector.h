#pragma once

#include <array>
#include <type_traits>

#include "../Utils/Constants.h"
#include "../Utils/MathUtils.h"
#include "ArrayAccessor1.h"
#include "VectorExpression.h"

namespace Engine
{
	//!
	//! \brief Generic statically-sized N-D vector class.
	//!
	//! This class defines N-D vector data where its size is determined statically
	//! at compile time.
	//!
	//! \tparam T - Number type.
	//! \tparam N - Dimension.
	//!
	template <typename T, size_t N>
	class Vector final : public VectorExpression<T, Vector<T, N>>
	{
	public:
		static_assert(N > 0,
			"Size of static-sized vector should be greater than zero.");
		static_assert(std::is_floating_point<T>::value,
			"Vector only can be instantiated with floating point types");

		typedef std::array<T, N> ContainerType;

		//! Constructs a vector with zeros.
		Vector();

		//! Constructs vector instance with parameters.
		template <typename... Params>
		explicit Vector(Params... params);

		//! Constructs vector instance with initializer list.
		template <typename U>
		Vector(const std::initializer_list<U>& lst);

		//! Constructs vector with expression template.
		template <typename E>
		Vector(const VectorExpression<T, E>& other);

		//! Copy constructor.
		Vector(const Vector& other);

		//! Sets all elements to \p s.
		void set(const T& s);

		//! Set vector instance with initializer list.
		template <typename U>
		void set(const std::initializer_list<U>& lst);

		//! Sets vector with expression template.
		template <typename E>
		void set(const VectorExpression<T, E>& other);

		//! Swaps the content of the vector with \p other vector.
		void swap(Vector& other);

		//! Sets all elements to zero.
		void setZero();

		//! Normalizes this vector.
		void normalize();

		//! Returns the size of the vector.
		constexpr size_t size() const;

		//! Returns the raw pointer to the vector data.
		T* data();

		//! Returns the const raw pointer to the vector data.
		const T* const data() const;

		//! Returns the begin iterator of the vector.
		typename ContainerType::iterator begin();

		//! Returns the begin const iterator of the vector.
		typename ContainerType::const_iterator begin() const;

		//! Returns the end iterator of the vector.
		typename ContainerType::iterator end();

		//! Returns the end const iterator of the vector.
		typename ContainerType::const_iterator end() const;

		//! Returns the array accessor.
		ArrayAccessor1<T> accessor();

		//! Returns the const array accessor.
		ConstArrayAccessor1<T> constAccessor() const;

		//! Returns const reference to the \p i -th element of the vector.
		T at(size_t i) const;

		//! Returns reference to the \p i -th element of the vector.
		T& at(size_t i);

		//! Returns the sum of all the elements.
		T sum() const;

		//! Returns the average of all the elements.
		T avg() const;

		//! Returns the minimum element.
		T min() const;

		//! Returns the maximum element.
		T max() const;

		//! Returns the absolute minimum element.
		T absmin() const;

		//! Returns the absolute maximum element.
		T absmax() const;

		//! Returns the index of the dominant axis.
		size_t dominantAxis() const;

		//! Returns the index of the subminant axis.
		size_t subminantAxis() const;

		//! Returns normalized vector.
		VectorScalarDiv<T, Vector> normalized() const;

		//! Returns the length of the vector.
		T length() const;

		//! Returns the squared length of the vector.
		T lengthSquared() const;

		//! Returns the distance to the other vector.
		template <typename E>
		T distanceTo(const E& other) const;

		//! Returns the squared distance to the other vector.
		template <typename E>
		T distanceSquaredTo(const E& other) const;

		//! Returns a vector with different value type.
		template <typename U>
		VectorTypeCast<U, Vector<T, N>, T> castTo() const;

		//! Returns true if \p other is the same as this vector.
		template <typename E>
		bool isEqual(const E& other) const;

		//! Returns true if \p other is similar to this vector.
		template <typename E>
		bool isSimilar(const E& other,
			T epsilon = std::numeric_limits<T>::epsilon()) const;

		//! Computes this + v.
		template <typename E>
		VectorAdd<T, Vector, E> add(const E& v) const;

		//! Computes this + (s, s, ... , s).
		VectorScalarAdd<T, Vector> add(const T& s) const;

		//! Computes this - v.
		template <typename E>
		VectorSub<T, Vector, E> sub(const E& v) const;

		//! Computes this - (s, s, ... , s).
		VectorScalarSub<T, Vector> sub(const T& s) const;

		//! Computes this * v.
		template <typename E>
		VectorMul<T, Vector, E> mul(const E& v) const;

		//! Computes this * (s, s, ... , s).
		VectorScalarMul<T, Vector> mul(const T& s) const;

		//! Computes this / v.
		template <typename E>
		VectorDiv<T, Vector, E> div(const E& v) const;

		//! Computes this / (s, s, ... , s).
		VectorScalarDiv<T, Vector> div(const T& s) const;

		//! Computes dot product.
		template <typename E>
		T dot(const E& v) const;

		// MARK: Binary operations: new instance = v (+) this

		//! Computes (s, s, ... , s) - this.
		VectorScalarRSub<T, Vector> rsub(const T& s) const;

		//! Computes v - this.
		template <typename E>
		VectorSub<T, Vector, E> rsub(const E& v) const;

		//! Computes (s, s, ... , s) / this.
		VectorScalarRDiv<T, Vector> rdiv(const T& s) const;

		//! Computes v / this.
		template <typename E>
		VectorDiv<T, Vector, E> rdiv(const E& v) const;

		// MARK: Augmented operations: this (+)= v

		//! Computes this += (s, s, ... , s).
		void iadd(const T& s);

		//! Computes this += v.
		template <typename E>
		void iadd(const E& v);

		//! Computes this -= (s, s, ... , s).
		void isub(const T& s);

		//! Computes this -= v.
		template <typename E>
		void isub(const E& v);

		//! Computes this *= (s, s, ... , s).
		void imul(const T& s);

		//! Computes this *= v.
		template <typename E>
		void imul(const E& v);

		//! Computes this /= (s, s, ... , s).
		void idiv(const T& s);

		//! Computes this /= v.
		template <typename E>
		void idiv(const E& v);

		//!
		//! \brief Iterates the vector and invoke given \p func for each element.
		//!
		//! This function iterates the vector elements and invoke the callback
		//! function \p func. The callback function takes array's element as its
		//! input. The order of execution will be 0 to N-1 where N is the size of
		//! the vector. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! Vector<float, 2> vec(10, 4.f);
		//! vec.forEach([](float elem) {
		//!     printf("%d\n", elem);
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void forEach(Callback func) const;

		//!
		//! \brief Iterates the vector and invoke given \p func for each index.
		//!
		//! This function iterates the vector elements and invoke the callback
		//! function \p func. The callback function takes one parameter which is the
		//! index of the vector. The order of execution will be 0 to N-1 where N is
		//! the size of the array. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! Vector<float, 2> vec(10, 4.f);
		//! vec.forEachIndex([&](size_t i) {
		//!     vec[i] = 4.f * i + 1.5f;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void forEachIndex(Callback func) const;

		//! Returns the const reference to the \p i -th element.
		const T& operator[](size_t i) const;

		//! Returns the reference to the \p i -th element.
		T& operator[](size_t);

		//! Set vector instance with initializer list.
		template <typename U>
		Vector& operator=(const std::initializer_list<U>& lst);

		//! Sets vector with expression template.
		template <typename E>
		Vector& operator=(const VectorExpression<T, E>& other);

		//! Computes this += (s, s, ... , s)
		Vector& operator+=(const T& s);

		//! Computes this += v
		template <typename E>
		Vector& operator+=(const E& v);

		//! Computes this -= (s, s, ... , s)
		Vector& operator-=(const T& s);

		//! Computes this -= v
		template <typename E>
		Vector& operator-=(const E& v);

		//! Computes this *= (s, s, ... , s)
		Vector& operator*=(const T& s);

		//! Computes this *= v
		template <typename E>
		Vector& operator*=(const E& v);

		//! Computes this /= (s, s, ... , s)
		Vector& operator/=(const T& s);

		//! Computes this /= v
		template <typename E>
		Vector& operator/=(const E& v);

		//! Returns true if \p other is the same as this vector.
		template <typename E>
		bool operator==(const E& v) const;

		//! Returns true if \p other is the not same as this vector.
		template <typename E>
		bool operator!=(const E& v) const;

	private:
		ContainerType _elements;

		template <typename... Params>
		void setAt(size_t i, T v, Params... params);
		void setAt(size_t i, T v);
	};

	//! Returns the type of the value itself.
	template <typename T>
	struct ScalarType 
	{
		typedef T value;
	};

	//! Returns the type of the value.
	template <typename T, size_t N>
	struct ScalarType<Vector<T, N>> 
	{
		typedef T value;
	};

	//! ---------------------------Definition----------------------------
	template <typename T, size_t N>
	Vector<T, N>::Vector() 
	{
		for (auto& elem : _elements) 
			elem = static_cast<T>(0);
	}

	template <typename T, size_t N>
	template <typename... Params>
	Vector<T, N>::Vector(Params... params) 
	{
		static_assert(sizeof...(params) == N, "Invalid number of parameters.");
		setAt(0, params...);
	}

	template <typename T, size_t N>
	template <typename U>
	Vector<T, N>::Vector(const std::initializer_list<U>& lst)  { set(lst); }

	template <typename T, size_t N>
	template <typename E>
	Vector<T, N>::Vector(const VectorExpression<T, E>& other) { set(other); }

	template <typename T, size_t N>
	Vector<T, N>::Vector(const Vector& other) : _elements(other._elements) {}

	template <typename T, size_t N>
	void Vector<T, N>::set(const T& s) { _elements.fill(s); }

	template <typename T, size_t N>
	template <typename U>
	void Vector<T, N>::set(const std::initializer_list<U>& lst) 
	{
		assert(lst.size() >= N);
		size_t i = 0;
		for (const auto& inputElem : lst) 
		{
			_elements[i] = static_cast<T>(inputElem);
			++i;
		}
	}

	template <typename T, size_t N>
	template <typename E>
	void Vector<T, N>::set(const VectorExpression<T, E>& other) 
	{
		assert(size() == other.size());
		// Parallel evaluation of the expression
		const E& expression = other();
		forEachIndex([&](size_t i) { _elements[i] = expression[i]; });
	}

	template <typename T, size_t N>
	void Vector<T, N>::swap(Vector& other) { std::swap(other._elements, _elements); }

	template <typename T, size_t N>
	void Vector<T, N>::setZero() { set(T(0)); }

	template <typename T, size_t N>
	void Vector<T, N>::normalize() { idiv(length()); }

	template <typename T, size_t N>
	constexpr size_t Vector<T, N>::size() const { return N; }

	template <typename T, size_t N>
	T* Vector<T, N>::data() { return _elements.data(); }

	template <typename T, size_t N>
	const T* const Vector<T, N>::data() const { return _elements.data(); }

	template <typename T, size_t N>
	typename Vector<T, N>::ContainerType::iterator Vector<T, N>::begin() 
	{
		return _elements.begin();
	}

	template <typename T, size_t N>
	typename Vector<T, N>::ContainerType::const_iterator Vector<T, N>::begin() const 
	{
		return _elements.cbegin();
	}

	template <typename T, size_t N>
	typename Vector<T, N>::ContainerType::iterator Vector<T, N>::end() 
	{
		return _elements.end();
	}

	template <typename T, size_t N>
	typename Vector<T, N>::ContainerType::const_iterator Vector<T, N>::end() const 
	{
		return _elements.cend();
	}

	template <typename T, size_t N>
	ArrayAccessor1<T> Vector<T, N>::accessor() { return ArrayAccessor1<T>(size(), data()); }

	template <typename T, size_t N>
	ConstArrayAccessor1<T> Vector<T, N>::constAccessor() const { return ConstArrayAccessor1<T>(size(), data()); }

	template <typename T, size_t N>
	T Vector<T, N>::at(size_t i) const { return _elements[i]; }

	template <typename T, size_t N>
	T& Vector<T, N>::at(size_t i) { return _elements[i]; }

	template <typename T, size_t N>
	T Vector<T, N>::sum() const 
	{
		T ret = 0;
		for (T val : _elements) 
			ret += val;
		return ret;
	}

	template <typename T, size_t N>
	T Vector<T, N>::avg() const { return sum() / static_cast<T>(size()); }

	template <typename T, size_t N>
	T Vector<T, N>::min() const 
	{
		T ret = _elements.front();
		for (T val : _elements) 
			ret = std::min(ret, val);
		return ret;
	}

	template <typename T, size_t N>
	T Vector<T, N>::max() const 
	{
		T ret = _elements.front();
		for (T val : _elements) 
			ret = std::max(ret, val);
		return ret;
	}

	template <typename T, size_t N>
	T Vector<T, N>::absmin() const 
	{
		T ret = _elements.front();
		for (T val : _elements) 
			ret = Engine::absmin(ret, val);
		return ret;
	}

	template <typename T, size_t N>
	T Vector<T, N>::absmax() const 
	{
		T ret = _elements.front();
		for (T val : _elements) 
			ret = Engine::absmax(ret, val);
		return ret;
	}

	template <typename T, size_t N>
	size_t Vector<T, N>::dominantAxis() const 
	{
		auto iter = std::max_element(begin(), end(), [](const T& a, const T& b) 
		{
			return std::fabs(a) < std::fabs(b);
		});
		return iter - begin();
	}

	template <typename T, size_t N>
	size_t Vector<T, N>::subminantAxis() const 
	{
		auto iter = std::max_element(begin(), end(), [](const T& a, const T& b) 
		{
			return std::fabs(a) > std::fabs(b);
		});
		return iter - begin();
	}

	template <typename T, size_t N>
	VectorScalarDiv<T, Vector<T, N>> Vector<T, N>::normalized() const 
	{
		T len = length();
		return VectorScalarDiv<T, Vector>(*this, len);
	}

	template <typename T, size_t N>
	T Vector<T, N>::length() const { return std::sqrt(lengthSquared()); }

	template <typename T, size_t N>
	T Vector<T, N>::lengthSquared() const { return dot(*this); }

	template <typename T, size_t N>
	template <typename E>
	T Vector<T, N>::distanceTo(const E& other) const 
	{
		return std::sqrt(distanceSquaredTo(other));
	}

	template <typename T, size_t N>
	template <typename E>
	T Vector<T, N>::distanceSquaredTo(const E& other) const 
	{
		assert(size() == other.size());
		T ret = 0;
		for (size_t i = 0; i < N; ++i) 
		{
			T diff = (_elements[i] - other[i]);
			ret += diff * diff;
		}

		return ret;
	}

	template <typename T, size_t N>
	template <typename U>
	VectorTypeCast<U, Vector<T, N>, T> Vector<T, N>::castTo() const 
	{
		return VectorTypeCast<U, Vector<T, N>, T>(*this);
	}

	template <typename T, size_t N>
	template <typename E>
	bool Vector<T, N>::isEqual(const E& other) const 
	{
		if (size() != other.size()) 
			return false;
		for (size_t i = 0; i < size(); ++i) 
			if (at(i) != other[i]) 
				return false;
		return true;
	}

	template <typename T, size_t N>
	template <typename E>
	bool Vector<T, N>::isSimilar(const E& other, T epsilon) const 
	{
		if (size() != other.size()) 
			return false;
		for (size_t i = 0; i < size(); ++i) 
			if (std::fabs(at(i) - other[i]) > epsilon) 
				return false;		
		return true;
	}

	template <typename T, size_t N>
	template <typename E>
	VectorAdd<T, Vector<T, N>, E> Vector<T, N>::add(const E& v) const 
	{
		return VectorAdd<T, Vector, E>(*this, v);
	}

	template <typename T, size_t N>
	VectorScalarAdd<T, Vector<T, N>> Vector<T, N>::add(const T& s) const 
	{
		return VectorScalarAdd<T, Vector>(*this, s);
	}

	template <typename T, size_t N>
	template <typename E>
	VectorSub<T, Vector<T, N>, E> Vector<T, N>::sub(const E& v) const 
	{
		return VectorSub<T, Vector, E>(*this, v);
	}

	template <typename T, size_t N>
	VectorScalarSub<T, Vector<T, N>> Vector<T, N>::sub(const T& s) const 
	{
		return VectorScalarSub<T, Vector>(*this, s);
	}

	template <typename T, size_t N>
	template <typename E>
	VectorMul<T, Vector<T, N>, E> Vector<T, N>::mul(const E& v) const 
	{
		return VectorMul<T, Vector, E>(*this, v);
	}

	template <typename T, size_t N>
	VectorScalarMul<T, Vector<T, N>> Vector<T, N>::mul(const T& s) const 
	{
		return VectorScalarMul<T, Vector>(*this, s);
	}

	template <typename T, size_t N>
	template <typename E>
	VectorDiv<T, Vector<T, N>, E> Vector<T, N>::div(const E& v) const 
	{
		return VectorDiv<T, Vector, E>(*this, v);
	}

	template <typename T, size_t N>
	VectorScalarDiv<T, Vector<T, N>> Vector<T, N>::div(const T& s) const 
	{
		return VectorScalarDiv<T, Vector>(*this, s);
	}

	template <typename T, size_t N>
	template <typename E>
	T Vector<T, N>::dot(const E& v) const 
	{
		assert(size() == v.size());
		T ret = 0;
		for (size_t i = 0; i < N; ++i) 
			ret += _elements[i] * v[i];
		return ret;
	}

	template <typename T, size_t N>
	VectorScalarRSub<T, Vector<T, N>> Vector<T, N>::rsub(const T& s) const 
	{
		return VectorScalarRSub<T, Vector>(*this, s);
	}

	template <typename T, size_t N>
	template <typename E>
	VectorSub<T, Vector<T, N>, E> Vector<T, N>::rsub(const E& v) const 
	{
		return VectorSub<T, Vector, E>(v, *this);
	}

	template <typename T, size_t N>
	VectorScalarRDiv<T, Vector<T, N>> Vector<T, N>::rdiv(const T& s) const 
	{
		return VectorScalarRDiv<T, Vector>(*this, s);
	}

	template <typename T, size_t N>
	template <typename E>
	VectorDiv<T, Vector<T, N>, E> Vector<T, N>::rdiv(const E& v) const 
	{
		return VectorDiv<T, Vector, E>(v, *this);
	}

	template <typename T, size_t N>
	void Vector<T, N>::iadd(const T& s)  { set(add(s)); }

	template <typename T, size_t N>
	template <typename E>
	void Vector<T, N>::iadd(const E& v) { set(add(v)); }

	template <typename T, size_t N>
	void Vector<T, N>::isub(const T& s) { set(sub(s)); }

	template <typename T, size_t N>
	template <typename E>
	void Vector<T, N>::isub(const E& v) { set(sub(v)); }

	template <typename T, size_t N>
	void Vector<T, N>::imul(const T& s) { set(mul(s)); }

	template <typename T, size_t N>
	template <typename E>
	void Vector<T, N>::imul(const E& v) { set(mul(v)); }

	template <typename T, size_t N>
	void Vector<T, N>::idiv(const T& s) { set(div(s)); }

	template <typename T, size_t N>
	template <typename E>
	void Vector<T, N>::idiv(const E& v) { set(div(v)); }

	template <typename T, size_t N>
	template <typename Callback>
	void Vector<T, N>::forEach(Callback func) const { constAccessor().forEach(func); }

	template <typename T, size_t N>
	template <typename Callback>
	void Vector<T, N>::forEachIndex(Callback func) const { constAccessor().forEachIndex(func); }

	template <typename T, size_t N>
	const T& Vector<T, N>::operator[](size_t i) const { return _elements[i]; }

	template <typename T, size_t N>
	T& Vector<T, N>::operator[](size_t i) { return _elements[i]; }

	template <typename T, size_t N>
	template <typename U>
	Vector<T, N>& Vector<T, N>::operator=(const std::initializer_list<U>& lst) { set(lst); return *this; }

	template <typename T, size_t N>
	template <typename E>
	Vector<T, N>& Vector<T, N>::operator=(const VectorExpression<T, E>& other) { set(other); return *this; }

	template <typename T, size_t N>
	Vector<T, N>& Vector<T, N>::operator+=(const T& s) { iadd(s); return *this; }

	template <typename T, size_t N>
	template <typename E>
	Vector<T, N>& Vector<T, N>::operator+=(const E& v) { iadd(v); return *this; }

	template <typename T, size_t N>
	Vector<T, N>& Vector<T, N>::operator-=(const T& s) { isub(s); return *this; }

	template <typename T, size_t N>
	template <typename E>
	Vector<T, N>& Vector<T, N>::operator-=(const E& v) { isub(v); return *this; }

	template <typename T, size_t N>
	Vector<T, N>& Vector<T, N>::operator*=(const T& s) { imul(s); return *this; }

	template <typename T, size_t N>
	template <typename E>
	Vector<T, N>& Vector<T, N>::operator*=(const E& v) { imul(v); return *this; }

	template <typename T, size_t N>
	Vector<T, N>& Vector<T, N>::operator/=(const T& s) { idiv(s); return *this; }

	template <typename T, size_t N>
	template <typename E>
	Vector<T, N>& Vector<T, N>::operator/=(const E& v) { idiv(v); return *this; }

	template <typename T, size_t N>
	template <typename E>
	bool Vector<T, N>::operator==(const E& v) const { return isEqual(v); }

	template <typename T, size_t N>
	template <typename E>
	bool Vector<T, N>::operator!=(const E& v) const { return !isEqual(v); }

	template <typename T, size_t N>
	template <typename... Params>
	void Vector<T, N>::setAt(size_t i, T v, Params... params) 
	{
		_elements[i] = v;
		setAt(i + 1, params...);
	}

	template <typename T, size_t N>
	void Vector<T, N>::setAt(size_t i, T v) { _elements[i] = v; }

}