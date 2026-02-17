#include "ReflectSystemPch.h"
#include "IReflectObjectProperty.h"

namespace ke
{
	IReflectObjectProperty::IReflectObjectProperty(const FlyweightStringA& name)
		: IReflectProperty(name)
	{
	}

    IReflectObjectProperty* ReflectCastHelper<IReflectObjectProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObject)
        {
            return static_cast<IReflectObjectProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectObjectProperty* ReflectCastHelper<IReflectObjectProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObject)
        {
            return static_cast<const IReflectObjectProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
