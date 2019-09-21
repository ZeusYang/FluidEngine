#pragma once

#include "../Math/Vector4.h"

namespace Engine
{
	class ColorUtils
	{
	public:

		static Vector4F makeWhite();

		static Vector4F makeGray();

		static Vector4F makeBlack();

		static Vector4F makeRed();

		static Vector4F makeGreen();

		static Vector4F makeBlue();

		static Vector4F makeCyan();

		static Vector4F makeMagenta();

		static Vector4F makeYellow();

		//!
		//! Makes color with jet colormap.
		//!
		//! \param value Input scalar value in [-1, 1] range.
		//! \return New color instance.
		//!
		static Vector4F makeJet(float value);

	};


}