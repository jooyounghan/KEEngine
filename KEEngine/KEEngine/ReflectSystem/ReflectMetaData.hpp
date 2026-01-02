#include "ReflectMetaData.h"

namespace ke
{
	template<typename ObjectType>
	template<typename PropertyType, typename ...Args>
	void ReflectMetaData<ObjectType>::registerPropertyMetaData(const FlyweightStringA& propertyName, Args... args)
	{
		if (_propertyMetaDataIndexMap.find(propertyName) != _propertyMetaDataIndexMap.end())
		{
			KE_DEBUG_ASSERT(false, "ReflectionDescriptor already registered in ReflectMetaData.");
		}
		else
		{
			uint32 propertyIndex = static_cast<uint32>(_propertyMetaDataList.size());
			_propertyMetaDataIndexMap.emplace(propertyName, propertyIndex);
			_propertyMetaDataList.push_back(std::make_unique<PropertyMetaData<ObjectType, PropertyType>>(args...));
		}
	}

	template<typename ObjectType>
	IPropertyMetaData<ObjectType>* ReflectMetaData<ObjectType>::getPropertyMetaData(const FlyweightStringA& propertyName) const
	{
		IPropertyMetaData<ObjectType>* result = nullptr;
		auto reflectionDescriptorIndex = _propertyMetaDataIndexMap.find(propertyName);
		if (reflectionDescriptorIndex == _propertyMetaDataIndexMap.end())
		{
			KE_DEBUG_ASSERT(false, "ReflectionDescriptor is not registered in ReflectMetaData.");
		}
		else
		{
			const std::unique_ptr<IPropertyMetaData<ObjectType>>& reflectionDescriptor = _propertyMetaDataList[reflectionDescriptorIndex->second];
			result = reflectionDescriptor.get();
		}
		return result;
	}

	template<typename ObjectType>
	void ReflectMetaData<ObjectType>::setDefaultValue(IReflectProperty* property) const
	{
		const FlyweightStringA& propertyName = property->getName();

		IPropertyMetaData<ObjectType>* propertyMetaData = getPropertyMetaData(propertyName);
		if (propertyMetaData != nullptr)
		{
			propertyMetaData->applyDefaultValue(property);
		}
	}
	template<typename ObjectType>
	void ReflectMetaData<ObjectType>::setDefaultValues(ObjectType* object) const
	{
		for (std::unique_ptr<IPropertyMetaData<ObjectType>> const& propertyMetaData : _propertyMetaDataList)
		{
			IReflectProperty* property = propertyMetaData->getFromObject(object);
			propertyMetaData->applyDefaultValue(property);
		}
	}
}