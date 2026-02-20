#define DEFAULT_BIND_PROPERTY_PARAMETER     \
    IReflectProperty* reflectProperty,      \
    const EReflectUIOption& uiOption

#define DECLAERE_BIND_DEFAULT_SPECIALIZATION(PropertyType)  \
template<>                                                  \
void ReflectPropertyBinder<PropertyType>::bindProperty(     \
    DEFAULT_BIND_PROPERTY_PARAMETER                         \
    , const PropertyType& defaultValue                      \
)

#define DECLARE_BIND_DEFAULT_RANGE_SPECILAIZATION(PropertyType) \
template<>                                                      \
void ReflectPropertyBinder<PropertyType>::bindProperty(         \
    DEFAULT_BIND_PROPERTY_PARAMETER                             \
    , const PropertyType& defaultValue                          \
    , const PropertyType& minValue                              \
    , const PropertyType& maxValue                              \
    , const PropertyType& step                                  \
)

namespace ke
{
    template<typename PropertyType>
    void ReflectPropertyBinder<PropertyType>::bindProperty(
        IReflectProperty* reflectProperty,
        const EReflectUIOption& uiOption
    )
    {
        reflectProperty->setUIOption(uiOption);
    }

    template<typename PropertyType>
    void ReflectPropertyBinder<PropertyType>::bindProperty(IReflectProperty* reflectProperty, const EReflectUIOption& uiOption, const PropertyType& defaultValue)
    {
        reflectProperty->setUIOption(uiOption);
        if (IReflectPODProperty* reflectPODProperty = reflectProperty->castTo<IReflectPODProperty>())
        {
            if (ReflectPODPropertyInfo<PropertyType>* info = reflectPODProperty->getPODPropertyInfo<PropertyType>())
            {
                info->setDefaultValue(defaultValue);
            }
        }
    }

    template<typename PropertyType>
    void ReflectPropertyBinder<PropertyType>::bindProperty(IReflectProperty * reflectProperty, const EReflectUIOption & uiOption, const PropertyType & defaultValue, const PropertyType & maxValue, const PropertyType & minValue, const PropertyType & stepValue)
    {
        STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectPropertyBinder);
    }

#pragma region Bind Specializations
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(bool);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(uint8);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(uint16);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(uint32);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(uint64);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(int8);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(int16);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(int32);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(int64);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(float);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(double);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(std::string);
    DECLAERE_BIND_DEFAULT_SPECIALIZATION(FlyweightStringA);

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