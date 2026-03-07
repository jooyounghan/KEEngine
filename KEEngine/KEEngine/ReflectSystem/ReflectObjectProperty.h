#pragma once
#include "IReflectObjectProperty.h"
#include "ReflectPropertyAccessor.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectObjectProperty : public IReflectObjectProperty, public ReflectPropertyAccessor<ObjectType, PropertyType>
	{
	public:
        ReflectObjectProperty(
            const FlyweightStringA& name,
            REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, PropertyType)
        );
        ~ReflectObjectProperty() override = default;

    public:
        virtual IReflectObject*         getReflectObject(IReflectObject* parentReflectObject) override;
        virtual const IReflectObject*   getReflectObject(const IReflectObject* parentReflectObject) const override;
	};
}
#include "ReflectObjectProperty.hpp"