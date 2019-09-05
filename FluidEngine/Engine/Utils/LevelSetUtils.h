#pragma once

#include <cmath>

#include "Macros.h"

namespace Engine
{
	//!
	//! \brief      Returns true if \p phi is inside the implicit surface (< 0).
	//!
	//! \param[in]  phi   The level set value.
	//!
	//! \tparam     T     Value type.
	//!
	//! \return     True if inside the implicit surface, false otherwise.
	//!
	template <typename T>
	bool isInsideSdf(T phi);

	//!
	//! \brief      Returns smeared Heaviside function.
	//!
	//! This function returns smeared (or smooth) Heaviside (or step) function
	//! between 0 and 1. If \p phi is less than -1.5, it will return 0. If \p phi
	//! is greater than 1.5, it will return 1. Between -1.5 and 1.5, the function
	//! will return smooth profile between 0 and 1. Derivative of this function is
	//! smearedDeltaSdf.
	//!
	//! \param[in]  phi   The level set value.
	//!
	//! \tparam     T     Value type.
	//!
	//! \return     Smeared Heaviside function.
	//!
	template <typename T>
	T smearedHeavisideSdf(T phi);

	//!
	//! \brief      Returns smeared delta function.
	//!
	//! This function returns smeared (or smooth) delta function between 0 and 1.
	//! If \p phi is less than -1.5, it will return 0. If \p phi is greater than
	//! 1.5, it will also return 0. Between -1.5 and 1.5, the function will return
	//! smooth delta function. Integral of this function is smearedHeavisideSdf.
	//!
	//! \param[in]  phi   The level set value.
	//!
	//! \tparam     T     Value type.
	//!
	//! \return     Smeared delta function.
	//!
	template <typename T>
	T smearedDeltaSdf(T phi);

	//!
	//! \brief      Returns the fraction occupied by the implicit surface.
	//!
	//! The input parameters, \p phi0 and \p phi1, are the level set values,
	//! measured from two nearby points. This function computes how much the
	//! implicit surface occupies the line between two points. For example, if both
	//! \p phi0 and \p phi1 are negative, it means the points are both inside the
	//! surface, thus the function will return 1. If both are positive, it will
	//! return 0 because both are outside the surface. If the signs are different,
	//! then only one of the points is inside the surface and the function will
	//! return a value between 0 and 1.
	//!
	//! \param[in]  phi0  The level set value from the first point.
	//! \param[in]  phi1  The level set value from the second point.
	//!
	//! \tparam     T     Value type.
	//!
	//! \return     The fraction occupied by the implicit surface.
	//!
	template <typename T>
	T fractionInsideSdf(T phi0, T phi1);

	//!
	//! \brief      Returns the fraction occupied by the implicit surface.
	//!
	//! Given four signed distance values (square corners), determine what fraction
	//! of the square is "inside". The original implementation can be found from
	//! Christopher Batty's variational fluid code at
	//! https://github.com/christopherbatty/Fluid3D.
	//!
	//! \tparam T               Value type.
	//!
	//! \param phiBottomLeft    The level set value on the bottom-left corner.
	//! \param phiBottomRight   The level set value on the bottom-right corner.
	//! \param phiTopLeft       The level set value on the top-left corner.
	//! \param phiTopRight      The level set value on the top-right corner.
	//!
	//! \return                 The fraction occupied by the implicit surface.
	//!
	template <typename T>
	T fractionInside(T phiBottomLeft, T phiBottomRight, T phiTopLeft, T phiTopRight);


	//! --------------------------------Definition-----------------------------

	template <typename T>
	bool isInsideSdf(T phi) { return phi < 0; }

	template <typename T>
	inline T smearedHeavisideSdf(T phi) 
	{
		if (phi > 1.5) 
			return 1;
		else 
		{
			if (phi < -1.5) 
				return 0;
			else 
				return 0.5f + phi / 3.0 + 0.5f * invPi<T>() * std::sin(pi<T>() * phi / 1.5);
		}
	}

	template <typename T>
	inline T smearedDeltaSdf(T phi) 
	{
		if (std::fabs(phi) > 1.5) 
			return 0;
		else 
			return 1.0 / 3.0 + 1.0 / 3.0 * std::cos(pi<T>() * phi / 1.5);
	}

	template <typename T>
	T fractionInsideSdf(T phi0, T phi1) 
	{
		if (isInsideSdf(phi0) && isInsideSdf(phi1)) 
			return 1;
		else if (isInsideSdf(phi0) && !isInsideSdf(phi1)) 
			return phi0 / (phi0 - phi1);
		else if (!isInsideSdf(phi0) && isInsideSdf(phi1)) 
			return phi1 / (phi1 - phi0);
		else 
			return 0;
	}

	template <typename T>
	void cycleArray(T* arr, int size) 
	{
		T t = arr[0];
		for (int i = 0; i < size - 1; ++i) 
			arr[i] = arr[i + 1];
		arr[size - 1] = t;
	}

	template <typename T>
	T fractionInside(T phiBottomLeft, T phiBottomRight, T phiTopLeft, T phiTopRight) 
	{
		int inside_count = (phiBottomLeft < 0 ? 1 : 0) + (phiTopLeft < 0 ? 1 : 0) +
			(phiBottomRight < 0 ? 1 : 0) + (phiTopRight < 0 ? 1 : 0);
		T list[] = { phiBottomLeft, phiBottomRight, phiTopRight, phiTopLeft };

		if (inside_count == 4) 
			return 1;

		else if (inside_count == 3) 
		{
			// rotate until the positive value is in the first position
			while (list[0] < 0) 
				cycleArray(list, 4);

			// Work out the area of the exterior triangle
			T side0 = 1 - fractionInsideSdf(list[0], list[3]);
			T side1 = 1 - fractionInsideSdf(list[0], list[1]);
			return 1 - 0.5f * side0 * side1;
		}
		else if (inside_count == 2) 
		{
			// rotate until a negative value is in the first position, and the next
			// negative is in either slot 1 or 2.
			while (list[0] >= 0 || !(list[1] < 0 || list[2] < 0)) 
				cycleArray(list, 4);

			if (list[1] < 0) 
			{  // the matching signs are adjacent
				T side_left = fractionInsideSdf(list[0], list[3]);
				T side_right = fractionInsideSdf(list[1], list[2]);
				return 0.5f * (side_left + side_right);
			}
			else 
			{  // matching signs are diagonally opposite
			 // determine the centre point's sign to disambiguate this case
				T middle_point = 0.25f * (list[0] + list[1] + list[2] + list[3]);
				if (middle_point < 0) {
					T area = 0;

					// first triangle (top left)
					T side1 = 1 - fractionInsideSdf(list[0], list[3]);
					T side3 = 1 - fractionInsideSdf(list[2], list[3]);

					area += 0.5f * side1 * side3;

					// second triangle (top right)
					T side2 = 1 - fractionInsideSdf(list[2], list[1]);
					T side0 = 1 - fractionInsideSdf(list[0], list[1]);
					area += 0.5f * side0 * side2;

					return 1 - area;
				}
				else 
				{
					T area = 0;

					// first triangle (bottom left)
					T side0 = fractionInsideSdf(list[0], list[1]);
					T side1 = fractionInsideSdf(list[0], list[3]);
					area += 0.5f * side0 * side1;

					// second triangle (top right)
					T side2 = fractionInsideSdf(list[2], list[1]);
					T side3 = fractionInsideSdf(list[2], list[3]);
					area += 0.5f * side2 * side3;
					return area;
				}
			}
		}
		else if (inside_count == 1) 
		{
			// rotate until the negative value is in the first position
			while (list[0] >= 0) {
				cycleArray(list, 4);
			}

			// Work out the area of the interior triangle, and subtract from 1.
			T side0 = fractionInsideSdf(list[0], list[3]);
			T side1 = fractionInsideSdf(list[0], list[1]);
			return 0.5f * side0 * side1;
		}
		else 
			return 0;
	}

	template <typename T>
	T distanceToZeroLevelSet(T phi0, T phi1) 
	{
		if (std::fabs(phi0) + std::fabs(phi1) > kEpsilonD) 
			return std::fabs(phi0) / (std::fabs(phi0) + std::fabs(phi1));
		else 
			return static_cast<T>(0.5);
	}

}