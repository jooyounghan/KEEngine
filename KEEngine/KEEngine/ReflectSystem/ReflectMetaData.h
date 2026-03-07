#pragma once
#include "ReflectProperty.h"
#include "ReflectObjectProperty.h"
#include "ReflectSequenceProperty.h"
#include "ReflectObjectSequenceProperty.h"
#include "ReflectKeyValueProperty.h"
#include "ReflectObjectKeyValueProperty.h"

namespace ke
{
	class ReflectMetaData
	{
	public:
		ReflectMetaData(const FlyweightStringA& ownerObjectName);
		~ReflectMetaData() = default;

	public:
		template<typename ObjectType, typename PropertyType>
		void addReflectProperty(
			const FlyweightStringA& name,
			EReflectUIOption uiOption,
			REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, PropertyType)
		);

		template<typename ObjectType, typename PropertyType>
		void addReflectProperty(
			const FlyweightStringA& name,
			EReflectUIOption uiOption,
			REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, PropertyType),
			const PropertyType& defaultValue
		);

		template<typename ObjectType, typename PropertyType>
		void addReflectObjectProperty(
			const FlyweightStringA& name,
			EReflectUIOption uiOption,
			REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, PropertyType)
		);

		template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
		void addReflectSequenceProperty(
			const FlyweightStringA& name,
			EReflectUIOption uiOption,
			REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, ContainerType<PropertyType>)
		);

		template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
		void addReflectSequenceProperty(
			const FlyweightStringA& name,
			EReflectUIOption uiOption,
			REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, ContainerType<PropertyType>),
			ContainerType<PropertyType>&& defaultValue
		);

		template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
		void addReflectObjectSequenceProperty(
			const FlyweightStringA& name,
			EReflectUIOption uiOption,
			REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, ContainerType<PropertyType>)
		);

	public:
		IReflectProperty*							getPropertyByName(const FlyweightStringA& name) const;
		inline const FlyweightStringA&				getOwnerObjectName() const { return _ownerObjectName; }
		inline const OwnerVector<IReflectProperty>& getAllProperties() const { return _properties; }

	private:
		OwnerVector<IReflectProperty>					_properties;
		std::map<FlyweightStringA, IReflectProperty*>	_orderedPropertyMap;
		FlyweightStringA								_ownerObjectName;
	};
}
#include "ReflectMetaData.hpp"