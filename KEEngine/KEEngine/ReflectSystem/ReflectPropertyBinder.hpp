#include "ReflectPropertyBinder.h"
#pragma once

#define DEFAULT_BIND_PROPERTY_PARAMETER	\
    IReflectProperty* reflectProperty,  \
    const EReflectUIOption& uiOption

// default-only specialization: bindProperty<PropertyType>(..., const PropertyType& defaultValue)
#define DECLAERE_BIND_DEFAULT_SPECIALIZATION(PropertyType)  \
template<>													\
template<>													\
void ReflectPropertyBinder<PropertyType>::bindPropertyInner(\
DEFAULT_BIND_PROPERTY_PARAMETER,							\
    const PropertyType& defaultValue						\
)

// range specialization: bindProperty<PropertyType,PropertyType,PropertyType,PropertyType>(..., min,max,step,default)
#define DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(PropertyType)		\
template<>															\
template<>															\
void ReflectPropertyBinder<PropertyType>::bindPropertyInner(		\
DEFAULT_BIND_PROPERTY_PARAMETER,									\
    const PropertyType& minValue,									\
    const PropertyType& maxValue,									\
    const PropertyType& step,										\
    const PropertyType& defaultValue								\
)

namespace ke
{
	template<typename PropertyType>
	void ReflectPropertyBinder<PropertyType>::bindProperty(
		IReflectProperty* reflectProperty, 
		const EReflectUIOption& uiOption
	)
	{
		bindPropertyInner(reflectProperty, uiOption);
	}

	template<typename PropertyType>
	void ReflectPropertyBinder<PropertyType>::bindPropertyInner(
		IReflectProperty* reflectProperty,
		const EReflectUIOption& uiOption
	)
	{
		reflectProperty->setUIOption(uiOption);
	}

	template<typename PropertyType>
	template<typename... Args>
	void ReflectPropertyBinder<PropertyType>::bindProperty(
		IReflectProperty* reflectProperty
		, const EReflectUIOption& uiOption
		, const Args&... args
	)
	{
		ke::ReflectPropertyBinder<PropertyType>::bindPropertyInner(
			reflectProperty,
			uiOption,
			static_cast<PropertyType>(args)...
		);
	}

	template<typename PropertyType>
	template<typename ...Args>
	void ReflectPropertyBinder<PropertyType>::bindPropertyInner(
		IReflectProperty* reflectProperty, 
		const EReflectUIOption& uiOption, 
		const Args & ...args
	)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(bindProperty);
	}



#pragma region Bind Specializations
	DECLAERE_BIND_DEFAULT_SPECIALIZATION(bool);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(uint8);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(uint16);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(uint32);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(uint64);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(int8);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(int16);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(int32);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(int64);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(float);
	DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(double);
#pragma endregion
}