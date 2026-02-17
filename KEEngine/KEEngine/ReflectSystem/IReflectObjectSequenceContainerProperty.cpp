#include "ReflectSystemPch.h"
#include "IReflectObjectSequenceContainerProperty.h"

namespace ke
{
	IReflectObjectSeqeunceContainerProperty::IReflectObjectSeqeunceContainerProperty(const FlyweightStringA& name)
		: IReflectContainerProperty(name)
	{

	}

    IReflectObjectSeqeunceContainerProperty* ReflectCastHelper<IReflectObjectSeqeunceContainerProperty>::cast(IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObjectContainer)
        {
            return static_cast<IReflectObjectSeqeunceContainerProperty*>(prop->getInterface());
        }
        return nullptr;
    }

    const IReflectObjectSeqeunceContainerProperty* ReflectCastHelper<IReflectObjectSeqeunceContainerProperty>::cast(const IReflectProperty* prop)
    {
        if (prop && prop->getType() == EReflectPropertyType::ReflectObjectContainer)
        {
            return static_cast<const IReflectObjectSeqeunceContainerProperty*>(prop->getInterface());
        }
        return nullptr;
    }
}
