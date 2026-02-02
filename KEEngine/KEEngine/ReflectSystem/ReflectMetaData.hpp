namespace ke
{
#define REFLECT_OBJECT ReflectObjectProperty<ObjectType, PropertyType>
#define REFLECT_POD	  ReflectPODProperty<ObjectType, PropertyType>

	template<typename ObjectType, typename PropertyType>
	void ReflectMetaData::addProperty(const FlyweightStringA& name, Getter<ObjectType, PropertyType> getter, ConstGetter<ObjectType, PropertyType> constGetter, Setter<ObjectType, PropertyType> setter)
	{
		IReflectProperty* property = nullptr;
		if constexpr (IS_BASE_OF(IReflectObject, PropertyType))
		{
			property = _properties.push_back<REFLECT_OBJECT>(name, getter, constGetter, setter);
		}
		else
		{
			property = _properties.push_back<REFLECT_POD>(name, getter, constGetter, setter);
		}
		_orderedPropertyMap.emplace(name, property);
	}

#undef REFLECT_OBJECT
#undef REFLECT_POD
}