namespace ke
{
#define REFLECT_OBJECT ReflectObjectProperty<ObjectType, PropertyType>
#define REFLECT_POD	  ReflectPODProperty<ObjectType, PropertyType>

	template<typename ObjectType, typename PropertyType>
	void ReflectMetaData::addProperty(const FlyweightStringA& name, Getter<ObjectType, PropertyType> getter, ConstGetter<ObjectType, PropertyType> constGetter, Setter<ObjectType, PropertyType> setter)
	{
		PTR(IReflectProperty) propertyPtr;
		if constexpr (IS_BASE_OF(IReflectObject, PropertyType))
		{
			propertyPtr = MAKE_PTR(REFLECT_OBJECT, name, getter, constGetter, setter);
		}
		else
		{
			propertyPtr = MAKE_PTR(REFLECT_POD, name, getter, constGetter, setter);
		}

		IReflectProperty* property = propertyPtr.get();
		_properties.emplace_back(std::move(propertyPtr));
		_orderedPropertyMap.emplace(name, property);
	}

#undef REFLECT_OBJECT
#undef REFLECT_POD
}