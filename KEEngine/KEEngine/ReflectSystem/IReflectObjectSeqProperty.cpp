#include "ReflectSystemPch.h"
#include "IReflectObjectSeqProperty.h"

namespace ke
{
	IReflectObjectSeqProperty::IReflectObjectSeqProperty(const FlyweightStringA& name)
		: IReflectContainerProperty(name)
	{

	}

    IReflectObjectSeqProperty* ReflectCastHelper<IReflectObjectSeqProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObjectContainer)
        {
            return static_cast<IReflectObjectSeqProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectObjectSeqProperty* ReflectCastHelper<IReflectObjectSeqProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObjectContainer)
        {
            return static_cast<const IReflectObjectSeqProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
