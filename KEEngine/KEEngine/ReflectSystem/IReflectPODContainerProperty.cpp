#include "ReflectSystemPch.h"
#include "IReflectPODContainerProperty.h"

namespace ke
{
	IReflectPODContainerProperty::IReflectPODContainerProperty(const FlyweightStringA& name)
		: IReflectContainerProperty(name)
	{
	
	}

    IReflectPODContainerProperty* ReflectCastHelper<IReflectPODContainerProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODContainer)
        {
            return static_cast<IReflectPODContainerProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectPODContainerProperty* ReflectCastHelper<IReflectPODContainerProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODContainer)
        {
            return static_cast<const IReflectPODContainerProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
