#pragma once
#include "ReflectProperty.h"

namespace ke
{
	template<typename PropertyType>
	ReflectProperty<PropertyType>::ReflectProperty(const FlyweightStringA& name, PropertyType* property)
		: IReflectProperty(name), _property(property)
	{
	}

	template<typename PropertyType>
	Offset ReflectProperty<PropertyType>::setFromString(const char* src)
	{
		return ReflectParser::parseFromString(src, _property);
	}

	template<typename PropertyType>
	Offset ReflectProperty<PropertyType>::setFromBinary(const char* src)
	{
		return ReflectParser::parseFromBinary(src, _property);
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToString(IBuffer* outBuffer) const
	{
		ReflectParser::parseToString(outBuffer, _property);
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToBinary(IBuffer* outBuffer) const
	{
		ReflectParser::parseToBinary(outBuffer, _property);
	}
}