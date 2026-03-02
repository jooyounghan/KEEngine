#include "ReflectSystemPch.h"
#include "IReflectSequenceProperty.h"

namespace ke
{
	IReflectSequenceProperty::IReflectSequenceProperty(const FlyweightStringA& name)
		: IReflectSequenceContainerProperty(name)
	{
	
	}

    IReflectSequenceProperty* ReflectCastHelper<IReflectSequenceProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODSequenceContainer)
        {
            return static_cast<IReflectSequenceProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectSequenceProperty* ReflectCastHelper<IReflectSequenceProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODSequenceContainer)
        {
            return static_cast<const IReflectSequenceProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
