#pragma once
#include "IReflectProperty.h"
#include "IReflectPODProperty.h"

namespace ke
{
    template<typename PropertyType>
    class ReflectPropertyBinder
    {
    public:
        static void bindProperty(
            IReflectProperty* reflectProperty
            , const EReflectUIOption& uiOption
        );

    public:
        static void bindProperty(
            IReflectProperty* reflectProperty
            , const EReflectUIOption& uiOption
            , const PropertyType& defaultValue
        );

    public:
        static void bindProperty(
            IReflectProperty* reflectProperty
            , const EReflectUIOption& uiOption
            , const PropertyType& defaultValue
            , const PropertyType& maxValue
            , const PropertyType& minValue
            , const PropertyType& stepValue
        );
    };
}
#include "ReflectPropertyBinder.hpp"