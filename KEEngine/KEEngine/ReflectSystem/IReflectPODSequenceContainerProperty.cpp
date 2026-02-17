#include "ReflectSystemPch.h"
#include "IReflectPODSequenceContainerProperty.h"

namespace ke
{
	IReflectPODSequenceContainerProperty::IReflectPODSequenceContainerProperty(const FlyweightStringA& name)
		: IReflectContainerProperty(name)
	{
	
	}

    IReflectPODSequenceContainerProperty* ReflectCastHelper<IReflectPODSequenceContainerProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODContainer)
        {
            return static_cast<IReflectPODSequenceContainerProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectPODSequenceContainerProperty* ReflectCastHelper<IReflectPODSequenceContainerProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODContainer)
        {
            return static_cast<const IReflectPODSequenceContainerProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
