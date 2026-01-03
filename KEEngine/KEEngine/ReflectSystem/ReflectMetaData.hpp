#include "ReflectMetaData.h"

namespace ke
{
	template<typename ObjectType>
	template<typename PropertyType, typename ...Args>
	void ReflectMetaData<ObjectType>::registerPropertyMetaData(const FlyweightStringA& propertyName, Args... args)
	{
		if (_propertyMetaDataIndexMap.find(propertyName) != _propertyMetaDataIndexMap.end())
		{
			KE_DEBUG_ASSERT(false, "PropertyMetaData already registered in ReflectMetaData.");
		}
		else
		{
			uint32 propertyIndex = static_cast<uint32>(_propertyMetaDataList.size());
			_propertyMetaDataIndexMap.emplace(propertyName, propertyIndex);
			_propertyMetaDataList.push_back(std::make_unique<PropertyMetaData<ObjectType, PropertyType>>(args...));
		}
	}
}