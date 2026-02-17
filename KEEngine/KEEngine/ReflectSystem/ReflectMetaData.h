#pragma once
#include "ReflectPODProperty.h"
#include "ReflectObjectProperty.h"
#include "ReflectPODSequenceContainerProperty.h"
#include "ReflectObjectSequenceContainerProperty.h"

namespace ke
{
	class ReflectMetaData
	{
	public:
		ReflectMetaData(const FlyweightStringA& ownerObjectName);
		~ReflectMetaData() = default;

	public:
		template<typename ObjectType, typename PropertyType>
		void addPODProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);

		template<typename ObjectType, typename PropertyType>
		void addReflectObjectProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);

		template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
		void addPODContainerProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<PropertyType>> getter
			, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter
			, Setter<ObjectType, ContainerType<PropertyType>> setter
		);

		template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
		void addReflectObjectContainerProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<PropertyType>> getter
			, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter
			, Setter<ObjectType, ContainerType<PropertyType>> setter
		);

	public:
		IReflectProperty* getPropertyByName(const FlyweightStringA& name) const;
		inline const FlyweightStringA& getOwnerObjectName() const { return _ownerObjectName; }
		inline const OwnerVector<IReflectProperty>& getAllProperties() const { return _properties; }

	private:
		OwnerVector<IReflectProperty> _properties;
		std::map<FlyweightStringA, IReflectProperty*> _orderedPropertyMap;
		FlyweightStringA _ownerObjectName;
	};
}
#include "ReflectMetaData.hpp"