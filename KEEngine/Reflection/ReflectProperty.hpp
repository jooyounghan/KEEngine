#pragma once
#include "ReflectProperty.h"

namespace ke
{
	inline IReflectProperty::IReflectProperty(const char* str) : _propertyName(str) {}
	
	template<typename PropertyType>
	inline ReflectProperty<PropertyType>::ReflectProperty(const char* str)
		: IReflectProperty(str)
	{
	}

	template<typename PropertyType>
	inline void ReflectProperty<PropertyType>::setFromString(const char* src) 
	{ 
		_property = move(ReflectParser<PropertyType>::ParseFromString(src)); 
	}

	template<typename PropertyType>
	inline void ReflectProperty<PropertyType>::setFromBinary(void const* src) 
	{
		memcpy(&_property, src, sizeof(PropertyType)); 
	}
	
	template<typename PropertyType>
	inline OwnedStringA ReflectProperty<PropertyType>::getToString() const
	{ 
		return ReflectParser<PropertyType>::ParseToString(_property);
	}
	
	template<typename PropertyType>
	inline const void* ReflectProperty<PropertyType>::getToBinary() const 
	{ 
		return static_cast<const void*>(&_property); 
	}
}