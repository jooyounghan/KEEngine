#pragma once
#include "ReflectionDescriptor.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectMetaData
	{
	public:
		ReflectMetaData() = default;
		NONCOPYABLE(ReflectMetaData);

	public:
		std::unordered_map<FlyweightStringA, uint32, HASH(FlyweightStringA)>	_reflectionDescriptorIndexMap;
		std::vector<std::unique_ptr<IReflectionDecriptor<ObjectType>>>			_reflectionDescriptorList;

	public:
		template<typename PropertyType, typename ...Args>
		void registerReflectionDescirptor(const FlyweightStringA& propertyName, Args... args);

	public:
		const std::vector<std::unique_ptr<IReflectionDecriptor<ObjectType>>>& getReflectionDescriptorList() const { return _reflectionDescriptorList; };

	public:
		IReflectionDecriptor<ObjectType>*	getReflectionDescriptor(const FlyweightStringA& propertyName) const;
		void								setDefaultValue(IReflection* property) const;
		void								setDefaultValues(ObjectType* object) const;
	};
}
#include "ReflectMetaData.hpp"