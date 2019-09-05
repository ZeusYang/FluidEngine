#pragma once

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/ArrayAccessor2.h"
#include "../Math/ArrayAccessor3.h"

namespace Engine
{
	//! \brief Returns 2-D gradient vector from given 2-D scalar grid-like array
	//!        \p data, \p gridSpacing, and array index (\p i, \p j).
	Vector2D gradient2(
		const ConstArrayAccessor2<double>& data,
		const Vector2D& gridSpacing,
		size_t i,
		size_t j);

	//! \brief Returns 2-D gradient vectors from given 2-D vector grid-like array
	//!        \p data, \p gridSpacing, and array index (\p i, \p j).
	std::array<Vector2D, 2> gradient2(
		const ConstArrayAccessor2<Vector2D>& data,
		const Vector2D& gridSpacing,
		size_t i,
		size_t j);

	//! \brief Returns 3-D gradient vector from given 3-D scalar grid-like array
	//!        \p data, \p gridSpacing, and array index (\p i, \p j, \p k).
	Vector3D gradient3(
		const ConstArrayAccessor3<double>& data,
		const Vector3D& gridSpacing,
		size_t i,
		size_t j,
		size_t k);

	//! \brief Returns 3-D gradient vectors from given 3-D vector grid-like array
	//!        \p data, \p gridSpacing, and array index (\p i, \p j, \p k).
	std::array<Vector3D, 3> gradient3(
		const ConstArrayAccessor3<Vector3D>& data,
		const Vector3D& gridSpacing,
		size_t i,
		size_t j,
		size_t k);

	//! \brief Returns Laplacian value from given 2-D scalar grid-like array
	//!        \p data, \p gridSpacing, and array index (\p i, \p j).
	double laplacian2(
		const ConstArrayAccessor2<double>& data,
		const Vector2D& gridSpacing,
		size_t i,
		size_t j);

	//! \brief Returns 2-D Laplacian vectors from given 2-D vector grid-like array
	//!        \p data, \p gridSpacing, and array index (\p i, \p j).
	Vector2D laplacian2(
		const ConstArrayAccessor2<Vector2D>& data,
		const Vector2D& gridSpacing,
		size_t i,
		size_t j);

	//! \brief Returns Laplacian value from given 3-D scalar grid-like array
	//!        \p data, \p gridSpacing, and array index (\p i, \p j, \p k).
	double laplacian3(
		const ConstArrayAccessor3<double>& data,
		const Vector3D& gridSpacing,
		size_t i,
		size_t j,
		size_t k);

	//! \brief Returns 3-D Laplacian vectors from given 3-D vector grid-like array
	//!        \p data, \p gridSpacing, and array index (\p i, \p j, \p k).
	Vector3D laplacian3(
		const ConstArrayAccessor3<Vector3D>& data,
		const Vector3D& gridSpacing,
		size_t i,
		size_t j,
		size_t k);
}
