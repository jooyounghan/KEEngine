#pragma once
#include "PropertyMetaData.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectMetaData
	{
	public:
		ReflectMetaData() = default;
		NONCOPYABLE(ReflectMetaData);

	public:
		std::unordered_map<FlyweightStringA, uint32, HASH(FlyweightStringA)>	_propertyMetaDataIndexMap;
		std::vector<std::unique_ptr<IPropertyMetaData<ObjectType>>>				_propertyMetaDataList;

	public:
		template<typename PropertyType, typename ...Args>
		void registerPropertyMetaData(const FlyweightStringA& propertyName, Args... args);

	public:
		const std::vector<std::unique_ptr<IPropertyMetaData<ObjectType>>>& getPropertyMetaDataList() const { return _propertyMetaDataList; };

	public:
		IPropertyMetaData<ObjectType>*	getPropertyMetaData(const FlyweightStringA& propertyName) const;
		void							setDefaultValue(IReflectProperty* property) const;
		void							setDefaultValues(ObjectType* object) const;
	};
}
#include "ReflectMetaData.hpp"