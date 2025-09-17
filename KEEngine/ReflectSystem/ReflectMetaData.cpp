#include "ReflectMetaData.h"

namespace ke
{
	void ReflectMetaData::registerProperty(EPropertyType type, IReflectProperty* property)
	{
	}

	const SPropertyMetaData* ReflectMetaData::findProperty(const char* propertyName) const
	{
		return nullptr;
	}

	void ReflectMetaData::setDefaultValue(IReflectProperty* property) const
	{
	}
}
