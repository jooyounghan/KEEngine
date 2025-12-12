#pragma once
#include "ReflectSystemPch.h"
#include "FlyweightString.h"

namespace ke
{
	//template<typename ObjectType>
	//class ObjectMetaData
	//{
	//public:
	//	ObjectMetaData() = default;
	//	NONCOPYABLE(ObjectMetaData);

	//public:
	//	std::unordered_map<FlyweightStringA, uint32, HASH(FlyweightStringA)>	_propertyMetaDataIndexMap;
	//	std::vector<IPropertyMetaData<ObjectType>*>								_propertyMetaDataList;

	//public:
	//	template<typename PropertyType, typename ...Args>
	//	void registerProperty(const FlyweightStringA& propertyName, Args... args);

	//public:
	//	void setDefaultValue(IReflectProperty* property) const;
	//};
}
#include "ObjectMetaData.h"