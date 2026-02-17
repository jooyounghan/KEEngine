namespace ke
{
	template<typename T>
	inline const void* IReflectStaticTypeId::getStaticTypeId()
	{
		static char staticTypeId;
		return &staticTypeId;
	}

	template<typename PropertyType, template<typename PropertyType> typename ReflectType>
	ReflectType<PropertyType>* IReflectStaticTypeId::getBase()
	{
		if (this->getTypeId() == getStaticTypeId<PropertyType>())
		{
			return static_cast<ReflectType<PropertyType>*>(this);
		}
	}

	template<typename T>
	T* IReflectProperty::as()
	{
		return ReflectCastHelper<T>::cast(this);
	}

	template<typename T>
	const T* IReflectProperty::as() const
	{
		return ReflectCastHelper<T>::cast(this);
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