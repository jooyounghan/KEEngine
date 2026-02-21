#include "ReflectSystemPch.h"
#include "IReflectPODSeqProperty.h"
#include "IReflectPODProperty.h"

namespace ke
{
	IReflectPODSeqProperty::IReflectPODSeqProperty(const FlyweightStringA& name)
		: IReflectContainerProperty(name)
	{
	
	}

	void IReflectPODSeqProperty::fromBianry(const size_t index, IReflectObject* object, const void* src)
	{
		getElementProperty(index, object)->fromBianry(object, src);
	}

	void IReflectPODSeqProperty::toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const
	{
		getElementProperty(index, object)->toBinary(object, outDst);
	}

	void IReflectPODSeqProperty::fromString(const size_t index, IReflectObject* object, const char* src, size_t strlen)
	{
		getElementProperty(index, object)->fromString(object, src, strlen);
	}

	void IReflectPODSeqProperty::toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		getElementProperty(index, object)->toString(object, outStringBuffer);
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
