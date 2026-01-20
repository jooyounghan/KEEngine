#pragma once

#define BIND_PROPERTY_FUNCITON_HEADER(PropertyType)		\
template<>												\
template<>												\
void ReflectPropertyBinder<PropertyType>::bindProperty(	\

#define DEFAULT_BIND_PROPERTY_PARAMETER	\
    IReflectProperty* reflectProperty,  \
    const EReflectUIOption& uiOption

#define DECLAERE_BIND_DEFAULT_SPECIALIZATION(PropertyType)  \
BIND_PROPERTY_FUNCITON_HEADER(PropertyType)					\
DEFAULT_BIND_PROPERTY_PARAMETER,							\
    const PropertyType& defaultValue						\
)

#define DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(PropertyType) \
BIND_PROPERTY_FUNCITON_HEADER(PropertyType)						\
DEFAULT_BIND_PROPERTY_PARAMETER,								\
    const PropertyType& minValue,								\
    const PropertyType& maxValue,								\
    const PropertyType& step,									\
    const PropertyType& defaultValue							\
)

namespace ke
{
	template<typename PropertyType>
	template<typename... Args>
	void ReflectPropertyBinder<PropertyType>::bindProperty(
		IReflectProperty* reflectProperty
		, const EReflectUIOption& uiOption
		, Args... args
	)
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(bindProperty);
	}

	template<typename PropertyType>
	void ReflectPropertyBinder<PropertyType>::bindProperty(
		IReflectProperty* reflectProperty, 
		const EReflectUIOption& uiOption
	)
	{
		reflectProperty->setUIOption(uiOption);
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