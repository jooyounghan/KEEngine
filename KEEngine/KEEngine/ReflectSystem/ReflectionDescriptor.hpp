#pragma once
#include "ReflectionDescriptor.h"
#include "ReflectParser.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	ReflectDescriptor<ObjectType, PropertyType>::ReflectDescriptor(const PropertyType& defaultValue, Getter getter)
		: _getter(getter)
	{
		if constexpr (std::is_base_of_v<IReflection, PropertyType>)
		{
			// 수정 필요
			_defaultValueBuffer.set(sizeof(PropertyType));
		}
		else
		{
			_defaultValueBuffer.set(sizeof(PropertyType));
			ReflectParser::parseToBinary(&_defaultValueBuffer, defaultValue);
		}

	}

	template<typename ObjectType, typename PropertyType>
	void ReflectDescriptor<ObjectType, PropertyType>::applyDefaultValue(IReflection* reflection)
	{
		reflection->setFromBinary(_defaultValueBuffer.getBuffer());
	}

	template<typename ObjectType, typename PropertyType>
	const void* ReflectDescriptor<ObjectType, PropertyType>::getDefaultValue() const 
	{ 
		return _defaultValueBuffer.getConstBuffer();
	}

	template<typename ObjectType, typename PropertyType>
	IReflection* ReflectDescriptor<ObjectType, PropertyType>::getFromObject(ObjectType* reflectObject)
	{
		return (reflectObject->*(_getter))();
	}
}