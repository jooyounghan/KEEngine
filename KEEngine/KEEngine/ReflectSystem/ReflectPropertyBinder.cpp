#include "ReflectSystemPch.h"
#include "ReflectPropertyBinder.h"
#include "IReflectPODProperty.h"
#include "IReflectPODSeqProperty.h"

#define DEFINE_BIND_DEFAULT_SPECIALIZATION(PropertyType)															\
DECLAERE_BIND_DEFAULT_SPECIALIZATION(PropertyType)																	\
{																													\
    reflectProperty->setUIOption(uiOption);																			\
    if (IReflectPODProperty* reflectPODProperty = reflectProperty->castTo<IReflectPODProperty>()) {					\
        if (ReflectPODPropertyInfo<PropertyType>* info = reflectPODProperty->getPODPropertyInfo<PropertyType>())	\
		{																											\
            info->setDefaultValue(defaultValue);																	\
        }																											\
    }																												\
}

#define DEFINE_BIND_DEFAULT_RANGE_SPECIALIZATION(PropertyType)														\
DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(PropertyType)																\
{																													\
    reflectProperty->setUIOption(uiOption);																			\
    if (IReflectPODProperty* reflectPODProperty = reflectProperty->castTo<IReflectPODProperty>()) {					\
        if (ReflectPODPropertyInfo<PropertyType>* info = reflectPODProperty->getPODPropertyInfo<PropertyType>())	\
		{																											\
			info->assignRangeInfo(minValue, maxValue, step);														\
            info->setDefaultValue(defaultValue);																	\
        }																											\
    }																												\
}

namespace ke
{
	DEFINE_BIND_DEFAULT_SPECIALIZATION(bool);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(uint8);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(uint16);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(uint32);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(uint64);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(int8);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(int16);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(int32);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(int64);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(float);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(double);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(std::string);
	DEFINE_BIND_DEFAULT_SPECIALIZATION(FlyweightStringA);

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
}