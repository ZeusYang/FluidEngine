#pragma once

#include <vector>
#include <cstring>

#include "../Math/Array1.h"

namespace Engine
{
	//! Abstract base class for any serializable class.
	class Serializable
	{
	public:

		Serializable() = default;

		virtual ~Serializable() = default;

		//! Serializes this instance into the flat buffer.
		virtual void serialize(std::vector<uint8_t>* buffer) const = 0;

		//! Deserializes this instance from the flat buffer.
		virtual void deserialize(const std::vector<uint8_t>& buffer) = 0;

	};

	//! Serializes serializable object.
	void serialize(const Serializable* serializable, std::vector<uint8_t>* buffer);

	//! Serializes data chunk using common schema.
	void serialize(const uint8_t* data, size_t size, std::vector<uint8_t>* buffer);

	//! Serializes data chunk using common schema.
	template <typename T>
	void serialize(const ConstArrayAccessor1<T>& array, std::vector<uint8_t>* buffer);

	//! Deserializes buffer to serializable object.
	void deserialize(const std::vector<uint8_t>& buffer, Serializable* serializable);

	//! Deserializes buffer to data chunk using common schema.
	void deserialize(const std::vector<uint8_t>& buffer, std::vector<uint8_t>* data);

	//! Deserializes buffer to data chunk using common schema.
	template <typename T>
	void deserialize(const std::vector<uint8_t>& buffer, Array1<T>* array);

	//! -----------------------------Definition---------------------------------

	template <typename T>
	void serialize(const ConstArrayAccessor1<T>& array, std::vector<uint8_t>* buffer) 
	{
		size_t size = sizeof(T) * array.size();
		serialize(reinterpret_cast<const uint8_t*>(array.data()), size, buffer);
	}

	template <typename T>
	void deserialize(const std::vector<uint8_t>& buffer, Array1<T>* array) 
	{
		std::vector<uint8_t> data;
		deserialize(buffer, &data);
		array->resize(data.size() / sizeof(T));
		memcpy(reinterpret_cast<uint8_t*>(array->data()), data.data(), data.size());
	}

}