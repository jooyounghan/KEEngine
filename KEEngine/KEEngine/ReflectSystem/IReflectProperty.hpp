namespace ke
{
	// Template specializations for safe type casting
	template<typename T>
	T* IReflectProperty::as()
	{
		// Default implementation returns nullptr
		return nullptr;
	}

	template<typename T>
	const T* IReflectProperty::as() const
	{
		// Default implementation returns nullptr
		return nullptr;
	}

	// Specialization for IReflectPODProperty
	template<>
	inline IReflectPODProperty* IReflectProperty::as<IReflectPODProperty>()
	{
		return asIReflectPODProperty();
	}

	template<>
	inline const IReflectPODProperty* IReflectProperty::as<IReflectPODProperty>() const
	{
		return asIReflectPODProperty();
	}

	// Specialization for IReflectVectorProperty
	template<>
	inline IReflectVectorProperty* IReflectProperty::as<IReflectVectorProperty>()
	{
		return asIReflectVectorProperty();
	}

	template<>
	inline const IReflectVectorProperty* IReflectProperty::as<IReflectVectorProperty>() const
	{
		return asIReflectVectorProperty();
	}

	// Specialization for IReflectEnumProperty
	template<>
	inline IReflectEnumProperty* IReflectProperty::as<IReflectEnumProperty>()
	{
		return asIReflectEnumProperty();
	}

	template<>
	inline const IReflectEnumProperty* IReflectProperty::as<IReflectEnumProperty>() const
	{
		return asIReflectEnumProperty();
	}

	// Specialization for IReflectObjectProperty
	template<>
	inline IReflectObjectProperty* IReflectProperty::as<IReflectObjectProperty>()
	{
		return asIReflectObjectProperty();
	}

	template<>
	inline const IReflectObjectProperty* IReflectProperty::as<IReflectObjectProperty>() const
	{
		return asIReflectObjectProperty();
	}

	template<typename ObjectType, typename PropertyType>
	ReflectPropertyBase<ObjectType, PropertyType>::ReflectPropertyBase(
		const FlyweightStringA& name
		, Getter<ObjectType, PropertyType> getter
		, ConstGetter<ObjectType, PropertyType> constGetter
		, Setter<ObjectType, PropertyType> setter
	)
		: IReflectProperty(name)
		, _getter(getter)
		, _constGetter(constGetter)
		, _setter(setter)
	{
		STATIC_ASSERT_IS_BASE_OF(IReflectObject, ObjectType);
	}
}