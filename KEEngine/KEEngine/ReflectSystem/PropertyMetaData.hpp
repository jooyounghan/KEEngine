#pragma once
#include "PropertyMetaData.h"
#include "ReflectMetaData.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	PropertyMetaData<ObjectType, PropertyType>::PropertyMetaData(const PropertyType& defaultValue)
	{
		if constexpr (!IS_BASE_OF_REFLECT_OBJECT(PropertyType))
		{
			_defaultValueBuffer.set(ReflectParser::getPropertyBufferSize(&defaultValue));
			ReflectParser::parseToBinary(&_defaultValueBuffer, &defaultValue);
		}
	}

	template<typename ObjectType, typename PropertyType>
	void PropertyMetaData<ObjectType, PropertyType>::applyDefaultValue(IReflectProperty* reflectProperty)
	{
		if constexpr (IS_BASE_OF_REFLECT_OBJECT(PropertyType))
		{
			static_cast<ReflectObject<PropertyType>*>(static_cast<ReflectProperty<PropertyType>*>(reflectProperty)->_property)->initialize();
		}
		else
		{
			reflectProperty->setFromBinary(_defaultValueBuffer.getBuffer());
		}
	}
}