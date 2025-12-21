#include "ReflectMetaData.h"

namespace ke
{
	template<typename ObjectType>
	template<typename PropertyType, typename ...Args>
	void ReflectMetaData<ObjectType>::registerReflectionDescirptor(const FlyweightStringA& propertyName, Args... args)
	{
		if (_reflectionDescriptorIndexMap.find(propertyName) != _reflectionDescriptorIndexMap.end())
		{
			KE_DEBUG_ASSERT(false, "ReflectionDescriptor already registered in ReflectMetaData.");
		}
		else
		{
			uint32 propertyIndex = static_cast<uint32>(_reflectionDescriptorList.size());
			_reflectionDescriptorIndexMap.emplace(propertyName, propertyIndex);
			_reflectionDescriptorList.push_back(std::make_unique<ReflectDescriptor<ObjectType, PropertyType>>(args...));
		}
	}

	template<typename ObjectType>
	IReflectionDecriptor<ObjectType>* ReflectMetaData<ObjectType>::getReflectionDescriptor(const FlyweightStringA& propertyName) const
	{
		IReflectionDecriptor<ObjectType>* result = nullptr;
		auto reflectionDescriptorIndex = _reflectionDescriptorIndexMap.find(propertyName);
		if (reflectionDescriptorIndex == _reflectionDescriptorIndexMap.end())
		{
			KE_DEBUG_ASSERT(false, "ReflectionDescriptor is not registered in ReflectMetaData.");
		}
		else
		{
			const std::unique_ptr<IReflectionDecriptor<ObjectType>>& reflectionDescriptor = _reflectionDescriptorList[reflectionDescriptorIndex->second];
			result = reflectionDescriptor.get();
		}
		return result;
	}

	template<typename ObjectType>
	void ReflectMetaData<ObjectType>::setDefaultValue(IReflection* property) const
	{
		const FlyweightStringA& propertyName = property->getName();

		IReflectionDecriptor<ObjectType>* reflectionDescriptor = getReflectionDescriptor(propertyName);
		if (reflectionDescriptor != nullptr)
		{
			reflectionDescriptor->applyDefaultValue(property);
		}
	}
	template<typename ObjectType>
	void ReflectMetaData<ObjectType>::setDefaultValues(ObjectType* object) const
	{
		for (std::unique_ptr<IReflectionDecriptor<ObjectType>> const& descriptor : _reflectionDescriptorList)
		{
			IReflection* property = descriptor->getFromObject(object);
			descriptor->applyDefaultValue(property);
		}
	}
}