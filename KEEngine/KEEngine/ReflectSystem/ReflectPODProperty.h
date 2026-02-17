#pragma once
#include "IReflectPODProperty.h"
#include "ReflectPropertyAccessor.h"
#include "ReflectPODPropertyInfo.h"
#include "ReflectParser.h"

namespace ke
{
    template<typename PropertyType>
    struct RangedPropertyInfo
    {
        PropertyType    _maxValue;
        PropertyType    _minValue;
        PropertyType    _step;
    };

	template<typename ObjectType, typename PropertyType>
	class ReflectPODProperty : public IReflectPODProperty, public RefelctPODPropertyInfo<PropertyType>, public ReflectPropertyAccessor<ObjectType, PropertyType>
	{
    public:
        ReflectPODProperty(
            const FlyweightStringA& name
            , Getter<ObjectType, PropertyType> getter
            , ConstGetter<ObjectType, PropertyType> constGetter
            , Setter<ObjectType, PropertyType> setter
        );
        ~ReflectPODProperty() override = default;

    public:
        virtual void fromBianry(IReflectObject* object, const void* src) override;
        virtual void toBinary(const IReflectObject* object, IBuffer* outDst) const override;
        virtual void fromString(IReflectObject* object, const char* src, size_t strlen) override;
        virtual void toString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
    };
}
#include "ReflectPODProperty.hpp"