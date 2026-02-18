namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	ReflectObjectSeqProperty<ObjectType, ContainerType, PropertyType>::ReflectObjectSeqProperty(
		const FlyweightStringA& name, 
		Getter<ObjectType, ContainerType<PropertyType>> getter, 
		ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter, 
		Setter<ObjectType, ContainerType<PropertyType>> setter
	)
	{
		STATIC_ASSERT_IS_BASE_OF(IReflectObject, PropertyType);
		STATIC_ASSERT((ReflectContainerCompatible<ContainerType, PropertyType>), "ContainerType must be ReflectContainerCompatible");
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	size_t ke::ReflectObjectSeqProperty<ObjectType, ContainerType, PropertyType>::size(const IReflectObject * object) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.size();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectObjectSeqProperty<ObjectType, ContainerType, PropertyType>::resize(const IReflectObject* object, size_t newSize)
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.resize(newSize);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	IReflectObject* ke::ReflectObjectSeqProperty<ObjectType, ContainerType, PropertyType>::getReflectObject(const size_t index, IReflectObject* object)
	{
		ContainerType<PropertyType>& container = this->get(object);
		PropertyType& property = container[index];
		return static_cast<IReflectObject*>(&property);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	const IReflectObject* ke::ReflectObjectSeqProperty<ObjectType, ContainerType, PropertyType>::getReflectObject(const size_t index, const IReflectObject* object) const
	{
		ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		return static_cast<const IReflectObject*>(&property);
	}
}