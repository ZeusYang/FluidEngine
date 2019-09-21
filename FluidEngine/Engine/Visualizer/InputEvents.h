#pragma once

#include <cstdint>

#include "../Utils/Macros.h"

namespace Engine
{
	//! Pointer input types.
	enum class PointerInputType : int8_t 
	{
		//! Unknown pointer input type.
		Unknown = 0,
		//! Mouse pointer input type.
		Mouse = 1,
		//! Touch pointer input type.
		Touch = 2,
		//! Pen pointer input type.
		Pen = 3,
	};

	//! Mouse button types.
	enum class MouseButtonType : int8_t 
	{
		//! No mouse button.
		None = 0,
		//! Left mouse button.
		Left = 1,
		//! Middle mouse button.
		Middle = 2,
		//! Right mouse button.
		Right = 3,
	};

	//! Modifier key types.
	enum class ModifierKey : int8_t
	{
		//! No modifier.
		None = 0,
		//! Shift modifier key.
		Shift = 1 << 0,
		//! Ctrl modifier key.
		Ctrl = 1 << 1,
		//! Alt modifier key.
		Alt = 1 << 2,
	};

	//! And operator for two modifier keys.
	inline ModifierKey operator&(ModifierKey a, ModifierKey b)
	{
		return static_cast<ModifierKey>(static_cast<int>(a) & static_cast<int>(b));
	}

	//! Or operator for two modifier keys.
	inline ModifierKey operator|(ModifierKey a, ModifierKey b) 
	{
		return static_cast<ModifierKey>(static_cast<int>(a) | static_cast<int>(b));
	}

	//! Mouse wheel event data.
	struct MouseWheelData 
	{
		//! Horizontal scroll amount.
		float deltaX = 0.0f;
		//! Vertical scroll amount.
		float deltaY = 0.0f;
	};

	//! Pointer event representation.
	class PointerEvent
	{
	public:
		//! Constructs an empty event.
		PointerEvent();

		//!
		//! \brief Constructs an event with parameters.
		//!
		//! \param newInputType Pointer input type.
		//! \param newModifierKey Currently pressed modifier key.
		//! \param newX X position.
		//! \param newY Y position.
		//! \param newDeltaX Delta of X from previous event.
		//! \param newDelyaY Delta of Y from previous event.
		//! \param pressedMouseButton Currently pressed mouse button.
		//! \param wheelData Mouse scroll wheel event data.
		//!
		PointerEvent(
			PointerInputType newInputType,
			ModifierKey newModifierKey,
			float newX, float newY,
			float newDeltaX, float newDelyaY,
			MouseButtonType pressedMouseButton,
			MouseWheelData wheelData);

		//! Returns pointer input type.
		PointerInputType inputType() const;

		//! Returns modifier key.
		ModifierKey modifierKey() const;

		//! Returns current x position.
		float x() const;

		//! Returns current y position.
		float y() const;

		//! Returns delta of x position.
		float deltaX() const;

		//! Returns delta of y position.
		float deltaY() const;

		//! Returns currently pressed mouse button.
		MouseButtonType pressedMouseButton() const;

		//! Returns mouse scroll wheel data.
		const MouseWheelData& wheelData() const;

	private:
		float _x;
		float _y;
		float _deltaX;
		float _deltaY;
		ModifierKey _modifierKey;
		MouseWheelData _wheelData;
		PointerInputType _inputType;
		MouseButtonType _pressedMouseButton;

	};

	//! Key input event representation.
	class KeyEvent 
	{
	public:
		//! Constructs an empty event.
		KeyEvent();

		//!
		//! \brief Constructs an event with parameters.
		//!
		//! \param newKey Key code.
		//! \param newModifierKey Modifier key type.
		//!
		KeyEvent(int newKey, ModifierKey newModifierKey);

		//! Returns key code.
		int key() const;

		//! Returns modifier key type.
		ModifierKey modifierKey() const;

	private:
		int _key = 0;
		ModifierKey _modifierKey = ModifierKey::None;
	};

}
