#pragma once

#include "Array.h"
#include "Vector.h"
#include "Matrix.h"

namespace Engine
{
	template <typename T, size_t N, typename Derived>
	class ArrayBase;

	template <typename T, size_t N>
	class Array;

	// MARK: ArrayView

	template <typename T, size_t N>
	class ArrayView final : public ArrayBase<T, N, ArrayView<T, N>>
	{
		using Base = ArrayBase<T, N, ArrayView<T, N>>;
		using Base::_size;
		using Base::setPtrAndSize;
		using Base::at;

	public:
		// CTOR
		ArrayView();

		ArrayView(T* ptr, const Vector<size_t, N>& size_);

		template <size_t M = N>
		ArrayView(typename std::enable_if_t<(M == 1), T*> ptr, size_t size_);

		ArrayView(Array<T, N>& other);

		ArrayView(const ArrayView& other);

		ArrayView(ArrayView&& other) noexcept;

		// set

		void set(Array<T, N>& other);

		void set(const ArrayView& other);

		void fill(const T& val);

		// Assignment Operators
		ArrayView& operator=(const ArrayView& other);

		ArrayView& operator=(ArrayView&& other) noexcept;
	};

	template <typename T, size_t N>
	class ArrayView<const T, N> final : public ArrayBase<const T, N, ArrayView<const T, N>> 
	{
		using Base = ArrayBase<const T, N, ArrayView<const T, N>>;
		using Base::_size;
		using Base::setPtrAndSize;

	public:
		// CTOR
		ArrayView();

		ArrayView(const T* ptr, const Vector<size_t, N>& size_);

		template <size_t M = N>
		ArrayView(typename std::enable_if_t<(M == 1), const T*> ptr, size_t size_);

		ArrayView(const Array<T, N>& other);

		ArrayView(const ArrayView<T, N>& other);

		ArrayView(const ArrayView<const T, N>& other);

		ArrayView(ArrayView<const T, N>&&) noexcept;

		// set

		void set(const Array<T, N>& other);

		void set(const ArrayView<T, N>& other);

		void set(const ArrayView<const T, N>& other);

		// Assignment Operators
		ArrayView& operator=(const ArrayView<T, N>& other);

		ArrayView& operator=(const ArrayView<const T, N>& other);

		ArrayView& operator=(ArrayView<const T, N>&& other) noexcept;
	};

	template <class T>
	using ArrayView1 = ArrayView<T, 1>;

	template <class T>
	using ArrayView2 = ArrayView<T, 2>;

	template <class T>
	using ArrayView3 = ArrayView<T, 3>;

	template <class T>
	using ArrayView4 = ArrayView<T, 4>;

	template <class T>
	using ConstArrayView1 = ArrayView<const T, 1>;

	template <class T>
	using ConstArrayView2 = ArrayView<const T, 2>;

	template <class T>
	using ConstArrayView3 = ArrayView<const T, 3>;

	template <class T>
	using ConstArrayView4 = ArrayView<const T, 4>;

	//! ---------------------------------------Definition----------------------------------------------

	// MARK: ArrayView

	template <typename T, size_t N>
	ArrayView<T, N>::ArrayView() : Base() {}

	template <typename T, size_t N>
	ArrayView<T, N>::ArrayView(T* ptr, const Vector<size_t, N>& size_)
		: ArrayView() { Base::setPtrAndSize(ptr, size_); }

	template <typename T, size_t N>
	template <size_t M>
	ArrayView<T, N>::ArrayView(typename std::enable_if_t<(M == 1), T*> ptr, size_t size_)
		: ArrayView(ptr, Vector<size_t, N>{size_}) {}

	template <typename T, size_t N>
	ArrayView<T, N>::ArrayView(Array<T, N>& other) : ArrayView() { set(other); }

	template <typename T, size_t N>
	ArrayView<T, N>::ArrayView(const ArrayView& other) { set(other); }

	template <typename T, size_t N>
	ArrayView<T, N>::ArrayView(ArrayView&& other) noexcept : ArrayView() { *this = std::move(other); }

	template <typename T, size_t N>
	void ArrayView<T, N>::set(Array<T, N>& other) { Base::setPtrAndSize(other.data(), other.size()); }

	template <typename T, size_t N>
	void ArrayView<T, N>::set(const ArrayView& other) { Base::setPtrAndSize(const_cast<T*>(other.data()), other.size()); }

	template <typename T, size_t N>
	void ArrayView<T, N>::fill(const T& val) 
	{
		forEachIndex(Vector<size_t, N>{}, _size,
			[&](auto... idx) { this->at(idx...) = val; });
	}

	template <typename T, size_t N>
	ArrayView<T, N>& ArrayView<T, N>::operator=(const ArrayView& other)
	{
		set(other);
		return *this;
	}

	template <typename T, size_t N>
	ArrayView<T, N>& ArrayView<T, N>::operator=(ArrayView&& other) noexcept 
	{
		Base::setPtrAndSize(other.data(), other.size());
		other.setPtrAndSize(nullptr, Vector<size_t, N>{});
		return *this;
	}

	// MARK: ConstArrayView

	template <typename T, size_t N>
	ArrayView<const T, N>::ArrayView() : Base() {}

	template <typename T, size_t N>
	ArrayView<const T, N>::ArrayView(const T* ptr, const Vector<size_t, N>& size_)
		: ArrayView() { Base::setPtrAndSize(ptr, size_); }

	template <typename T, size_t N>
	template <size_t M>
	ArrayView<const T, N>::ArrayView(
		typename std::enable_if_t<(M == 1), const T*> ptr, size_t size_)
		: ArrayView(ptr, Vector<size_t, N>{size_}) {}

	template <typename T, size_t N>
	ArrayView<const T, N>::ArrayView(const Array<T, N>& other) : ArrayView() { set(other); }

	template <typename T, size_t N>
	ArrayView<const T, N>::ArrayView(const ArrayView<T, N>& other) { set(other); }

	template <typename T, size_t N>
	ArrayView<const T, N>::ArrayView(const ArrayView<const T, N>& other) { set(other); }

	template <typename T, size_t N>
	ArrayView<const T, N>::ArrayView(ArrayView&& other) noexcept : ArrayView() { *this = std::move(other); }

	template <typename T, size_t N>
	void ArrayView<const T, N>::set(const Array<T, N>& other) 
	{
		Base::setPtrAndSize(other.data(), other.size());
	}

	template <typename T, size_t N>
	void ArrayView<const T, N>::set(const ArrayView<T, N>& other)
	{
		Base::setPtrAndSize(other.data(), other.size());
	}

	template <typename T, size_t N>
	void ArrayView<const T, N>::set(const ArrayView<const T, N>& other)
	{
		Base::setPtrAndSize(other.data(), other.size());
	}

	template <typename T, size_t N>
	ArrayView<const T, N>& ArrayView<const T, N>::operator=(const ArrayView<T, N>& other)
	{
		set(other);
		return *this;
	}

	template <typename T, size_t N>
	ArrayView<const T, N>& ArrayView<const T, N>::operator=(
		const ArrayView<const T, N>& other)
	{
		set(other);
		return *this;
	}

	template <typename T, size_t N>
	ArrayView<const T, N>& ArrayView<const T, N>::operator=(
		ArrayView<const T, N>&& other) noexcept
	{
		Base::setPtrAndSize(other.data(), other.size());
		other.setPtrAndSize(nullptr, Vector<size_t, N>{});
		return *this;
	}

}
