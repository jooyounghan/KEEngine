#pragma once
#include "ReflectProperty.h"
#include "StringConvertor.h"

namespace ke
{
	IReflectProperty::IReflectProperty(const char* str) : _propertyName(str) {}
	
	template<typename PropertyType>
	ReflectProperty<PropertyType>::ReflectProperty(const char* str)
		: IReflectProperty(str)
	{
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::setFromString(const char* src) 
	{ 
		_property = move(ReflectParser<PropertyType>::ParseFromString(src)); 
	}

	template<typename PropertyType>
	void ReflectProperty<PropertyType>::setFromBinary(void const* src) 
	{
		_property = move(ReflectParser<PropertyType>::ParseFromBinary(src));
	}
	
	template<typename PropertyType>
	OwnedStringA ReflectProperty<PropertyType>::getToString() const
	{ 
		return ReflectParser<PropertyType>::ParseToString(_property);
	}
	
	template<typename PropertyType>
	void ReflectProperty<PropertyType>::getToBinary(StaticBuffer<kPropertyBinaryBufferSize>& outBuffer)
	{ 
		ReflectParser<PropertyType>::ParseToBinary(_property, outBuffer);
	}
}