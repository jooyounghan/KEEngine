#pragma once
#include "ReflectionDescriptor.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	ReflectDescriptor<ObjectType, PropertyType>::ReflectDescriptor(Getter getter, Setter setter)
		: _getter(getter), _setter(setter)
	{
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectDescriptor<ObjectType, PropertyType>::applyDefaultValue(IReflection* reflection)
	{
		reflection->deserializeFromBinary(_defaultValueBuffer.getBufferPointer());
	}

	template<typename ObjectType, typename PropertyType>
	const void* ReflectDescriptor<ObjectType, PropertyType>::getDefaultValue() const 
	{ 
		return _defaultValueBuffer.getBufferPointer(); 
	}

	template<typename ObjectType, typename PropertyType>
	const void* ReflectDescriptor<ObjectType, PropertyType>::getFromObject(ObjectType* reflectObject) const
	{
		const PropertyType& ref = (reflectObject->*(_getter))();
		return static_cast<const void*>(&ref);
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectDescriptor<ObjectType, PropertyType>::setFromObject(ObjectType* reflectObject, const void* value)
	{
		const PropertyType* propertyPtr = static_cast<const PropertyType*>(value);
		(reflectObject->*(_setter))(*propertyPtr);
	}
}