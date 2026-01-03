#pragma once
#include "PropertyMetaData.h"

namespace ke
{
	template<typename ObjectType>
	class ReflectMetaData
	{
		template<typename Object>
		friend class ReflectObject;

	public:
		ReflectMetaData() = default;
		NONCOPYABLE(ReflectMetaData);

	public:
		using PropertyMetaDataIndexMap = std::unordered_map<FlyweightStringA, uint32, HASH(FlyweightStringA)>;
		using PropertyMetaDataList = std::vector<std::unique_ptr<IPropertyMetaData<ObjectType>>>;

	protected:
		PropertyMetaDataIndexMap	_propertyMetaDataIndexMap;
		PropertyMetaDataList		_propertyMetaDataList;

	public:
		template<typename PropertyType, typename ...Args>
		void registerPropertyMetaData(const FlyweightStringA& propertyName, Args... args);

	public:
		const PropertyMetaDataList& getPropertyMetaDataList() const { return _propertyMetaDataList; };
	};
}
#include "ReflectMetaData.hpp"