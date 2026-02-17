namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	ReflectObjectSequenceContainerProperty<ObjectType, ContainerType, PropertyType>::ReflectObjectSequenceContainerProperty(
		const FlyweightStringA& name, 
		Getter<ObjectType, ContainerType<PropertyType>> getter, 
		ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter, 
		Setter<ObjectType, ContainerType<PropertyType>> setter
	)
	{
		STATIC_ASSERT_IS_BASE_OF(IReflectObject, PropertyType);
		STATIC_ASSERT(ReflectContainerCompatible<ContainerType, PropertyType>, "ContainerType must be ReflectContainerCompatible");
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	size_t ke::ReflectObjectSequenceContainerProperty<ObjectType, ContainerType, PropertyType>::getSize(const IReflectObject * parentReflectObject) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.size();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	IReflectObject* ke::ReflectObjectSequenceContainerProperty<ObjectType, ContainerType, PropertyType>::getReflectObject(const size_t index, IReflectObject* parentReflectObject)
	{
		ContainerType<PropertyType>& container = this->get(object);
		PropertyType& property = container[index];
		return static_cast<IReflectObject*>(&property);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	const IReflectObject* ke::ReflectObjectSequenceContainerProperty<ObjectType, ContainerType, PropertyType>::getReflectObject(const size_t index, const IReflectObject* parentReflectObject) const
	{
		ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		return static_cast<const IReflectObject*>(&property);
	}
}