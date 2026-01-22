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
		std::vector<PTR(IReflectProperty)> _properties;

	private:
		std::map<FlyweightStringA, IReflectProperty*> _orderedPropertyMap;

	public:
		template<typename ObjectType, typename PropertyType>
		void addProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);

	public:
		IReflectProperty* getPropertyByName(const FlyweightStringA& name) const;
		inline const FlyweightStringA& getOwnerObjectName() const { return _ownerObjectName; }

	public:
		inline const std::vector<PTR(IReflectProperty)>& getAllProperties() const { return _properties; }

	private:
		FlyweightStringA _ownerObjectName;
	};
}
#include "ReflectMetaData.hpp"