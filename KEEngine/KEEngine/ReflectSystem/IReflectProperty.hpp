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
		if (getPropertyType() == EReflectPropertyType::POD)
		{
			return dynamic_cast<IReflectPODProperty*>(this);
		}
		return nullptr;
	}

	template<>
	inline const IReflectPODProperty* IReflectProperty::as<IReflectPODProperty>() const
	{
		if (getPropertyType() == EReflectPropertyType::POD)
		{
			return dynamic_cast<const IReflectPODProperty*>(this);
		}
		return nullptr;
	}

	// Specialization for IReflectVectorProperty
	template<>
	inline IReflectVectorProperty* IReflectProperty::as<IReflectVectorProperty>()
	{
		if (getPropertyType() == EReflectPropertyType::Vector)
		{
			return dynamic_cast<IReflectVectorProperty*>(this);
		}
		return nullptr;
	}

	template<>
	inline const IReflectVectorProperty* IReflectProperty::as<IReflectVectorProperty>() const
	{
		if (getPropertyType() == EReflectPropertyType::Vector)
		{
			return dynamic_cast<const IReflectVectorProperty*>(this);
		}
		return nullptr;
	}

	// Specialization for IReflectEnumProperty
	template<>
	inline IReflectEnumProperty* IReflectProperty::as<IReflectEnumProperty>()
	{
		if (getPropertyType() == EReflectPropertyType::Enum)
		{
			return dynamic_cast<IReflectEnumProperty*>(this);
		}
		return nullptr;
	}

	template<>
	inline const IReflectEnumProperty* IReflectProperty::as<IReflectEnumProperty>() const
	{
		if (getPropertyType() == EReflectPropertyType::Enum)
		{
			return dynamic_cast<const IReflectEnumProperty*>(this);
		}
		return nullptr;
	}

	// Specialization for IReflectObjectProperty
	template<>
	inline IReflectObjectProperty* IReflectProperty::as<IReflectObjectProperty>()
	{
		if (getPropertyType() == EReflectPropertyType::Object)
		{
			return dynamic_cast<IReflectObjectProperty*>(this);
		}
		return nullptr;
	}

	template<>
	inline const IReflectObjectProperty* IReflectProperty::as<IReflectObjectProperty>() const
	{
		if (getPropertyType() == EReflectPropertyType::Object)
		{
			return dynamic_cast<const IReflectObjectProperty*>(this);
		}
		return nullptr;
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