#pragma once
#include "ReflectProperty.h"

namespace ke
{
	template<typename PropertyType>
	Offset ReflectProperty<PropertyType>::setFromString(const char* src)
	{
		if constexpr (std::is_base_of_v<IReflection, PropertyType>)
		{
			return _property.setFromString(src);
		}
		else
		{
			return ReflectParser::parseFromString(src, _property);
		}
	}

	template<typename PropertyType>
	Offset ReflectProperty<PropertyType>::setFromBinary(const char* src)
	{
		if constexpr (std::is_base_of_v<IReflection, PropertyType>)
		{
			return _property.setFromBinary(src);
		}
		else
		{
			return ReflectParser::parseFromBinary(src, _property);
		}

	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToString(IBuffer* outBuffer) const
	{
		if constexpr (std::is_base_of_v<IReflection, PropertyType>)
		{
			_property.getToString(outBuffer);
		}
		else
		{
			ReflectParser::parseToString(outBuffer, _property);
		}
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToBinary(IBuffer* outBuffer) const
	{
		if constexpr (std::is_base_of_v<IReflection, PropertyType>)
		{
			_property.getToBinary(outBuffer);
		}
		else
		{
			ReflectParser::parseToBinary(outBuffer, _property);
		}
	}
}