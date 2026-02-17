#include "ReflectSystemPch.h"
#include "IReflectPODSeqProperty.h"

namespace ke
{
	IReflectPODSeqProperty::IReflectPODSeqProperty(const FlyweightStringA& name)
		: IReflectContainerProperty(name)
	{
	
	}

    IReflectPODSeqProperty* ReflectCastHelper<IReflectPODSeqProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODContainer)
        {
            return static_cast<IReflectPODSeqProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectPODSeqProperty* ReflectCastHelper<IReflectPODSeqProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::PODContainer)
        {
            return static_cast<const IReflectPODSeqProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
