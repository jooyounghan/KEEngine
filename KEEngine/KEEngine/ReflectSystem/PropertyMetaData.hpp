#pragma once
#include "PropertyMetaData.h"
#include "ReflectParser.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	PropertyMetaData<ObjectType, PropertyType>::PropertyMetaData(const PropertyType& defaultValue, Getter getter)
		: _getter(getter)
	{
		_defaultValueBuffer.set(ReflectParser::getPropertyBufferSize(&defaultValue));
		ReflectParser::parseToBinary(&_defaultValueBuffer, &defaultValue);
	}

	template<typename ObjectType, typename PropertyType>
	IReflectProperty* PropertyMetaData<ObjectType, PropertyType>::getFromObject(ObjectType* reflectObject)
	{
		return (reflectObject->*(_getter))();
	}

	template<typename ObjectType, typename PropertyType>
	void PropertyMetaData<ObjectType, PropertyType>::applyDefaultValue(IReflectProperty* reflectProperty)
	{
		reflectProperty->setFromBinary(_defaultValueBuffer.getBuffer());
	}

	template<typename ObjectType, typename PropertyType>
	const void* PropertyMetaData<ObjectType, PropertyType>::getDefaultValue() const 
	{ 
		return _defaultValueBuffer.getConstBuffer();
	}
}