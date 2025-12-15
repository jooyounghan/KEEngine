#include "ObjectMetaData.h"

namespace ke
{
	template<typename ObjectType>
	template<typename PropertyType, typename ...Args>
	void ObjectMetaData<ObjectType>::registerProperty(const FlyweightStringA& propertyName, Args... args)
	{
		if (_metaDataIndexMap.find(propertyName) != _metaDataIndexMap.end())
		{
			KE_DEBUG_ASSERT(false, "Property already registered in ObjectMetaData.");
		}
		else
		{
			uint32 propertyIndex = static_cast<uint32>(_metaDataList.size());
			_metaDataIndexMap.emplace(propertyName, propertyIndex);
			_metaDataList.push_back(std::make_unique<PropertyMetaData<ObjectType, PropertyType>>(args...));
		}
	}

	template<typename ObjectType>
	IPropertyMetaData<ObjectType>* ObjectMetaData<ObjectType>::getPropertyMetaData(const FlyweightStringA& propertyName)
	{
		IPropertyMetaData<ObjectType>* result = nullptr;
		auto metaDataIndex = _metaDataIndexMap.find(propertyName);
		if (metaDataIndex == _metaDataIndexMap.end())
		{
			KE_DEBUG_ASSERT(false, "Property is not registered in ObjectMetaData.");
		}
		else
		{
			std::unique_ptr<IPropertyMetaData<ObjectType>>& propertyMetaData = _metaDataList[metaDataIndex->second];
			result = propertyMetaData.get();
		}
		return result;
	}

	template<typename ObjectType>
	void ObjectMetaData<ObjectType>::setDefaultValue(IReflectProperty* property) const
	{
		const FlyweightStringA& propertyName = property->getPropertName();

		IPropertyMetaData<ObjectType>* propertyMetaData = getPropertyMetaData(propertyName);
		if (propertyMetaData != nullptr)
		{
			propertyMetaData->applyDefaultValue(property);
		}
	}
}