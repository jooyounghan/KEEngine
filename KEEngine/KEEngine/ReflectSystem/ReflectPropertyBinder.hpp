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
    void ReflectPropertyBinder<PropertyType>::bindProperty(IReflectProperty* reflectProperty, const EReflectUIOption& uiOption, const PropertyType& defaultValue, const PropertyType& maxValue, const PropertyType& minValue, const PropertyType& stepValue)
    {
        reflectProperty->setUIOption(uiOption);
        if (IReflectPODProperty* reflectPODProperty = reflectProperty->castTo<IReflectPODProperty>())
        {
            if (ReflectPODPropertyInfo<PropertyType>* info = reflectPODProperty->getPODPropertyInfo<PropertyType>())
            {
                info->assignRangeInfo(minValue, maxValue, stepValue);
                info->setDefaultValue(defaultValue);
            }
        }
    }
}