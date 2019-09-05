#pragma once

#include "Mg.h"
#include "FdmLinearSystem3.h"
#include "../Geometry/FaceCenteredGrid3.h"

namespace Engine
{
	//! Multigrid-style 3-D FDM matrix.
	typedef MgMatrix<FdmBlas3> FdmMgMatrix3;

	//! Multigrid-style 3-D FDM vector.
	typedef MgVector<FdmBlas3> FdmMgVector3;

	//! Multigrid-syle 3-D linear system.
	struct FdmMgLinearSystem3
	{
		//! The system matrix.
		FdmMgMatrix3 A;

		//! The solution vector.
		FdmMgVector3 x;

		//! The RHS vector.
		FdmMgVector3 b;

		//! Clears the linear system.
		void clear();

		//! Returns the number of multigrid levels.
		size_t numberOfLevels() const;

		//! Resizes the system with the coarsest resolution and number of levels.
		void resizeWithCoarsest(const Size3 &coarsestResolution, size_t numberOfLevels);

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
		void resizeWithFinest(const Size3 &finestResolution, size_t maxNumberOfLevels);
	};

	//! Multigrid utilities for 2-D FDM system.
	class FdmMgUtils3 
	{
	public:
		//! Restricts given finer grid to the coarser grid.
		static void restrict(const FdmVector3 &finer, FdmVector3 *coarser);

		//! Corrects given coarser grid to the finer grid.
		static void correct(const FdmVector3 &coarser, FdmVector3 *finer);

		//! Resizes the array with the coarsest resolution and number of levels.
		template <typename T>
		static void resizeArrayWithCoarsest(const Size3 &coarsestResolution, size_t numberOfLevels, std::vector<Array3<T>> *levels);

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
		static void resizeArrayWithFinest(const Size3 &finestResolution, size_t maxNumberOfLevels, std::vector<Array3<T>> *levels);
	};

	//! ----------------------------------Definition---------------------------------------------

	template <typename T>
	void FdmMgUtils3::resizeArrayWithCoarsest(const Size3& coarsestResolution,
		size_t numberOfLevels,
		std::vector<Array3<T>>* levels) {
		numberOfLevels = std::max(numberOfLevels, kOneSize);

		levels->resize(numberOfLevels);

		// Level 0 is the finest level, thus takes coarsestResolution ^
		// numberOfLevels.
		// Level numberOfLevels - 1 is the coarsest, taking coarsestResolution.
		Size3 res = coarsestResolution;
		for (size_t level = 0; level < numberOfLevels; ++level) {
			(*levels)[numberOfLevels - level - 1].resize(res);
			res.x = res.x << 1;
			res.y = res.y << 1;
			res.z = res.z << 1;
		}
	}

	template <typename T>
	void FdmMgUtils3::resizeArrayWithFinest(const Size3& finestResolution,
		size_t maxNumberOfLevels,
		std::vector<Array3<T>>* levels) {
		Size3 res = finestResolution;
		size_t i = 1;
		for (; i < maxNumberOfLevels; ++i) {
			if (res.x % 2 == 0 && res.y % 2 == 0 && res.z % 2 == 0) {
				res.x = res.x >> 1;
				res.y = res.y >> 1;
				res.z = res.z >> 1;
			}
			else {
				break;
			}
		}
		resizeArrayWithCoarsest(res, i, levels);
	}

}
