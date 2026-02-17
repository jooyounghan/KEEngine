namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	ReflectPODContainerProperty<ObjectType, ContainerType, PropertyType>::ReflectPODContainerProperty(
		const FlyweightStringA& name,
		Getter<ObjectType, ContainerType<PropertyType>> getter,
		ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter,
		Setter<ObjectType, ContainerType<PropertyType>> setter
	)
		: IReflectPODContainerProperty(name),
		RefelctPODPropertyInfo<PropertyType>(),
		ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>(getter, constGetter, setter)
	{

	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	size_t ke::ReflectPODContainerProperty<ObjectType, ContainerType, PropertyType>::getSize(const IReflectObject* parentReflectObject) const
	{
		return size_t();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODContainerProperty<ObjectType, ContainerType, PropertyType>::fromBianry(const size_t index, IReflectObject* object, const void* src)
	{}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODContainerProperty<ObjectType, ContainerType, PropertyType>::toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const
	{}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODContainerProperty<ObjectType, ContainerType, PropertyType>::fromString(const size_t index, IReflectObject* object, const char* src, size_t strlen)
	{}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODContainerProperty<ObjectType, ContainerType, PropertyType>::toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const
	{}
}