#include "ReflectObjectProperty.h"
namespace ke
{
    template<typename ObjectType, typename PropertyType>
    ReflectObjectProperty<ObjectType, PropertyType>::ReflectObjectProperty(
        const FlyweightStringA& name, 
        Getter<ObjectType, PropertyType> getter, 
        ConstGetter<ObjectType, PropertyType> constGetter, 
        Setter<ObjectType, PropertyType> setter
    )
		: IReflectObjectProperty(name), ReflectPropertyAccessor<ObjectType, PropertyType>(getter, constGetter, setter)
    {
        STATIC_ASSERT_IS_BASE_OF(IReflectObject, PropertyType);
    }

    template<typename ObjectType, typename PropertyType>
    IReflectObject* ReflectObjectProperty<ObjectType, PropertyType>::getReflectObject(IReflectObject* parentReflectObject) 
    {
        return static_cast<IReflectObject*>(&this->get(parentReflectObject)); 
    }

    template<typename ObjectType, typename PropertyType>
    const IReflectObject* ReflectObjectProperty<ObjectType, PropertyType>::getReflectObject(const IReflectObject* parentReflectObject) const 
    { 
        return static_cast<const IReflectObject*>(&this->get(parentReflectObject)); 
    }
}