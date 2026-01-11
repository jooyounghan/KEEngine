#pragma once
#include "ReflectProperty.h"
#include <vector>
#include <map>

namespace ke
{
	class ReflectMetaData
	{
	public:
		ReflectMetaData(const FlyweightStringA& ownerObjectName);
		~ReflectMetaData() = default;

	private:
		std::vector<std::unique_ptr<IReflectProperty>> _properties;

	private:
		std::map<FlyweightStringA, IReflectProperty*> _orderedPropertyMap;

	public:
		template<typename ObjectType, typename PropertyType>
		void addProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		)
		{
			std::unique_ptr<IReflectProperty> propertyPtr = std::make_unique <ReflectProperty<ObjectType, PropertyType>>(
				name
				, getter
				, constGetter
				, setter
			);
			IReflectProperty* property = propertyPtr.get();
			_properties.emplace_back(std::move(propertyPtr));
			_orderedPropertyMap.emplace(name, property);
		}

	public:
		IReflectProperty* getPropertyByName(const FlyweightStringA& name) const;
		inline const FlyweightStringA& getOwnerObjectName() const { return _ownerObjectName; }

	private:
		FlyweightStringA _ownerObjectName;
	};
}