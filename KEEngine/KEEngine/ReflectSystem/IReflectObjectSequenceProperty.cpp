#include "ReflectSystemPch.h"
#include "IReflectObjectSequenceProperty.h"

namespace ke
{
	IReflectObjectSequenceProperty::IReflectObjectSequenceProperty(const FlyweightStringA& name)
		: IReflectContainerProperty(name)
	{

	}

    IReflectObjectSequenceProperty* ReflectCastHelper<IReflectObjectSequenceProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObjectContainer)
        {
            return static_cast<IReflectObjectSequenceProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectObjectSequenceProperty* ReflectCastHelper<IReflectObjectSequenceProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObjectContainer)
        {
            return static_cast<const IReflectObjectSequenceProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
