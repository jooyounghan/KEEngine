#include "ReflectSystemPch.h"
#include "ReflectPropertyBinder.h"

#define DEFINE_BIND_DEFAULT_SPECIALIZATION(PropertyType)								\
DECLAERE_BIND_DEFAULT_SPECIALIZATION(PropertyType)										\
{																						\
	reflectProperty->setUIOption(uiOption);												\
	IReflectPODProperty* reflectPODProperty =											\
		reflectProperty->getPODProperty();												\
	if (reflectPODProperty != nullptr)													\
	{																					\
		reflectPODProperty->getBase<PropertyType>()->setDefaultValue(defaultValue);		\
	}																					\
}

#define DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(PropertyType)												\
DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(PropertyType)														\
{																											\
	reflectProperty->setUIOption(uiOption);																	\
	IReflectPODProperty* reflectPODProperty =																\
		reflectProperty->getPODProperty();																	\
	if (reflectPODProperty != nullptr)																		\
	{																										\
		ReflectPODPropertyBase<PropertyType>* property = reflectPODProperty->getBase<PropertyType>();		\
		property->assignRangeInfo(minValue, maxValue, step);												\
		property->setDefaultValue(defaultValue);															\
	}																										\
}

namespace ke
{
	DEFINE_BIND_DEFAULT_SPECIALIZATION(bool);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(uint8);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(uint16);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(uint32);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(uint64);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(int8);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(int16);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(int32);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(int64);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(float);
	DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(double);

	DEFINE_BIND_DEFAULT_SPECIALIZATION(std::string);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(FlyweightStringA);
}