#pragma once
#include "IReflectPODProperty.h"
#include "ReflectPropertyAccessor.h"
#include "ReflectParser.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectProperty : public IReflectPODProperty, public ReflectPropertyInfo<PropertyType>, public ReflectPropertyAccessor<ObjectType, PropertyType>
	{
    public:
        ReflectProperty(
            const FlyweightStringA& name
            , Getter<ObjectType, PropertyType> getter
            , ConstGetter<ObjectType, PropertyType> constGetter
            , Setter<ObjectType, PropertyType> setter
        );
        ~ReflectProperty() override = default;

    protected:
        virtual void* getPODPropertyInfoPtr() override { return static_cast<ReflectPropertyInfo<PropertyType>*>(this); }
        virtual const void* getPODPropertyInfoPtr() const override { return static_cast<const ReflectPropertyInfo<PropertyType>*>(this); }

    public:
        virtual void fromBianry(IReflectObject* object, const void* src) override;
        virtual void toBinary(const IReflectObject* object, IBuffer* outDst) const override;
        virtual void fromString(IReflectObject* object, const char* src, size_t strLen) override;
        virtual void toString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
    };
}
#include "ReflectProperty.hpp"