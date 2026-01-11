#include "ReflectSystemPch.h"
#include "ReflectMetaData.h"

namespace ke
{
	ReflectMetaData::ReflectMetaData(const FlyweightStringA& ownerObjectName)
		: _ownerObjectName(ownerObjectName)
	{
	}

	IReflectProperty* ke::ReflectMetaData::getPropertyByName(const FlyweightStringA& name) const
	{
		auto it = _orderedPropertyMap.find(name);
		if (it != _orderedPropertyMap.end())
		{
			return it->second;
		}
		return nullptr;
	}
}
