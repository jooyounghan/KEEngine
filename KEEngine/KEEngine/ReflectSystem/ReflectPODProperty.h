#pragma once
#include "IReflectPODProperty.h"
#include "ReflectPropertyAccessor.h"
#include "ReflectParser.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectPODProperty : public IReflectPODProperty, public ReflectPODPropertyInfo<PropertyType>, public ReflectPropertyAccessor<ObjectType, PropertyType>
	{
    public:
        ReflectPODProperty(
            const FlyweightStringA& name
            , Getter<ObjectType, PropertyType> getter
            , ConstGetter<ObjectType, PropertyType> constGetter
            , Setter<ObjectType, PropertyType> setter
        );
        ~ReflectPODProperty() override = default;

    protected:
        virtual void* getPODPropertyInfoPtr() override { return static_cast<ReflectPODPropertyInfo<PropertyType>*>(this); }
        virtual const void* getPODPropertyInfoPtr() const override { return static_cast<const ReflectPODPropertyInfo<PropertyType>*>(this); }

    public:
        virtual void fromBianry(IReflectObject* object, const void* src) override;
        virtual void toBinary(const IReflectObject* object, IBuffer* outDst) const override;
        virtual void fromString(IReflectObject* object, const char* src, size_t strLen) override;
        virtual void toString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
    };
}
#include "ReflectPODProperty.hpp"