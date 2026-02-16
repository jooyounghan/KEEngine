#pragma once
#include "ReflectEnumProperty.h"
#include <cstring>

namespace ke
{
	template<typename ObjectType, typename EnumType>
	ReflectEnumProperty<ObjectType, EnumType>::ReflectEnumProperty(
		const FlyweightStringA& name
		, Getter<ObjectType, EnumType> getter
		, ConstGetter<ObjectType, EnumType> constGetter
		, Setter<ObjectType, EnumType> setter
	)
		: ReflectPropertyBase<ObjectType, EnumType>(name, getter, constGetter, setter)
	{
	}

	template<typename ObjectType, typename EnumType>
	int64 ReflectEnumProperty<ObjectType, EnumType>::getEnumValue(const IReflectObject* object) const
	{
		return static_cast<int64>(this->get(object));
	}

	template<typename ObjectType, typename EnumType>
	void ReflectEnumProperty<ObjectType, EnumType>::setEnumValue(IReflectObject* object, int64 value)
	{
		this->set(object, static_cast<EnumType>(value));
	}

	template<typename ObjectType, typename EnumType>
	const char* ReflectEnumProperty<ObjectType, EnumType>::getEnumName(int64 value) const
	{
		for (size_t i = 0; i < _enumValues.size(); ++i)
		{
			if (_enumValues[i] == value)
			{
				return _enumNames[i];
			}
		}
		return nullptr;
	}

	template<typename ObjectType, typename EnumType>
	const std::vector<int64>& ReflectEnumProperty<ObjectType, EnumType>::getAllEnumValues() const
	{
		return _enumValues;
	}

	template<typename ObjectType, typename EnumType>
	const std::vector<const char*>& ReflectEnumProperty<ObjectType, EnumType>::getAllEnumNames() const
	{
		return _enumNames;
	}

	template<typename ObjectType, typename EnumType>
	void ReflectEnumProperty<ObjectType, EnumType>::registerEnumValue(const char* name, int64 value)
	{
		_enumNames.push_back(name);
		_enumValues.push_back(value);
	}

	template<typename ObjectType, typename EnumType>
	void ReflectEnumProperty<ObjectType, EnumType>::setFromBianry(IReflectObject* object, const void* src)
	{
		ReflectParser::parseFromBinary(src, &this->get(object));
	}

	template<typename ObjectType, typename EnumType>
	void ReflectEnumProperty<ObjectType, EnumType>::getToBinary(const IReflectObject* object, IBuffer* outDst) const
	{
		ReflectParser::parseToBinary(outDst, &this->get(object));
	}

	template<typename ObjectType, typename EnumType>
	void ReflectEnumProperty<ObjectType, EnumType>::setFromString(IReflectObject* object, const char* src, size_t strlen)
	{
		// Try to parse as enum name first
		for (size_t i = 0; i < _enumNames.size(); ++i)
		{
			if (strncmp(_enumNames[i], src, strlen) == 0 && _enumNames[i][strlen] == '\0')
			{
				this->set(object, static_cast<EnumType>(_enumValues[i]));
				return;
			}
		}
		// Fall back to parsing as integer
		ReflectParser::parseFromString(src, strlen, &this->get(object));
	}

	template<typename ObjectType, typename EnumType>
	void ReflectEnumProperty<ObjectType, EnumType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		int64 value = static_cast<int64>(this->get(object));
		const char* name = getEnumName(value);
		if (name != nullptr)
		{
			outStringBuffer->write(name, strlen(name));
		}
		else
		{
			ReflectParser::parseToString(outStringBuffer, &this->get(object));
		}
	}
}
