#pragma once
#include "ReflectSystemPch.h"
#include "ReflectProperty.h"

namespace ke
{
	template<typename PropertyType>
	void ReflectProperty<PropertyType>::setFromString(const char* src)
	{
		ReflectParser::parseFromString(src, _property);
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::setFromBinary(void const* src)
	{
		ReflectParser::parseFromBinary(src, _property);
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