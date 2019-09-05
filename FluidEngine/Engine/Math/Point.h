#pragma once

#include <array>
#include <assert.h>
#include <type_traits>

namespace Engine
{
	//!
	//! \brief Generic N-D point class.
	//!
	//! \tparam T - Number type.
	//! \tparam N - Dimension.
	//!
	template <typename T, size_t N>
	class Point final
	{
	public:
		static_assert(N > 0, "Size of static-sized point should be greater than zero.");
		static_assert(std::is_arithmetic<T>::value, "Point only can be instantiated with arithmetic types");

		//! Constructs a point with zeros.
		Point();

		//! Constructs point instance with parameters.
		template <typename... Params>
		explicit Point(Params... params);

		//! Constructs point instance with initiazer list.
		template <typename U>
		explicit Point(const std::initializer_list<U>& lst);

		//! Copy constructor.
		Point(const Point& other);

		//! Set point instance with initializer list.
		template <typename U>
		void set(const std::initializer_list<U>& lst);

		//! Set point instance with other point.
		void set(const Point& other);

		//! Set point instance with initializer list.
		template <typename U>
		Point& operator=(const std::initializer_list<U>& lst);

		//! Set point instance with other point.
		Point& operator=(const Point& other);

		//! Returns the reference to the \p i -th element.
		T& operator[](size_t);

		//! Returns the const reference to the \p i -th element.
		const T& operator[](size_t i) const;

	private:
		std::array<T, N> _elements;

		template <typename... Params>
		void setAt(size_t i, T v, Params... params);

		void setAt(size_t i, T v);
	};

	template <typename T, size_t N>
	Point<T, N>::Point() 
	{
		for (auto& elem : _elements) 
			elem = static_cast<T>(0);
	}

	template <typename T, size_t N>
	template <typename... Params>
	Point<T, N>::Point(Params... params) 
	{
		static_assert(sizeof...(params) == N, "Invalid number of parameters.");
		setAt(0, params...);
	}

	template <typename T, size_t N>
	template <typename U>
	Point<T, N>::Point(const std::initializer_list<U>& lst) 
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
	Point<T, N>::Point(const Point& other) :
		_elements(other._elements) {}

	template <typename T, size_t N>
	template <typename U>
	void Point<T, N>::set(const std::initializer_list<U>& lst) 
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
	void Point<T, N>::set(const Point& other) { _elements = other._elements; }

	template <typename T, size_t N>
	template <typename U>
	Point<T, N>& Point<T, N>::operator=(const std::initializer_list<U>& lst) 
	{
		set(lst);
		return *this;
	}

	template <typename T, size_t N>
	Point<T, N>& Point<T, N>::operator=(const Point& other) 
	{
		set(other);
		return *this;
	}

	template <typename T, size_t N>
	const T& Point<T, N>::operator[](size_t i) const { return _elements[i]; }

	template <typename T, size_t N>
	T& Point<T, N>::operator[](size_t i) { return _elements[i]; }

	template <typename T, size_t N>
	template <typename... Params>
	void Point<T, N>::setAt(size_t i, T v, Params... params)
	{
		_elements[i] = v;
		setAt(i + 1, params...);
	}

	template <typename T, size_t N>
	void Point<T, N>::setAt(size_t i, T v) { _elements[i] = v; }

}