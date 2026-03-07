#include "ReflectMetaData.h"
namespace ke
{
	template<typename ObjectType, typename PropertyType>
	void ReflectMetaData::addReflectProperty(
		const FlyweightStringA& name, 
		EReflectUIOption uiOption,
		REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, PropertyType)
	)
	{
		IReflectProperty* property = _properties.push_back<ReflectProperty<ObjectType, PropertyType>>(name, getter, constGetter, setter);
		property->setUIOption(uiOption);
		_orderedPropertyMap.emplace(name, property);
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectMetaData::addReflectProperty(
		const FlyweightStringA& name,
		EReflectUIOption uiOption,
		REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, PropertyType),
		const PropertyType& defaultPropertyValue
	)
	{
		IReflectProperty* property = _properties.push_back<ReflectProperty<ObjectType, PropertyType>>(name, getter, constGetter, setter);
		property->setUIOption(uiOption);
		ReflectProperty<ObjectType, PropertyType>* reflectProperty = static_cast<ReflectProperty<ObjectType, PropertyType>*>(property);
		reflectProperty->setDefaultValue(defaultPropertyValue);
		_orderedPropertyMap.emplace(name, property);

	}

	template<typename ObjectType, typename PropertyType>
	void ReflectMetaData::addReflectObjectProperty(
		const FlyweightStringA & name,
		EReflectUIOption uiOption,
		REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, PropertyType)
	)
	{
		IReflectProperty* property = _properties.push_back<ReflectObjectProperty<ObjectType, PropertyType>>(name, getter, constGetter, setter);
		_orderedPropertyMap.emplace(name, property);
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	void ReflectMetaData::addReflectSequenceProperty(
		const FlyweightStringA & name, 
		EReflectUIOption uiOption,
		REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, ContainerType<PropertyType>)
	)
	{
		IReflectProperty* property = _properties.push_back<ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>>(name, getter, constGetter, setter);
		property->setUIOption(uiOption);
		_orderedPropertyMap.emplace(name, property);
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	void ReflectMetaData::addReflectSequenceProperty(
		const FlyweightStringA& name,
		EReflectUIOption uiOption,
		REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, ContainerType<PropertyType>),
		ContainerType<PropertyType>&& defaultValue
	)
	{
		IReflectProperty* property = _properties.push_back<ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>>(name, getter, constGetter, setter);
		property->setUIOption(uiOption);
		ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>* reflectProperty = static_cast<ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>*>(property);
		reflectProperty->setDefaultValue(std::forward<ContainerType<PropertyType>>(defaultValue));
		_orderedPropertyMap.emplace(name, property);
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	void ReflectMetaData::addReflectObjectSequenceProperty(
		const FlyweightStringA & name,
		EReflectUIOption uiOption,
		REFLECT_PROPERTY_ACCESSOR_ARGUMENTS(ObjectType, ContainerType<PropertyType>)
	)
	{
		IReflectProperty* property = _properties.push_back<ReflectObjectSequenceProperty<ObjectType, ContainerType, PropertyType>>(name, getter, constGetter, setter);
		property->setUIOption(uiOption);
		_orderedPropertyMap.emplace(name, property);
	}
}