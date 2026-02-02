namespace ke
{
	template<typename ObjectType, typename PropertyType>
	void ReflectMetaData::addProperty(const FlyweightStringA& name, Getter<ObjectType, PropertyType> getter, ConstGetter<ObjectType, PropertyType> constGetter, Setter<ObjectType, PropertyType> setter)
	{
		IReflectProperty* property = nullptr;
		if constexpr (IS_BASE_OF(IReflectObject, PropertyType))
		{
			property = _properties.push_back<ReflectObjectProperty<ObjectType, PropertyType>>(
				name, getter, constGetter, setter
			);
		}
		else
		{
			property = _properties.push_back<ReflectPODProperty<ObjectType, PropertyType>>(
				name, getter, constGetter, setter
			);
		}
		_orderedPropertyMap.emplace(name, property);
	}
}