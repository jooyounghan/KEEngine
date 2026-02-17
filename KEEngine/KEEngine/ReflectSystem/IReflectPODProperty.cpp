#include "ReflectSystemPch.h"
#include "IReflectPODProperty.h"

namespace ke
{
	IReflectPODProperty::IReflectPODProperty(const FlyweightStringA& name) 
		: IReflectProperty(name) 
	{
	}

    IReflectPODProperty* ReflectCastHelper<IReflectPODProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::POD)
        {
            return static_cast<IReflectPODProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectPODProperty* ReflectCastHelper<IReflectPODProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::POD)
        {
            return static_cast<const IReflectPODProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
