#include "PropertyMetaData.h"

#define DECLARE_PROPERTY_TYPE_CONVERTOR(Type)			\
template<>												\
EPropertyType PropertyTypeConvertor<Type>::GetType();

#define DEFINE_PROPERTY_TYPE_CONVERTOR(Type, PropertyType)		\
template<>														\
EPropertyType PropertyTypeConvertor<Type>::GetType()			\
{																\
	return PropertyType;										\
}

namespace ke
{
	template<typename Type>
	EPropertyType PropertyTypeConvertor<Type>::GetType()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(PropertyTypeGetter);
	};

	DECLARE_PROPERTY_TYPE_CONVERTOR(bool);
	DECLARE_PROPERTY_TYPE_CONVERTOR(int8);
	DECLARE_PROPERTY_TYPE_CONVERTOR(int16);
	DECLARE_PROPERTY_TYPE_CONVERTOR(int32);
	DECLARE_PROPERTY_TYPE_CONVERTOR(int64);
	DECLARE_PROPERTY_TYPE_CONVERTOR(uint8);
	DECLARE_PROPERTY_TYPE_CONVERTOR(uint16);
	DECLARE_PROPERTY_TYPE_CONVERTOR(uint32);
	DECLARE_PROPERTY_TYPE_CONVERTOR(uint64);
	DECLARE_PROPERTY_TYPE_CONVERTOR(float);
	DECLARE_PROPERTY_TYPE_CONVERTOR(double);

	template<typename ObjectType>
	IPropertyMetaData<ObjectType>::IPropertyMetaData(EPropertyType propertyType, EPropertyFlag propertyFlag)
		: _propertyType(propertyType)
		, _propertyFlag(propertyFlag)
	{
	}

	template<typename ObjectType>
	void IPropertyMetaData<ObjectType>::applyDefaultValue(IReflectProperty* reflectProperty) 
	{ 
		reflectProperty->setFromBinary(_defaultValueBuffer.getConstBuffer()); 
	}

	template<typename ObjectType, typename PropertyType>
	PropertyMetaData<ObjectType, PropertyType>::PropertyMetaData(
		EPropertyFlag propertyFlag,
		const PropertyType& defaultPropertyValue,
		Getter getter,
		Setter setter
	) : IPropertyMetaData<ObjectType>(PropertyTypeConvertor<PropertyType>::GetType(), propertyFlag)
		, _getter(getter)
		, _setter(setter)
	{
		ReflectParser::parseToBinary(&__super::_defaultValueBuffer, defaultPropertyValue);
	}

	template<typename ObjectType, typename PropertyType>
	const void* PropertyMetaData<ObjectType, PropertyType>::getPropertyFromObject(ObjectType* reflectObject) const
	{
		const PropertyType& ref = (reflectObject->*(_getter))();
		return static_cast<const void*>(&ref);
	}

	template<typename ObjectType, typename PropertyType>
	void PropertyMetaData<ObjectType, PropertyType>::setPropertyFromObject(ObjectType* reflectObject, const void* value)
	{
		const PropertyType* propertyPtr = static_cast<const PropertyType*>(value);
		(reflectObject->*(_setter))(*propertyPtr);
	}
}