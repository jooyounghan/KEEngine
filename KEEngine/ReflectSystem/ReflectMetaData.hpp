#include "ReflectMetaData.h"
#include "TemplateCommon.h"

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
}