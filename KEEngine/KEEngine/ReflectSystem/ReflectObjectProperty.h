#pragma once
#include "IReflectObjectProperty.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectObjectProperty : public IReflectObjectProperty
	{
	public:
        ReflectObjectProperty(
            const FlyweightStringA& name
            , Getter<ObjectType, PropertyType> getter
            , ConstGetter<ObjectType, PropertyType> constGetter
            , Setter<ObjectType, PropertyType> setter
        );
        ~ReflectObjectProperty() override = default;

    public:
        virtual IReflectObject*         getReflectObject(IReflectObject* parentReflectObject) override;
        virtual const IReflectObject*   getReflectObject(const IReflectObject* parentReflectObject) const override;
	};
}
#include "ReflectObjectProperty.hpp"