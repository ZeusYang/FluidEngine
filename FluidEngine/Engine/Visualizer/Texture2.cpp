#include "Texture2.h"

namespace Engine
{
	Texture2::Texture2() {}

	Texture2::~Texture2() {}

	void Texture2::clear() 
	{
		_size = Size2();
		onClear();
	}

	void Texture2::setTexture(const ConstArrayView2<Vector4F> &data) 
	{
		//if (data.size() == Size2()) 
		//	clear();
		//else if (data.size() == _size) 
		//	update(data);
		//else 
		//{
		//	clear();
		//	_size = data.size();
		//	onSetTexture(data);
		//}
	}

	void Texture2::bind(Renderer *renderer, unsigned int slotId) 
	{
		onBind(renderer, slotId);
	}

	const Size2 &Texture2::size() const { return _size; }

	const TextureSamplingMode &Texture2::samplingMode() const { return _samplingMode; }

	void Texture2::setSamplingMode(const TextureSamplingMode &mode) 
	{
		_samplingMode = mode;
		onSamplingModeChanged(mode);
	}
}