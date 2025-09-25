#include "ReflectMetaData.h"

namespace ke
{
	void ReflectMetaData::registerProperty(EPropertyType type, IReflectProperty* property)
	{
		SPropertyMetaData meta;
		meta._propertyType = type;
		property->getToBinary(&meta._defaultValueBuffer);
		_propertyMetaDatas.pushBack(move(meta));
	}

	const SPropertyMetaData* ReflectMetaData::findProperty(const char* propertyName) const
	{
		return nullptr;
	}

	void ReflectMetaData::setDefaultValue(IReflectProperty* property) const
	{
	}
}
