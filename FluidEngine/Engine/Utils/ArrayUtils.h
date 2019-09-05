#pragma once

#include <iostream>

#include "Parallel.h"
#include "../Math/Array1.h"
#include "../Math/Array2.h"
#include "../Math/Array3.h"
#include "../Math/Vector.h"
#include "../Math/ArrayAccessor2.h"
#include "../Math/ArrayAccessor3.h"

namespace Engine
{
	//!
	//! \brief Assigns \p value to 1-D array \p output with \p size.
	//!
	//! This function assigns \p value to 1-D array \p output with \p size. The
	//! output array must support random access operator [].
	//!
	template <typename ArrayType, typename T>
	void setRange1(size_t size, const T& value, ArrayType* output);

	//!
	//! \brief Assigns \p value to 1-D array \p output from \p begin to \p end.
	//!
	//! This function assigns \p value to 1-D array \p output from \p begin to \p
	//! end. The output array must support random access operator [].
	//!
	template <typename ArrayType, typename T>
	void setRange1(size_t begin, size_t end, const T& value, ArrayType* output);

	//!
	//! \brief Copies \p input array to \p output array with \p size.
	//!
	//! This function copies \p input array to \p output array with \p size. The
	//! input and output array must support random access operator [].
	//!
	template <typename ArrayType1, typename ArrayType2>
	void copyRange1(const ArrayType1& input, size_t size, ArrayType2* output);

	//!
	//! \brief Copies \p input array to \p output array from \p begin to \p end.
	//!
	//! This function copies \p input array to \p output array from \p begin to
	//! \p end. The input and output array must support random access operator [].
	//!
	template <typename ArrayType1, typename ArrayType2>
	void copyRange1(const ArrayType1& input, size_t begin, size_t end, ArrayType2* output);

	//!
	//! \brief Copies 2-D \p input array to \p output array with \p sizeX and
	//! \p sizeY.
	//!
	//! This function copies 2-D \p input array to \p output array with \p sizeX and
	//! \p sizeY. The input and output array must support 2-D random access operator
	//! (i, j).
	//!
	template <typename ArrayType1, typename ArrayType2>
	void copyRange2(const ArrayType1& input, size_t sizeX, size_t sizeY, ArrayType2* output);

	//!
	//! \brief Copies 2-D \p input array to \p output array from
	//! (\p beginX, \p beginY) to (\p endX, \p endY).
	//!
	//! This function copies 2-D \p input array to \p output array from
	//! (\p beginX, \p beginY) to (\p endX, \p endY). The input and output array
	//! must support 2-D random access operator (i, j).
	//!
	template <typename ArrayType1, typename ArrayType2>
	void copyRange2(const ArrayType1& input, size_t beginX, size_t endX, size_t beginY, size_t endY, ArrayType2* output);

	//!
	//! \brief Copies 3-D \p input array to \p output array with \p sizeX and
	//! \p sizeY.
	//!
	//! This function copies 3-D \p input array to \p output array with \p sizeX and
	//! \p sizeY. The input and output array must support 3-D random access operator
	//! (i, j, k).
	//!
	template <typename ArrayType1, typename ArrayType2>
	void copyRange3(const ArrayType1& input, size_t sizeX, size_t sizeY, size_t sizeZ, ArrayType2* output);

	//!
	//! \brief Copies 3-D \p input array to \p output array from
	//! (\p beginX, \p beginY, \p beginZ) to (\p endX, \p endY, \p endZ).
	//!
	//! This function copies 3-D \p input array to \p output array from
	//! (\p beginX, \p beginY, \p beginZ) to (\p endX, \p endY, \p endZ). The input
	//! and output array must support 3-D random access operator (i, j, k).
	//!
	template <typename ArrayType1, typename ArrayType2>
	void copyRange3(const ArrayType1& input, size_t beginX, size_t endX, size_t beginY, size_t endY,
		size_t beginZ, size_t endZ, ArrayType2* output);

	//!
	//! \brief Extrapolates 2-D input data from 'valid' (1) to 'invalid' (0) region.
	//!
	//! This function extrapolates 2-D input data from 'valid' (1) to 'invalid' (0)
	//! region. It iterates multiple times to propagate the 'valid' values to nearby
	//! 'invalid' region. The maximum distance of the propagation is equal to
	//! numberOfIterations. The input parameters 'valid' and 'data' should be
	//! collocated.
	//!
	//! \param input - data to extrapolate
	//! \param valid - set 1 if valid, else 0.
	//! \param numberOfIterations - number of iterations for propagation
	//! \param output - extrapolated output
	//!
	template <typename T>
	void extrapolateToRegion(const ConstArrayAccessor2<T>& input, const ConstArrayAccessor2<char>& valid,
		unsigned int numberOfIterations, ArrayAccessor2<T> output);

	//!
	//! \brief Extrapolates 3-D input data from 'valid' (1) to 'invalid' (0) region.
	//!
	//! This function extrapolates 3-D input data from 'valid' (1) to 'invalid' (0)
	//! region. It iterates multiple times to propagate the 'valid' values to nearby
	//! 'invalid' region. The maximum distance of the propagation is equal to
	//! numberOfIterations. The input parameters 'valid' and 'data' should be
	//! collocated.
	//!
	//! \param input - data to extrapolate
	//! \param valid - set 1 if valid, else 0.
	//! \param numberOfIterations - number of iterations for propagation
	//! \param output - extrapolated output
	//!
	template <typename T>
	void extrapolateToRegion(const ConstArrayAccessor3<T>& input, const ConstArrayAccessor3<char>& valid,
		unsigned int numberOfIterations, ArrayAccessor3<T> output);

	//!
	//! \brief Converts 2-D array to Comma Separated Value (CSV) stream.
	//!
	//! \param data - data to convert
	//! \param strm - stream object to write CSV
	//!
	template <typename ArrayType>
	void convertToCsv(const ArrayType& data, std::ostream* strm);

	//! ------------------------------------------Definition--------------------------------------------

	template <typename ArrayType, typename T>
	void setRange1(size_t size, const T& value, ArrayType* output) { setRange1(kZeroSize, size, value, output); }

	template <typename ArrayType, typename T>
	void setRange1(size_t begin, size_t end, const T& value, ArrayType* output) 
	{
		parallelFor(begin, end,
			[&](size_t i) {
			(*output)[i] = value; });
	}

	template <typename ArrayType1, typename ArrayType2>
	void copyRange1(const ArrayType1& input, size_t size, ArrayType2* output) { copyRange1(input, 0, size, output); }

	template <typename ArrayType1, typename ArrayType2>
	void copyRange1(const ArrayType1& input, size_t begin, size_t end, ArrayType2* output) 
	{
		parallelFor(begin, end,
			[&input, &output](size_t i) {
			(*output)[i] = input[i];});
	}

	template <typename ArrayType1, typename ArrayType2>
	void copyRange2(const ArrayType1& input, size_t sizeX, size_t sizeY, ArrayType2* output)
	{
		copyRange2(input, kZeroSize, sizeX, kZeroSize, sizeY, output);
	}

	template <typename ArrayType1, typename ArrayType2>
	void copyRange2(const ArrayType1& input, size_t beginX, size_t endX, size_t beginY, size_t endY, ArrayType2* output)
	{
		parallelFor(beginX, endX, beginY, endY,
			[&input, &output](size_t i, size_t j) {
			(*output)(i, j) = input(i, j); });
	}

	template <typename ArrayType1, typename ArrayType2>
	void copyRange3(const ArrayType1& input, size_t sizeX, size_t sizeY, size_t sizeZ, ArrayType2* output) 
	{
		copyRange3(input, kZeroSize, sizeX, kZeroSize, sizeY, kZeroSize, sizeZ, output);
	}

	template <typename ArrayType1, typename ArrayType2>
	void copyRange3(const ArrayType1& input, size_t beginX, size_t endX, size_t beginY, size_t endY,
		size_t beginZ, size_t endZ, ArrayType2* output) 
	{
		parallelFor(beginX, endX, beginY, endY, beginZ, endZ,
			[&input, &output](size_t i, size_t j, size_t k) {
			(*output)(i, j, k) = input(i, j, k);
		});
	}


	template <typename T>
	void extrapolateToRegion(
		const ConstArrayAccessor2<T>& input,
		const ConstArrayAccessor2<char>& valid,
		unsigned int numberOfIterations,
		ArrayAccessor2<T> output)
	{
		const Size2 size = input.size();

		assert(size == valid.size());
		assert(size == output.size());

		Array2<char> valid0(size);
		Array2<char> valid1(size);

		valid0.parallelForEachIndex([&](size_t i, size_t j) {
			valid0(i, j) = valid(i, j);
			output(i, j) = input(i, j);
		});

		for (unsigned int iter = 0; iter < numberOfIterations; ++iter) 
		{
			valid0.forEachIndex([&](size_t i, size_t j) 
			{
				T sum = zero<T>();
				unsigned int count = 0;

				if (!valid0(i, j)) 
				{
					if (i + 1 < size.x && valid0(i + 1, j)) 
					{
						sum += output(i + 1, j);
						++count;
					}

					if (i > 0 && valid0(i - 1, j))
					{
						sum += output(i - 1, j);
						++count;
					}

					if (j + 1 < size.y && valid0(i, j + 1)) 
					{
						sum += output(i, j + 1);
						++count;
					}

					if (j > 0 && valid0(i, j - 1)) 
					{
						sum += output(i, j - 1);
						++count;
					}

					if (count > 0) 
					{
						output(i, j) = sum / static_cast<typename ScalarType<T>::value>(count);
						valid1(i, j) = 1;
					}
				}
				else 
					valid1(i, j) = 1;
			});

			valid0.swap(valid1);
		}
	}

	template <typename T>
	void extrapolateToRegion(
		const ConstArrayAccessor3<T>& input,
		const ConstArrayAccessor3<char>& valid,
		unsigned int numberOfIterations,
		ArrayAccessor3<T> output) {
		const Size3 size = input.size();

		assert(size == valid.size());
		assert(size == output.size());

		Array3<char> valid0(size);
		Array3<char> valid1(size);

		valid0.parallelForEachIndex([&](size_t i, size_t j, size_t k) {
			valid0(i, j, k) = valid(i, j, k);
			output(i, j, k) = input(i, j, k);
		});

		for (unsigned int iter = 0; iter < numberOfIterations; ++iter) {
			valid0.forEachIndex([&](size_t i, size_t j, size_t k) {
				T sum = zero<T>();
				unsigned int count = 0;

				if (!valid0(i, j, k)) {
					if (i + 1 < size.x && valid0(i + 1, j, k)) {
						sum += output(i + 1, j, k);
						++count;
					}

					if (i > 0 && valid0(i - 1, j, k)) {
						sum += output(i - 1, j, k);
						++count;
					}

					if (j + 1 < size.y && valid0(i, j + 1, k)) {
						sum += output(i, j + 1, k);
						++count;
					}

					if (j > 0 && valid0(i, j - 1, k)) {
						sum += output(i, j - 1, k);
						++count;
					}

					if (k + 1 < size.z && valid0(i, j, k + 1)) {
						sum += output(i, j, k + 1);
						++count;
					}

					if (k > 0 && valid0(i, j, k - 1)) {
						sum += output(i, j, k - 1);
						++count;
					}

					if (count > 0) {
						output(i, j, k)
							= sum
							/ static_cast<typename ScalarType<T>::value>(count);
						valid1(i, j, k) = 1;
					}
				}
				else {
					valid1(i, j, k) = 1;
				}
			});

			valid0.swap(valid1);
		}
	}

}

