#include "ReflectSystemPch.h"
#include "IReflectSequenceProperty.h"

namespace ke
{
	IReflectSequenceProperty::IReflectSequenceProperty(const FlyweightStringA& name)
		: IReflectContainerProperty(name)
	{
	
	}

    IReflectSequenceProperty* ReflectCastHelper<IReflectSequenceProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODContainer)
        {
            return static_cast<IReflectSequenceProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectSequenceProperty* ReflectCastHelper<IReflectSequenceProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODContainer)
        {
            return static_cast<const IReflectSequenceProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
