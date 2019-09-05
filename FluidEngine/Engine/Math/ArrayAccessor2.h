#pragma once

#include <utility>

#include "Size2.h"
#include "Point2.h"
#include "../Utils/Parallel.h"
#include "ArrayAccessor.h"

namespace Engine
{
	//!
	//! \brief 2-D array accessor class.
	//!
	//! This class represents 2-D array accessor. Array accessor provides array-like
	//! data read/write functions, but does not handle memory management. Thus, it
	//! is more like a random access iterator, but with multi-dimension support.
	//! Similar to Array<T, 2>, this class interprets a linear array as a 2-D array
	//! using i-major indexing.
	//!
	//! \see Array<T, 2>
	//!
	//! \tparam T - Array value type.
	//!
	template <typename T>
	class ArrayAccessor<T, 2> final
	{
	public:
		//! Constructs empty 2-D array accessor.
		ArrayAccessor();

		//! Constructs an array accessor that wraps given array.
		//! \param size Size of the 2-D array.
		//! \param data Raw array pointer.
		ArrayAccessor(const Size2& size, T* const data);

		//! Constructs an array accessor that wraps given array.
		//! \param width Width of the 2-D array.
		//! \param height Height of the 2-D array.
		//! \param data Raw array pointer.
		ArrayAccessor(size_t width, size_t height, T* const data);

		//! Copy constructor.
		ArrayAccessor(const ArrayAccessor& other);

		//! Replaces the content with given \p other array accessor.
		void set(const ArrayAccessor& other);

		//! Resets the array.
		void reset(const Size2& size, T* const data);

		//! Resets the array.
		void reset(size_t width, size_t height, T* const data);

		//! Returns the reference to the i-th element.
		T& at(size_t i);

		//! Returns the const reference to the i-th element.
		const T& at(size_t i) const;

		//! Returns the reference to the element at (pt.x, pt.y).
		T& at(const Point2UI& pt);

		//! Returns the const reference to the element at (pt.x, pt.y).
		const T& at(const Point2UI& pt) const;

		//! Returns the reference to the element at (i, j).
		T& at(size_t i, size_t j);

		//! Returns the const reference to the element at (i, j).
		const T& at(size_t i, size_t j) const;

		//! Returns the begin iterator of the array.
		T* const begin() const;

		//! Returns the end iterator of the array.
		T* const end() const;

		//! Returns the begin iterator of the array.
		T* begin();

		//! Returns the end iterator of the array.
		T* end();

		//! Returns the size of the array.
		Size2 size() const;

		//! Returns the width of the array.
		size_t width() const;

		//! Returns the height of the array.
		size_t height() const;

		//! Returns the raw pointer to the array data.
		T* const data() const;

		//! Swaps the content of with \p other array accessor.
		void swap(ArrayAccessor& other);

		//!
		//! \brief Iterates the array and invoke given \p func for each index.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes array's element as its
		//! input. The order of execution will be the same as the nested for-loop
		//! below:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! for (size_t j = 0; j < acc.height(); ++j) {
		//!     for (size_t i = 0; i < acc.width(); ++i) {
		//!         func(acc(i, j));
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.forEach([](int elem) {
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
		//! function \p func. The callback function takes two parameters which are
		//! the (i, j) indices of the array. The order of execution will be the same
		//! as the nested for-loop below:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! for (size_t j = 0; j < acc.height(); ++j) {
		//!     for (size_t i = 0; i < acc.width(); ++i) {
		//!         func(i, j);
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.forEachIndex([&](size_t i, size_t j) {
		//!     acc(i, j) = 4.f * i + 7.f * j + 1.5f;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void forEachIndex(Callback func) const;

		//!
		//! \brief Iterates the array and invoke given \p func for each index in
		//!     parallel.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes array's element as its
		//! input. The order of execution will be non-deterministic since it runs in
		//! parallel. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.parallelForEach([](int& elem) {
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
		//! function takes two parameters which are the (i, j) indices of the array.
		//! The order of execution will be non-deterministic since it runs in
		//! parallel. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.parallelForEachIndex([&](size_t i, size_t j) {
		//!     acc(i, j) *= 2;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void parallelForEachIndex(Callback func) const;

		//! Returns the linear index of the given 2-D coordinate (pt.x, pt.y).
		size_t index(const Point2UI& pt) const;

		//! Returns the linear index of the given 2-D coordinate (i, j).
		size_t index(size_t i, size_t j) const;

		//! Returns the reference to the i-th element.
		T& operator[](size_t i);

		//! Returns the const reference to the i-th element.
		const T& operator[](size_t i) const;

		//! Returns the reference to the element at (pt.x, pt.y).
		T& operator()(const Point2UI& pt);

		//! Returns the const reference to the element at (pt.x, pt.y).
		const T& operator()(const Point2UI& pt) const;

		//! Returns the reference to the element at (i, j).
		T& operator()(size_t i, size_t j);

		//! Returns the const reference to the element at (i, j).
		const T& operator()(size_t i, size_t j) const;

		//! Copies given array accessor \p other.
		ArrayAccessor& operator=(const ArrayAccessor& other);

		//! Casts type to ConstArrayAccessor.
		operator ConstArrayAccessor<T, 2>() const;

	private:
		Size2 _size;
		T *_data;
	};

	//! Type alias for 2-D array accessor.
	template <typename T> using ArrayAccessor2 = ArrayAccessor<T, 2>;

	//!
	//! \brief 2-D read-only array accessor class.
	//!
	//! This class represents 2-D read-only array accessor. Array accessor provides
	//! array-like data read/write functions, but does not handle memory management.
	//! Thus, it is more like a random access iterator, but with multi-dimension
	//! support. Similar to Array2<T, 2>, this class interprets a linear array as a
	//! 2-D array using i-major indexing.
	//!
	//! \see Array2<T, 2>
	//!
	template <typename T>
	class ConstArrayAccessor<T, 2>
	{
	public:
		//! Constructs empty 2-D read-only array accessor.
		ConstArrayAccessor();

		//! Constructs a read-only array accessor that wraps given array.
		//! \param size Size of the 2-D array.
		//! \param data Raw array pointer.
		ConstArrayAccessor(const Size2& size, const T* const data);

		//! Constructs an array accessor that wraps given array.
		//! \param width Width of the 2-D array.
		//! \param height Height of the 2-D array.
		//! \param data Raw array pointer.
		ConstArrayAccessor(size_t width, size_t height, const T* const data);

		//! Constructs a read-only array accessor from read/write accessor.
		explicit ConstArrayAccessor(const ArrayAccessor<T, 2>& other);

		//! Copy constructor.
		ConstArrayAccessor(const ConstArrayAccessor& other);

		//! Returns the reference to the i-th element.
		const T& at(size_t i) const;

		//! Returns the const reference to the element at (pt.x, pt.y).
		const T& at(const Point2UI& pt) const;

		//! Returns the const reference to the element at (i, j).
		const T& at(size_t i, size_t j) const;

		//! Returns the begin iterator of the array.
		const T* const begin() const;

		//! Returns the end iterator of the array.
		const T* const end() const;

		//! Returns the size of the array.
		Size2 size() const;

		//! Returns the width of the array.
		size_t width() const;

		//! Returns the height of the array.
		size_t height() const;

		//! Returns the raw pointer to the array data.
		const T* const data() const;

		//!
		//! \brief Iterates the array and invoke given \p func for each index.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func. The callback function takes array's element as its
		//! input. The order of execution will be the same as the nested for-loop
		//! below:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! for (size_t j = 0; j < acc.height(); ++j) {
		//!     for (size_t i = 0; i < acc.width(); ++i) {
		//!         func(acc(i, j));
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.forEach([](int elem) {
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
		//! function \p func. The callback function takes two parameters which are
		//! the (i, j) indices of the array. The order of execution will be the same
		//! as the nested for-loop below:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! for (size_t j = 0; j < acc.height(); ++j) {
		//!     for (size_t i = 0; i < acc.width(); ++i) {
		//!         func(i, j);
		//!     }
		//! }
		//! \endcode
		//!
		//! Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.forEachIndex([&](size_t i, size_t j) {
		//!     acc(i, j) = 4.f * i + 7.f * j + 1.5f;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void forEachIndex(Callback func) const;

		//!
		//! \brief Iterates the array and invoke given \p func for each index in
		//!     parallel using multi-threading.
		//!
		//! This function iterates the array elements and invoke the callback
		//! function \p func in parallel using multi-threading. The callback
		//! function takes two parameters which are the (i, j) indices of the array.
		//! The order of execution will be non-deterministic since it runs in
		//! parallel. Below is the sample usage:
		//!
		//! \code{.cpp}
		//! int data = {1, 2, 3, 4, 5, 6};
		//! ConstArrayAccessor<int, 2> acc(2, 3, data);
		//! acc.parallelForEachIndex([&](size_t i, size_t j) {
		//!     acc(i, j) *= 2;
		//! });
		//! \endcode
		//!
		template <typename Callback>
		void parallelForEachIndex(Callback func) const;

		//! Returns the linear index of the given 2-D coordinate (pt.x, pt.y).
		size_t index(const Point2UI& pt) const;

		//! Returns the linear index of the given 2-D coordinate (i, j).
		size_t index(size_t i, size_t j) const;

		//! Returns the const reference to the i-th element.
		const T& operator[](size_t i) const;

		//! Returns the const reference to the element at (pt.x, pt.y).
		const T& operator()(const Point2UI& pt) const;

		//! Returns the const reference to the element at (i, j).
		const T& operator()(size_t i, size_t j) const;

	private:
		Size2 _size;
		const T* _data;
	};

	//! Type alias for 2-D const array accessor.
	template <typename T> using ConstArrayAccessor2 = ConstArrayAccessor<T, 2>;

	//! -------------------ArrayAccessor Definition-----------------------------------
	template <typename T>
	ArrayAccessor<T, 2>::ArrayAccessor() : _data(nullptr) { }

	template <typename T>
	ArrayAccessor<T, 2>::ArrayAccessor(const Size2& size, T* const data) { reset(size, data); }

	template <typename T>
	ArrayAccessor<T, 2>::ArrayAccessor(size_t width, size_t height, T* const data) { reset(width, height, data); }

	template <typename T>
	ArrayAccessor<T, 2>::ArrayAccessor(const ArrayAccessor& other) { set(other); }

	template <typename T>
	void ArrayAccessor<T, 2>::set(const ArrayAccessor& other) { reset(other._size, other._data); }

	template <typename T>
	void ArrayAccessor<T, 2>::reset(const Size2& size, T* const data) { _size = size; _data = data; }

	template <typename T>
	void ArrayAccessor<T, 2>::reset(size_t width, size_t height, T* const data) { reset(Size2(width, height), data); }

	template <typename T>
	T& ArrayAccessor<T, 2>::at(size_t i) { assert(i < _size.x*_size.y); return _data[i]; }

	template <typename T>
	const T& ArrayAccessor<T, 2>::at(size_t i) const { assert(i < _size.x*_size.y); return _data[i]; }

	template <typename T>
	T& ArrayAccessor<T, 2>::at(const Point2UI& pt) { return at(pt.x, pt.y); }

	template <typename T>
	const T& ArrayAccessor<T, 2>::at(const Point2UI& pt) const { return at(pt.x, pt.y); }

	template <typename T>
	T& ArrayAccessor<T, 2>::at(size_t i, size_t j) 
	{
		assert(i < _size.x && j < _size.y);
		return _data[i + _size.x * j];
	}

	template <typename T>
	const T& ArrayAccessor<T, 2>::at(size_t i, size_t j) const 
	{
		assert(i < _size.x && j < _size.y);
		return _data[i + _size.x * j];
	}

	template <typename T>
	T* const ArrayAccessor<T, 2>::begin() const { return _data; }

	template <typename T>
	T* const ArrayAccessor<T, 2>::end() const { return _data + _size.x * _size.y; }

	template <typename T>
	T* ArrayAccessor<T, 2>::begin() { return _data; }

	template <typename T>
	T* ArrayAccessor<T, 2>::end() { return _data + _size.x * _size.y; }

	template <typename T>
	Size2 ArrayAccessor<T, 2>::size() const { return _size; }

	template <typename T>
	size_t ArrayAccessor<T, 2>::width() const { return _size.x; }

	template <typename T>
	size_t ArrayAccessor<T, 2>::height() const { return _size.y; }

	template <typename T>
	T* const ArrayAccessor<T, 2>::data() const { return _data; }

	template <typename T>
	void ArrayAccessor<T, 2>::swap(ArrayAccessor& other) { std::swap(other._data, _data); std::swap(other._size, _size); }

	template <typename T>
	template <typename Callback>
	void ArrayAccessor<T, 2>::forEach(Callback func) const 
	{
		for (size_t j = 0; j < _size.y; ++j) 
			for (size_t i = 0; i < _size.x; ++i) 
				func(at(i, j));
	}

	template <typename T>
	template <typename Callback>
	void ArrayAccessor<T, 2>::forEachIndex(Callback func) const 
	{
		for (size_t j = 0; j < _size.y; ++j) 
			for (size_t i = 0; i < _size.x; ++i) 
				func(i, j);
	}

	template <typename T>
	template <typename Callback>
	void ArrayAccessor<T, 2>::parallelForEach(Callback func) 
	{
		parallelFor(kZeroSize, _size.x, kZeroSize, _size.y,
			[&](size_t i, size_t j) {
			func(at(i, j)); });
	}

	template <typename T>
	template <typename Callback>
	void ArrayAccessor<T, 2>::parallelForEachIndex(Callback func) const 
	{
		parallelFor(kZeroSize, _size.x, kZeroSize, _size.y, func);
	}

	template <typename T>
	size_t ArrayAccessor<T, 2>::index(const Point2UI& pt) const 
	{
		assert(pt.x < _size.x && pt.y < _size.y);
		return pt.x + _size.x * pt.y;
	}

	template <typename T>
	size_t ArrayAccessor<T, 2>::index(size_t i, size_t j) const 
	{
		assert(i < _size.x && j < _size.y);
		return i + _size.x * j;
	}

	template <typename T>
	T& ArrayAccessor<T, 2>::operator[](size_t i) { return _data[i]; }

	template <typename T>
	const T& ArrayAccessor<T, 2>::operator[](size_t i) const { return _data[i]; }

	template <typename T>
	T& ArrayAccessor<T, 2>::operator()(const Point2UI &pt) 
	{
		assert(pt.x < _size.x && pt.y < _size.y);
		return _data[pt.x + _size.x * pt.y];
	}

	template <typename T>
	const T& ArrayAccessor<T, 2>::operator()(const Point2UI &pt) const
	{
		assert(pt.x < _size.x && pt.y < _size.y);
		return _data[pt.x + _size.x * pt.y];
	}

	template <typename T>
	T& ArrayAccessor<T, 2>::operator()(size_t i, size_t j) 
	{
		assert(i < _size.x && j < _size.y);
		return _data[i + _size.x * j];
	}

	template <typename T>
	const T& ArrayAccessor<T, 2>::operator()(size_t i, size_t j) const
	{
		assert(i < _size.x && j < _size.y);
		return _data[i + _size.x * j];
	}

	template <typename T>
	ArrayAccessor<T, 2>& ArrayAccessor<T, 2>::operator=(const ArrayAccessor& other) { set(other); return *this; }

	template <typename T>
	ArrayAccessor<T, 2>::operator ConstArrayAccessor<T, 2>() const {
		return ConstArrayAccessor<T, 2>(*this);
	}

	//! -------------------ConstArrayAccessor Definition-----------------------------------
	template <typename T>
	ConstArrayAccessor<T, 2>::ConstArrayAccessor() : _data(nullptr) { }

	template <typename T>
	ConstArrayAccessor<T, 2>::ConstArrayAccessor(const Size2& size, const T* const data) { _size = size; _data = data; }

	template <typename T>
	ConstArrayAccessor<T, 2>::ConstArrayAccessor(size_t width, size_t height, const T* const data) 
	{
		_size = Size2(width, height);
		_data = data;
	}

	template <typename T>
	ConstArrayAccessor<T, 2>::ConstArrayAccessor(const ArrayAccessor<T, 2>& other) 
	{
		_size = other.size();
		_data = other.data();
	}

	template <typename T>
	ConstArrayAccessor<T, 2>::ConstArrayAccessor(const ConstArrayAccessor& other) 
	{
		_size = other._size;
		_data = other._data;
	}

	template <typename T>
	const T& ConstArrayAccessor<T, 2>::at(size_t i) const { assert(i < _size.x*_size.y); return _data[i]; }

	template <typename T>
	const T& ConstArrayAccessor<T, 2>::at(const Point2UI& pt) const { return at(pt.x, pt.y); }

	template <typename T>
	const T& ConstArrayAccessor<T, 2>::at(size_t i, size_t j) const { assert(i < _size.x && j < _size.y); return _data[i + _size.x * j]; }

	template <typename T>
	const T* const ConstArrayAccessor<T, 2>::begin() const { return _data; }

	template <typename T>
	const T* const ConstArrayAccessor<T, 2>::end() const { return _data + _size.x * _size.y; }

	template <typename T>
	Size2 ConstArrayAccessor<T, 2>::size() const { return _size; }

	template <typename T>
	size_t ConstArrayAccessor<T, 2>::width() const { return _size.x; }

	template <typename T>
	size_t ConstArrayAccessor<T, 2>::height() const { return _size.y; }

	template <typename T>
	const T* const ConstArrayAccessor<T, 2>::data() const { return _data; }

	template <typename T>
	template <typename Callback>
	void ConstArrayAccessor<T, 2>::forEach(Callback func) const 
	{
		for (size_t j = 0; j < _size.y; ++j) 
			for (size_t i = 0; i < _size.x; ++i) 
				func(at(i, j));
	}

	template <typename T>
	template <typename Callback>
	void ConstArrayAccessor<T, 2>::forEachIndex(Callback func) const 
	{
		for (size_t j = 0; j < _size.y; ++j) 
			for (size_t i = 0; i < _size.x; ++i) 
				func(i, j);
	}

	template <typename T>
	template <typename Callback>
	void ConstArrayAccessor<T, 2>::parallelForEachIndex(Callback func) const 
	{
		parallelFor(kZeroSize, _size.x, kZeroSize, _size.y, func);
	}

	template <typename T>
	size_t ConstArrayAccessor<T, 2>::index(const Point2UI& pt) const 
	{
		assert(pt.x < _size.x && pt.y < _size.y);
		return pt.x + _size.x * pt.y;
	}

	template <typename T>
	size_t ConstArrayAccessor<T, 2>::index(size_t i, size_t j) const 
	{
		assert(i < _size.x && j < _size.y);
		return i + _size.x * j;
	}

	template <typename T>
	const T& ConstArrayAccessor<T, 2>::operator[](size_t i) const { return _data[i]; }

	template <typename T>
	const T& ConstArrayAccessor<T, 2>::operator()(const Point2UI &pt) const 
	{
		assert(pt.x < _size.x && pt.y < _size.y);
		return _data[pt.x + _size.x * pt.y];
	}

	template <typename T>
	const T& ConstArrayAccessor<T, 2>::operator()(size_t i, size_t j) const 
	{
		assert(i < _size.x && j < _size.y);
		return _data[i + _size.x * j];
	}

}