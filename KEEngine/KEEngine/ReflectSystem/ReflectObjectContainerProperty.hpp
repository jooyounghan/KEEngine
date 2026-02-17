namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	ReflectObjectContainerProperty<ObjectType, ContainerType, PropertyType>::ReflectObjectContainerProperty(
		const FlyweightStringA& name, 
		Getter<ObjectType, ContainerType<PropertyType>> getter, 
		ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter, 
		Setter<ObjectType, ContainerType<PropertyType>> setter
	)
	{
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	size_t ke::ReflectObjectContainerProperty<ObjectType, ContainerType, PropertyType>::getSize(const IReflectObject * parentReflectObject) const
	{
		return size_t();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	IReflectObject* ke::ReflectObjectContainerProperty<ObjectType, ContainerType, PropertyType>::getReflectObject(const size_t index, IReflectObject* parentReflectObject)
	{
		return nullptr;
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	const IReflectObject* ke::ReflectObjectContainerProperty<ObjectType, ContainerType, PropertyType>::getReflectObject(const size_t index, const IReflectObject* parentReflectObject) const
	{
		return nullptr;
	}
}