namespace ke
{
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