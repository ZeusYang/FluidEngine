#pragma once

#include "../Utils/Macros.h"
#include "../Utils/MathUtils.h"
#include "../Utils/Parallel.h"
#include "ArrayAccessor1.h"
#include "VectorExpression.h"

#include <limits>
#include <vector>
#include <initializer_list>

namespace Engine
{

	//!
	//! \brief General purpose dynamically-sizedN-D vector class.
	//!
	//! This class defines N-D vector data where its size can be defined
	//! dynamically.
	//!
	//! \tparam T Type of the element.
	//!
	template <typename T>
	class VectorN final : public VectorExpression<T, VectorN<T>>
	{
	public:
		static_assert(std::is_floating_point<T>::value,
			"VectorN only can be instantiated with floating point types");

		typedef std::vector<T> ContainerType;

		// MARK: Constructors

		//! Constructs empty vector.
		VectorN();

		//! Constructs default vector (val, val, ... , val).
		VectorN(size_t n, const T& val = 0);

		//! Constructs vector with given initializer list.
		template <typename U>
		VectorN(const std::initializer_list<U>& lst);

		//! Constructs vector with expression template.
		template <typename E>
		VectorN(const VectorExpression<T, E>& other);

		//! Copy constructor.
		VectorN(const VectorN& other);

		//! Move constructor.
		VectorN(VectorN&& other);

		// MARK: Basic setters

		//! Resizes to \p n dimensional vector with initial value \p val.
		void resize(size_t n, const T& val = 0);

		//! Clears the vector and make it zero-dimensional.
		void clear();

		//! Sets all elements to \p s.
		void set(const T& s);

		//! Sets all elements with given initializer list.
		template <typename U>
		void set(const std::initializer_list<U>& lst);

		//! Sets vector with expression template.
		template <typename E>
		void set(const VectorExpression<T, E>& other);

		//! Adds an element.
		void append(const T& val);

		//! Swaps the content of the vector with \p other vector.
		void swap(VectorN& other);

		//! Sets all elements to zero.
		void setZero();

		//! Normalizes this vector.
		void normalize();

		// MARK: Basic getters

		//! Returns the size of the vector.
		size_t size() const;

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
		VectorScalarDiv<T, VectorN> normalized() const;

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
		VectorTypeCast<U, VectorN<T>, T> castTo() const;

		//! Returns true if \p other is the same as this vector.
		template <typename E>
		bool isEqual(const E& other) const;

		//! Returns true if \p other is similar to this vector.
		template <typename E>
		bool isSimilar(const E& other,
			T epsilon = std::numeric_limits<T>::epsilon()) const;

		// MARK: Binary operations: new instance = this (+) v

		//! Computes this + v.
		template <typename E>
		VectorAdd<T, VectorN, E> add(const E& v) const;

		//! Computes this + (s, s, ... , s).
		VectorScalarAdd<T, VectorN> add(const T& s) const;

		//! Computes this - v.
		template <typename E>
		VectorSub<T, VectorN, E> sub(const E& v) const;

		//! Computes this - (s, s, ... , s).
		VectorScalarSub<T, VectorN> sub(const T& s) const;

		//! Computes this * v.
		template <typename E>
		VectorMul<T, VectorN, E> mul(const E& v) const;

		//! Computes this * (s, s, ... , s).
		VectorScalarMul<T, VectorN> mul(const T& s) const;

		//! Computes this / v.
		template <typename E>
		VectorDiv<T, VectorN, E> div(const E& v) const;

		//! Computes this / (s, s, ... , s).
		VectorScalarDiv<T, VectorN> div(const T& s) const;

		//! Computes dot product.
		template <typename E>
		T dot(const E& v) const;

		// MARK: Binary operations: new instance = v (+) this

		//! Computes (s, s, ... , s) - this.
		VectorScalarRSub<T, VectorN> rsub(const T& s) const;

		//! Computes v - this.
		template <typename E>
		VectorSub<T, VectorN, E> rsub(const E& v) const;

		//! Computes (s, s, ... , s) / this.
		VectorScalarRDiv<T, VectorN> rdiv(const T& s) const;

		//! Computes v / this.
		template <typename E>
		VectorDiv<T, VectorN, E> rdiv(const E& v) const;

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

		// MARK: Operators

		//!
		//! \brief Iterates the vector and invoke given \p func for each element.
		//!
		//! This function iterates the vector elements and invoke the callback
		//! function \p func. The callback function takes array's element as its
		//! input. The order of execution will be 0 to N-1 where N is the size of
		//! the vector. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! VectorN<float> vec(10, 4.f);
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
		//! VectorN<float> vec(10, 4.f);
		//! vec.forEachIndex([&](size_t i) {
		//!     vec[i] = 4.f * i + 1.5f;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void forEachIndex(Callback func) const;

		//!
		//! \brief Iterates the vector and invoke given \p func for each element in
		//!     parallel using multi-threading.
		//!
		//! This function iterates the vector elements and invoke the callback
		//! function \p func in parallel using multi-threading. The callback
		//! function takes vector's element as its input. The order of execution
		//! will be non-deterministic since it runs in parallel.
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! VectorN<float> vec(1000, 4.f);
		//! vec.parallelForEach([](float& elem) {
		//!     elem *= 2;
		//! });
		//! \endcode
		//!
		//! The parameter type of the callback function doesn't have to be T&, but
		//! const T& or T can be used as well.
		//!
		template <typename Callback>
		void parallelForEach(Callback func);

		//!
		//! \brief Iterates the vector and invoke given \p func for each index in
		//!     parallel using multi-threading.
		//!
		//! This function iterates the vector elements and invoke the callback
		//! function \p func in parallel using multi-threading. The callback
		//! function takes one parameter which is the index of the vector. The order
		//! of execution will be non-deterministic since it runs in parallel.
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! VectorN<float> vec(1000, 4.f);
		//! vec.parallelForEachIndex([](size_t i) {
		//!     array[i] *= 2;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void parallelForEachIndex(Callback func) const;

		//! Returns the \p i -th element.
		T operator[](size_t i) const;

		//! Returns the reference to the \p i -th element.
		T& operator[](size_t i);

		//! Sets vector with given initializer list.
		template <typename U>
		VectorN& operator=(const std::initializer_list<U>& lst);

		//! Sets vector with expression template.
		template <typename E>
		VectorN& operator=(const VectorExpression<T, E>& other);

		//! Copy assignment.
		VectorN& operator=(const VectorN& other);

		//! Move assignment.
		VectorN& operator=(VectorN&& other);

		//! Computes this += (s, s, ... , s)
		VectorN& operator+=(const T& s);

		//! Computes this += v
		template <typename E>
		VectorN& operator+=(const E& v);

		//! Computes this -= (s, s, ... , s)
		VectorN& operator-=(const T& s);

		//! Computes this -= v
		template <typename E>
		VectorN& operator-=(const E& v);

		//! Computes this *= (s, s, ... , s)
		VectorN& operator*=(const T& s);

		//! Computes this *= v
		template <typename E>
		VectorN& operator*=(const E& v);

		//! Computes this /= (s, s, ... , s)
		VectorN& operator/=(const T& s);

		//! Computes this /= v
		template <typename E>
		VectorN& operator/=(const E& v);

		//! Returns true if \p other is the same as this vector.
		template <typename E>
		bool operator==(const E& v) const;

		//! Returns true if \p other is the not same as this vector.
		template <typename E>
		bool operator!=(const E& v) const;

	private:
		ContainerType _elements;

	};

	//! Float-type N-D vector.
	typedef VectorN<float> VectorNF;

	//! Double-type N-D vector.
	typedef VectorN<double> VectorND;

	// MARK: VectorN

	template <typename T>
	VectorN<T>::VectorN() {}

	template <typename T>
	VectorN<T>::VectorN(size_t n, const T& val) : _elements(n, val) {}

	template <typename T>
	template <typename U>
	VectorN<T>::VectorN(const std::initializer_list<U>& lst) { set(lst); }

	template <typename T>
	template <typename E>
	VectorN<T>::VectorN(const VectorExpression<T, E>& other) { set(other); }

	template <typename T>
	VectorN<T>::VectorN(const VectorN& other) { set(other); }

	template <typename T>
	VectorN<T>::VectorN(VectorN&& other) { (*this) = std::move(other); }

	template <typename T>
	void VectorN<T>::resize(size_t n, const T& val) { _elements.resize(n, val); }

	template <typename T>
	void VectorN<T>::clear() { _elements.clear(); }

	template <typename T>
	void VectorN<T>::set(const T& s) { parallelFill(begin(), end(), s); }

	template <typename T>
	template <typename U>
	void VectorN<T>::set(const std::initializer_list<U>& lst) { _elements = lst; }

	template <typename T>
	template <typename E>
	void VectorN<T>::set(const VectorExpression<T, E>& other) 
	{
		resize(other.size());
		// Parallel evaluation of the expression
		const E& expression = other();
		parallelForEachIndex([&](size_t i) { _elements[i] = expression[i]; });
	}

	template <typename T>
	void VectorN<T>::append(const T& val) { _elements.push_back(val); }

	template <typename T>
	void VectorN<T>::swap(VectorN& other) { std::swap(other._elements, _elements); }

	template <typename T>
	void VectorN<T>::setZero() { set(T(0)); }

	template <typename T>
	void VectorN<T>::normalize() { idiv(length()); }

	template <typename T>
	size_t VectorN<T>::size() const { return _elements.size(); }

	template <typename T>
	T* VectorN<T>::data() { return _elements.data(); }

	template <typename T>
	const T* const VectorN<T>::data() const { return _elements.data(); }

	template <typename T>
	typename VectorN<T>::ContainerType::iterator VectorN<T>::begin() { return _elements.begin(); }

	template <typename T>
	typename VectorN<T>::ContainerType::const_iterator VectorN<T>::begin() const { return _elements.cbegin(); }

	template <typename T>
	typename VectorN<T>::ContainerType::iterator VectorN<T>::end() { return _elements.end(); }

	template <typename T>
	typename VectorN<T>::ContainerType::const_iterator VectorN<T>::end() const { return _elements.cend(); }

	template <typename T>
	ArrayAccessor1<T> VectorN<T>::accessor() { return ArrayAccessor1<T>(size(), data()); }

	template <typename T>
	ConstArrayAccessor1<T> VectorN<T>::constAccessor() const { return ConstArrayAccessor1<T>(size(), data()); }

	template <typename T>
	T VectorN<T>::at(size_t i) const { return _elements[i]; }

	template <typename T>
	T& VectorN<T>::at(size_t i) { return _elements[i]; }

	template <typename T>
	T VectorN<T>::sum() const 
	{
		return parallelReduce(kZeroSize, size(), T(0),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result += _elements[i];
			return result; }, std::plus<T>());
	}

	template <typename T>
	T VectorN<T>::avg() const { return sum() / static_cast<T>(size()); }

	template <typename T>
	T VectorN<T>::min() const 
	{
		const T& (*_min)(const T&, const T&) = std::min<T>;
		return parallelReduce(kZeroSize, size(), std::numeric_limits<T>::max(),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result = std::min(result, _elements[i]);
			return result; }, _min);
	}

	template <typename T>
	T VectorN<T>::max() const 
	{
		const T& (*_max)(const T&, const T&) = std::max<T>;
		return parallelReduce(kZeroSize, size(), std::numeric_limits<T>::min(),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result = std::max(result, _elements[i]);
			return result; }, _max);
	}

	template <typename T>
	T VectorN<T>::absmin() const 
	{
		return parallelReduce(kZeroSize, size(), std::numeric_limits<T>::max(),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result = Engine::absmin(result, _elements[i]);
			return result; }, Engine::absmin<T>);
	}

	template <typename T>
	T VectorN<T>::absmax() const 
	{
		return parallelReduce(kZeroSize, size(), T(0),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result = Engine::absmax(result, _elements[i]);
			return result; }, Engine::absmax<T>);
	}

	template <typename T>
	size_t VectorN<T>::dominantAxis() const 
	{
		auto iter = std::max_element(begin(), end(), [](const T& a, const T& b) {
			return std::fabs(a) < std::fabs(b); });
		return iter - begin();
	}

	template <typename T>
	size_t VectorN<T>::subminantAxis() const 
	{
		auto iter = std::max_element(begin(), end(), [](const T& a, const T& b) {
			return std::fabs(a) > std::fabs(b); });
		return iter - begin();
	}

	template <typename T>
	VectorScalarDiv<T, VectorN<T>> VectorN<T>::normalized() const 
	{
		T len = length();
		return VectorScalarDiv<T, VectorN>(*this, len);
	}

	template <typename T>
	T VectorN<T>::length() const { return std::sqrt(lengthSquared()); }

	template <typename T>
	T VectorN<T>::lengthSquared() const { return dot(*this); }

	template <typename T>
	template <typename E>
	T VectorN<T>::distanceTo(const E& other) const { return std::sqrt(distanceSquaredTo(other)); }

	template <typename T>
	template <typename E>
	T VectorN<T>::distanceSquaredTo(const E& other) const 
	{
		assert(size() == other.size());
		return parallelReduce(kZeroSize, size(), T(0),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) {
				T diff = (_elements[i] - other[i]);
				result += diff * diff;
			}
			return result; }, std::plus<T>());
	}

	template <typename T>
	template <typename U>
	VectorTypeCast<U, VectorN<T>, T> VectorN<T>::castTo() const { return VectorTypeCast<U, VectorN<T>, T>(*this); }

	template <typename T>
	template <typename E>
	bool VectorN<T>::isEqual(const E& other) const 
	{
		if (size() != other.size()) 
			return false;
		for (size_t i = 0; i < size(); ++i) 
			if (at(i) != other[i]) 
				return false;
		return true;
	}

	template <typename T>
	template <typename E>
	bool VectorN<T>::isSimilar(const E& other, T epsilon) const 
	{
		if (size() != other.size()) 
			return false;
		for (size_t i = 0; i < size(); ++i) 
			if (std::fabs(at(i) - other[i]) > epsilon) 
				return false;
		return true;
	}

	template <typename T>
	template <typename E>
	VectorAdd<T, VectorN<T>, E> VectorN<T>::add(const E& v) const { return VectorAdd<T, VectorN, E>(*this, v); }

	template <typename T>
	VectorScalarAdd<T, VectorN<T>> VectorN<T>::add(const T& s) const { return VectorScalarAdd<T, VectorN>(*this, s); }

	template <typename T>
	template <typename E>
	VectorSub<T, VectorN<T>, E> VectorN<T>::sub(const E& v) const { return VectorSub<T, VectorN, E>(*this, v); }

	template <typename T>
	VectorScalarSub<T, VectorN<T>> VectorN<T>::sub(const T& s) const { return VectorScalarSub<T, VectorN>(*this, s); }

	template <typename T>
	template <typename E>
	VectorMul<T, VectorN<T>, E> VectorN<T>::mul(const E& v) const { return VectorMul<T, VectorN, E>(*this, v); }

	template <typename T>
	VectorScalarMul<T, VectorN<T>> VectorN<T>::mul(const T& s) const { return VectorScalarMul<T, VectorN>(*this, s); }

	template <typename T>
	template <typename E>
	VectorDiv<T, VectorN<T>, E> VectorN<T>::div(const E& v) const { return VectorDiv<T, VectorN, E>(*this, v); }

	template <typename T>
	VectorScalarDiv<T, VectorN<T>> VectorN<T>::div(const T& s) const { return VectorScalarDiv<T, VectorN>(*this, s); }

	template <typename T>
	template <typename E>
	T VectorN<T>::dot(const E& v) const 
	{
		assert(size() == v.size());
		return parallelReduce(kZeroSize, size(), T(0),
			[&](size_t start, size_t end, T init) {
			T result = init;
			for (size_t i = start; i < end; ++i) 
				result += _elements[i] * v[i];
			return result; }, std::plus<T>());
	}

	template <typename T>
	VectorScalarRSub<T, VectorN<T>> VectorN<T>::rsub(const T& s) const { return VectorScalarRSub<T, VectorN>(*this, s); }

	template <typename T>
	template <typename E>
	VectorSub<T, VectorN<T>, E> VectorN<T>::rsub(const E& v) const { return VectorSub<T, VectorN, E>(v, *this); }

	template <typename T>
	VectorScalarRDiv<T, VectorN<T>> VectorN<T>::rdiv(const T& s) const { return VectorScalarRDiv<T, VectorN>(*this, s); }

	template <typename T>
	template <typename E>
	VectorDiv<T, VectorN<T>, E> VectorN<T>::rdiv(const E& v) const { return VectorDiv<T, VectorN, E>(v, *this); }

	template <typename T>
	void VectorN<T>::iadd(const T& s) { set(add(s)); }

	template <typename T>
	template <typename E>
	void VectorN<T>::iadd(const E& v) { set(add(v)); }

	template <typename T>
	void VectorN<T>::isub(const T& s) { set(sub(s)); }

	template <typename T>
	template <typename E>
	void VectorN<T>::isub(const E& v) { set(sub(v)); }

	template <typename T>
	void VectorN<T>::imul(const T& s) { set(mul(s)); }

	template <typename T>
	template <typename E>
	void VectorN<T>::imul(const E& v) { set(mul(v)); }

	template <typename T>
	void VectorN<T>::idiv(const T& s) { set(div(s)); }

	template <typename T>
	template <typename E>
	void VectorN<T>::idiv(const E& v) { set(div(v)); }

	template <typename T>
	template <typename Callback>
	void VectorN<T>::forEach(Callback func) const { constAccessor().forEach(func); }

	template <typename T>
	template <typename Callback>
	void VectorN<T>::forEachIndex(Callback func) const { constAccessor().forEachIndex(func); }

	template <typename T>
	template <typename Callback>
	void VectorN<T>::parallelForEach(Callback func) { accessor().parallelForEach(func); }

	template <typename T>
	template <typename Callback>
	void VectorN<T>::parallelForEachIndex(Callback func) const { constAccessor().parallelForEachIndex(func); }

	template <typename T>
	T VectorN<T>::operator[](size_t i) const { return _elements[i]; }

	template <typename T>
	T& VectorN<T>::operator[](size_t i) { return _elements[i]; }

	template <typename T>
	template <typename U>
	VectorN<T>& VectorN<T>::operator=(const std::initializer_list<U>& lst) { set(lst); return *this; }

	template <typename T>
	template <typename E>
	VectorN<T>& VectorN<T>::operator=(const VectorExpression<T, E>& other) { set(other); return *this; }

	template <typename T>
	VectorN<T>& VectorN<T>::operator=(const VectorN& other) { set(other); return *this; }

	template <typename T>
	VectorN<T>& VectorN<T>::operator=(VectorN&& other) { _elements = std::move(other._elements); return *this; }

	template <typename T>
	VectorN<T>& VectorN<T>::operator+=(const T& s) { iadd(s); return *this; }

	template <typename T>
	template <typename E>
	VectorN<T>& VectorN<T>::operator+=(const E& v) { iadd(v); return *this; }

	template <typename T>
	VectorN<T>& VectorN<T>::operator-=(const T& s) { isub(s); return *this; }

	template <typename T>
	template <typename E>
	VectorN<T>& VectorN<T>::operator-=(const E& v) { isub(v); return *this; }

	template <typename T>
	VectorN<T>& VectorN<T>::operator*=(const T& s) { imul(s); return *this; }

	template <typename T>
	template <typename E>
	VectorN<T>& VectorN<T>::operator*=(const E& v) { imul(v); return *this; }

	template <typename T>
	VectorN<T>& VectorN<T>::operator/=(const T& s) { idiv(s); return *this; }

	template <typename T>
	template <typename E>
	VectorN<T>& VectorN<T>::operator/=(const E& v) { idiv(v); return *this; }

	template <typename T>
	template <typename E>
	bool VectorN<T>::operator==(const E& v) const { return isEqual(v); }

	template <typename T>
	template <typename E>
	bool VectorN<T>::operator!=(const E& v) const { return !isEqual(v); }

}