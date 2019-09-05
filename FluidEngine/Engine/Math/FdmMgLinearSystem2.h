#pragma once

#include "Mg.h"
#include "FdmLinearSystem2.h"
#include "../Geometry/FaceCenteredGrid2.h"

namespace Engine
{
	//! Multigrid-style 2-D FDM matrix.
	typedef MgMatrix<FdmBlas2> FdmMgMatrix2;

	//! Multigrid-style 2-D FDM vector.
	typedef MgVector<FdmBlas2> FdmMgVector2;

	//! Multigrid-syle 2-D linear system.
	struct FdmMgLinearSystem2 
	{
		//! The system matrix.
		FdmMgMatrix2 A;

		//! The solution vector.
		FdmMgVector2 x;

		//! The RHS vector.
		FdmMgVector2 b;

		//! Clears the linear system.
		void clear();

		//! Returns the number of multigrid levels.
		size_t numberOfLevels() const;

		//! Resizes the system with the coarsest resolution and number of levels.
		void resizeWithCoarsest(const Size2 &coarsestResolution, size_t numberOfLevels);

		//!
		//! \brief Resizes the system with the finest resolution and max number of
		//! levels.
		//!
		//! This function resizes the system with multiple levels until the
		//! resolution is divisible with 2^(level-1).
		//!
		//! \param finestResolution - The finest grid resolution.
		//! \param maxNumberOfLevels - Maximum number of multigrid levels.
		//!
		void resizeWithFinest(const Size2 &finestResolution, size_t maxNumberOfLevels);
	};

	//! Multigrid utilities for 2-D FDM system.
	class FdmMgUtils2 
	{
	public:
		//! Restricts given finer grid to the coarser grid.
		static void restrict(const FdmVector2 &finer, FdmVector2 *coarser);

		//! Corrects given coarser grid to the finer grid.
		static void correct(const FdmVector2 &coarser, FdmVector2 *finer);

		//! Resizes the array with the coarsest resolution and number of levels.
		template <typename T>
		static void resizeArrayWithCoarsest(const Size2 &coarsestResolution, size_t numberOfLevels, std::vector<Array2<T>> *levels);

		//!
		//! \brief Resizes the array with the finest resolution and max number of
		//! levels.
		//!
		//! This function resizes the system with multiple levels until the
		//! resolution is divisible with 2^(level-1).
		//!
		//! \param finestResolution - The finest grid resolution.
		//! \param maxNumberOfLevels - Maximum number of multigrid levels.
		//!
		template <typename T>
		static void resizeArrayWithFinest(const Size2 &finestResolution, size_t maxNumberOfLevels, std::vector<Array2<T>> *levels);
	};

	//! ----------------------------------Definition---------------------------------------------

	template <typename T>
	void FdmMgUtils2::resizeArrayWithCoarsest(
		const Size2& coarsestResolution,
		size_t numberOfLevels,
		std::vector<Array2<T>>* levels) 
	{
		numberOfLevels = std::max(numberOfLevels, kOneSize);

		levels->resize(numberOfLevels);

		// Level 0 is the finest level, thus takes coarsestResolution ^
		// numberOfLevels.
		// Level numberOfLevels - 1 is the coarsest, taking coarsestResolution.
		Size2 res = coarsestResolution;
		for (size_t level = 0; level < numberOfLevels; ++level) 
		{
			(*levels)[numberOfLevels - level - 1].resize(res);
			res.x = res.x << 1;
			res.y = res.y << 1;
		}
	}

	template <typename T>
	void FdmMgUtils2::resizeArrayWithFinest(
		const Size2& finestResolution,
		size_t maxNumberOfLevels,
		std::vector<Array2<T>>* levels) 
	{
		Size2 res = finestResolution;
		size_t i = 1;
		for (; i < maxNumberOfLevels; ++i) 
		{
			if (res.x % 2 == 0 && res.y % 2 == 0)
			{
				res.x = res.x >> 1;
				res.y = res.y >> 1;
			}
			else 
				break;
		}
		resizeArrayWithCoarsest(res, i, levels);
	}


}
