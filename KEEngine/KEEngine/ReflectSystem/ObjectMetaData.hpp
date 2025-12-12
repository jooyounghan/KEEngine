#include "ObjectMetaData.h"

namespace ke
{
	//const SPropertyMetaData* ReflectMetaData::findProperty(const char* propertyName) const
//{
//	return nullptr;
//}

	//template<typename ObjectType>
	//template<typename PropertyType, typename ...Args>
	//void ReflectMetaData<ObjectType>::registerProperty(const FlyweightStringA& propertyName, Args... args)
	//{
	//	HashBucketFindResult<FlyweightStringA, uint32> findResult = _propertyMetaDataIndexMap.find(propertyName);
	//	KE_DEBUG_ASSERT(findResult._keyPtr == nullptr, "Property already registered in ReflectMetaData.");
	//	if (findResult._keyPtr == nullptr)
	//	{
	//		_propertyMetaDataList.pushBack(new PropertyMetaData<ObjectType, PropertyType>(args...));
	//		uint32 propertyIndex = static_cast<uint32>(_propertyMetaDataList.size() - 1);
	//		_propertyMetaDataIndexMap.insert(propertyName, propertyIndex);
	//	}
	//}

	//template<typename ObjectType>
	//void ReflectMetaData<ObjectType>::setDefaultValue(IReflectProperty* property) const
	//{
	//	const FlyweightStringA& propertyName = property->getPropertName();
	//	HashBucketFindResult<FlyweightStringA, uint32> findResult = _propertyMetaDataIndexMap.find(propertyName);
	//	if (findResult._keyPtr != nullptr)
	//	{
	//		const uint32& propertyIndex = *findResult._valuePtr;
	//		property->setFromBinary(_propertyMetaDataList[propertyIndex]->getDefaultValueBuffer());
	//	}
	//}
}