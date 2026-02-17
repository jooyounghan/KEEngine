#include "ReflectSystemPch.h"
#include "IReflectObjectContainerProperty.h"

namespace ke
{
	IReflectObjectContainerProperty::IReflectObjectContainerProperty(const FlyweightStringA& name)
		: IReflectProperty(name)
	{

	}

    IReflectObjectContainerProperty* ReflectCastHelper<IReflectObjectContainerProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObjectContainer)
        {
            return static_cast<IReflectObjectContainerProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectObjectContainerProperty* ReflectCastHelper<IReflectObjectContainerProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObjectContainer)
        {
            return static_cast<const IReflectObjectContainerProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
