namespace ke
{
	template<typename ObjectType, typename PropertyType>
	void ReflectMetaData::addPODProperty(const FlyweightStringA& name, Getter<ObjectType, PropertyType> getter, ConstGetter<ObjectType, PropertyType> constGetter, Setter<ObjectType, PropertyType> setter)
	{
		IReflectProperty* property = _properties.push_back<ReflectPODProperty<ObjectType, PropertyType>>(name, getter, constGetter, setter);
		_orderedPropertyMap.emplace(name, property);
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectMetaData::addReflectObjectProperty(const FlyweightStringA & name, Getter<ObjectType, PropertyType> getter, ConstGetter<ObjectType, PropertyType> constGetter, Setter<ObjectType, PropertyType> setter)
	{
		IReflectProperty* property = _properties.push_back<ReflectObjectProperty<ObjectType, PropertyType>>(name, getter, constGetter, setter);
		_orderedPropertyMap.emplace(name, property);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectMetaData::addReflectPODSeqProperty(const FlyweightStringA & name, Getter<ObjectType, ContainerType<PropertyType>> getter, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter, Setter<ObjectType, ContainerType<PropertyType>> setter)
	{
		IReflectProperty* property = _properties.push_back<ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>>(name, getter, constGetter, setter);
		_orderedPropertyMap.emplace(name, property);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectMetaData::addReflectObjectSeqProperty(const FlyweightStringA & name, Getter<ObjectType, ContainerType<PropertyType>> getter, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter, Setter<ObjectType, ContainerType<PropertyType>> setter)
	{
		IReflectProperty* property = _properties.push_back<ReflectObjectSeqProperty<ObjectType, ContainerType, PropertyType>>(name, getter, constGetter, setter);
		_orderedPropertyMap.emplace(name, property);
	}
}