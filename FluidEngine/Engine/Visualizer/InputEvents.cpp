#include "InputEvents.h"

namespace Engine
{
	// MARK: PointerEvent implementation

	PointerEvent::PointerEvent() : 
		_x(0.0),
		_y(0.0),
		_deltaX(0.0),
		_deltaY(0.0),
		_modifierKey(ModifierKey::None),
		_inputType(PointerInputType::Unknown),
		_pressedMouseButton(MouseButtonType::None) {}

	PointerEvent::PointerEvent(
		PointerInputType newInputType,
		ModifierKey newModifierKey,
		float newX, float newY,
		float newDeltaX, float newDelyaY,
		MouseButtonType pressedMouseButton,
		MouseWheelData wheelData) :
		_x(newX),
		_y(newY),
		_deltaX(newDeltaX),
		_deltaY(newDelyaY),
		_inputType(newInputType),
		_modifierKey(newModifierKey),
		_pressedMouseButton(pressedMouseButton),
		_wheelData(wheelData) {}

	PointerInputType PointerEvent::inputType() const { return _inputType; }

	ModifierKey PointerEvent::modifierKey() const { return _modifierKey; }

	float PointerEvent::x() const { return _x; }

	float PointerEvent::y() const { return _y; }

	float PointerEvent::deltaX() const { return _deltaX; }

	float PointerEvent::deltaY() const { return _deltaY; }

	MouseButtonType PointerEvent::pressedMouseButton() const { return _pressedMouseButton; }

	const MouseWheelData &PointerEvent::wheelData() const { return _wheelData; }

	// MARK: KeyEvent implementation
	KeyEvent::KeyEvent() : _key(0), _modifierKey(ModifierKey::None) {}

	KeyEvent::KeyEvent(int newKey, ModifierKey newModifierKey)
		: _key(newKey), _modifierKey(newModifierKey) {}

	int KeyEvent::key() const { return _key; }

	ModifierKey KeyEvent::modifierKey() const { return _modifierKey; }

}