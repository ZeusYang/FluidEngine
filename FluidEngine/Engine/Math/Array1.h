#pragma once

#include <vector>
#include <fstream>
#include <utility>
#include <iostream>
#include <functional>

#include "Array.h"
#include "ArrayAccessor1.h"

namespace Engine
{
	//!
	//! \brief 1-D array class.
	//!
	//! This class represents 1-D array data structure. This class is a simple
	//! wrapper around std::vector with some additional features such as the array
	//! accessor object and parallel for-loop.
	//!
	//! \tparam T - Type to store in the array.
	//!
	template <typename T>
	class Array<T, 1> final
	{
	public:
		typedef std::vector<T> ContainerType;
		typedef typename ContainerType::iterator Iterator;
		typedef typename ContainerType::const_iterator ConstIterator;

		//! Constructs zero-sized 1-D array.
		Array();

		//! Constructs 1-D array with given \p size and fill it with \p initVal.
		//! \param size Initial size of the array.
		//! \param initVal Initial value of each array element.
		explicit Array(size_t size, const T &initVal = T());

		//!
		//! \brief Constructs 1-D array with given initializer list \p lst.
		//!
		//! This constructor will build 1-D array with given initializer list \p lst
		//! such as
		//!
		//! \code{.cpp}
		//! Array<int, 1> arr = {1, 2, 4, 9, 3};
		//! \endcode
		//!
		//! \param lst Initializer list that should be copy to the new array.
		//!
		Array(const std::initializer_list<T>& lst);

		//! Copy constructor.
		Array(const Array& other);

		//! Move constructor.
		Array(Array&& other);

		//! Sets entire array with given \p value.
		void set(const T& value);

		//! Copies given array \p other to this array.
		void set(const Array& other);

		//! Copies given initializer list \p lst to this array.
		void set(const std::initializer_list<T>& lst);

		//! Clears the array and resizes to zero.
		void clear();

		//! Resizes the array with \p size and fill the new element with \p initVal.
		void resize(size_t size, const T& initVal = T());

		//! Returns the reference to the i-th element.
		T& at(size_t i);

		//! Returns the const reference to the i-th element.
		const T& at(size_t i) const;

		//! Returns size of the array.
		size_t size() const;

		//! Returns the raw pointer to the array data.
		T* data();

		//! Returns the const raw pointer to the array data.
		const T* const data() const;

		//! Returns the begin iterator of the array.
		Iterator begin();

		//! Returns the begin const iterator of the array.
		ConstIterator begin() const;

		//! Returns the end iterator of the array.
		Iterator end();

		//! Returns the end const iterator of the array.
		ConstIterator end() const;

		//! Returns the array accessor.
		ArrayAccessor1<T> accessor();

		//! Returns the const array accessor.
		ConstArrayAccessor1<T> constAccessor() const;

		//! Swaps the content of the array with \p other array.
		void swap(Array& other);

		//! Appends single value \p newVal at the end of the array.
		void append(const T& newVal);

		//! Appends \p other array at the end of the array.
		void append(const Array& other);

		//!
		//! \brief Iterates the array and invoke given \p func for each element.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes array's element as its
		//! input. The order of execution will be 0 to N-1 where N is the size of
		//! the array. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! Array<int, 1> array(10, 4);
		//! array.forEach([](int elem) {
		//!     printf("%d\n", elem);
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void forEach(Callback func) const;

		//!
		//! \brief Iterates the array and invoke given \p func for each index.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes one parameter which is the
		//! index of the array. The order of execution will be 0 to N-1 where N is
		//! the size of the array. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! Array<int, 1> array(10, 4);
		//! array.forEachIndex([&](size_t i) {
		//!     array[i] = 4.f * i + 1.5f;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void forEachIndex(Callback func) const;

		//!
		//! \brief Iterates the array and invoke given \p func for each element in
		//!     parallel using multi-threading.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func in parallel using multi-threading. The callback
		//! function takes array's element as its input. The order of execution will
		//! be non-deterministic since it runs in parallel.
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! Array<int, 1> array(1000, 4);
		//! array.parallelForEach([](int& elem) {
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
		//! \brief Iterates the array and invoke given \p func for each index in
		//!     parallel using multi-threading.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func in parallel using multi-threading. The callback
		//! function takes one parameter which is the index of the array. The order
		//! of execution will be non-deterministic since it runs in parallel.
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! Array<int, 1> array(1000, 4);
		//! array.parallelForEachIndex([](size_t i) {
		//!     array[i] *= 2;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void parallelForEachIndex(Callback func) const;

		//! Returns the reference to i-th element.
		T& operator[](size_t i);

		//! Returns the const reference to i-th element.
		const T& operator[](size_t i) const;

		//! Sets entire array with given \p value.
		Array& operator=(const T& other);

		//! Copies given array \p other to this array.
		Array& operator=(const Array& other);

		//! Move assignment.
		Array& operator=(Array&& other);

		//! Copies given initializer list \p lst to this array.
		Array& operator=(const std::initializer_list<T>& lst);

	private:
		ContainerType _data;
	};

	//! Type alias for 1-D array.
	template <typename T>
	using Array1 = Array<T, 1>;

	template <typename T>
	Array<T, 1>::Array() {}

	template <typename T>
	Array<T, 1>::Array(size_t size, const T& initVal)  { resize(size, initVal); }

	template <typename T>
	Array<T, 1>::Array(const std::initializer_list<T>& lst)  { set(lst); }

	template <typename T>
	Array<T, 1>::Array(const Array& other) { set(other); }

	template <typename T>
	Array<T, 1>::Array(Array&& other) { (*this) = std::move(other); }

	template <typename T>
	void Array<T, 1>::set(const T& value) 
	{
		for (auto& v : _data) 
			v = value;
	}

	template <typename T>
	void Array<T, 1>::set(const Array& other) 
	{
		_data.resize(other._data.size());
		std::copy(other._data.begin(), other._data.end(), _data.begin());
	}

	template <typename T>
	void Array<T, 1>::set(const std::initializer_list<T>& lst) 
	{
		size_t size = lst.size();
		resize(size);
		auto colIter = lst.begin();
		for (size_t i = 0; i < size; ++i) {
			(*this)[i] = *colIter;
			++colIter;
		}
	}

	template <typename T>
	void Array<T, 1>::clear() { _data.clear(); }

	template <typename T>
	void Array<T, 1>::resize(size_t size, const T& initVal) { _data.resize(size, initVal); }

	template <typename T>
	T& Array<T, 1>::at(size_t i) 
	{
		assert(i < size());
		return _data[i];
	}

	template <typename T>
	const T& Array<T, 1>::at(size_t i) const 
	{
		assert(i < size());
		return _data[i];
	}

	template <typename T>
	size_t Array<T, 1>::size() const  { return _data.size(); }

	template <typename T>
	T* Array<T, 1>::data() { return _data.data(); }

	template <typename T>
	const T* const Array<T, 1>::data() const { return _data.data(); }

	template <typename T>
	typename Array<T, 1>::ContainerType::iterator Array<T, 1>::begin() { return _data.begin(); }

	template <typename T>
	typename Array<T, 1>::ContainerType::const_iterator Array<T, 1>::begin() const { return _data.cbegin(); }

	template <typename T>
	typename Array<T, 1>::ContainerType::iterator Array<T, 1>::end() { return _data.end(); }

	template <typename T>
	typename Array<T, 1>::ContainerType::const_iterator Array<T, 1>::end() const { return _data.cend(); }

	template <typename T>
	ArrayAccessor1<T> Array<T, 1>::accessor() { return ArrayAccessor1<T>(size(), data()); }

	template <typename T>
	ConstArrayAccessor1<T> Array<T, 1>::constAccessor() const { return ConstArrayAccessor1<T>(size(), data()); }

	template <typename T>
	void Array<T, 1>::swap(Array& other) { std::swap(other._data, _data); }

	template <typename T>
	void Array<T, 1>::append(const T& newVal) { _data.push_back(newVal); }

	template <typename T>
	void Array<T, 1>::append(const Array& other) { _data.insert(_data.end(), other._data.begin(), other._data.end()); }

	template <typename T>
	template <typename Callback>
	void Array<T, 1>::forEach(Callback func) const { constAccessor().forEach(func); }

	template <typename T>
	template <typename Callback>
	void Array<T, 1>::forEachIndex(Callback func) const { constAccessor().forEachIndex(func); }

	template <typename T>
	template <typename Callback>
	void Array<T, 1>::parallelForEach(Callback func) { accessor().parallelForEach(func); }

	template <typename T>
	template <typename Callback>
	void Array<T, 1>::parallelForEachIndex(Callback func) const { constAccessor().parallelForEachIndex(func); }

	template <typename T>
	T& Array<T, 1>::operator[](size_t i) { return _data[i]; }

	template <typename T>
	const T& Array<T, 1>::operator[](size_t i) const { return _data[i]; }

	template <typename T>
	Array<T, 1>& Array<T, 1>::operator=(const T& value) 
	{
		set(value);
		return *this;
	}

	template <typename T>
	Array<T, 1>& Array<T, 1>::operator=(const Array& other) 
	{
		set(other);
		return *this;
	}

	template <typename T>
	Array<T, 1>& Array<T, 1>::operator=(Array&& other) 
	{
		_data = std::move(other._data);
		return *this;
	}

	template <typename T>
	Array<T, 1>& Array<T, 1>::operator=(const std::initializer_list<T>& lst) 
	{
		set(lst);
		return *this;
	}

}