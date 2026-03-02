namespace ke
{
	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	ReflectObjectSequenceProperty<ObjectType, ContainerType, PropertyType>::ReflectObjectSequenceProperty(
		const FlyweightStringA& name, 
		Getter<ObjectType, ContainerType<PropertyType>> getter, 
		ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter, 
		Setter<ObjectType, ContainerType<PropertyType>> setter
	)
	{
		STATIC_ASSERT_IS_BASE_OF(IReflectObject, PropertyType);
		STATIC_ASSERT((ReflectSequenceContainerCompatible<ContainerType<PropertyType>, PropertyType>), "ContainerType must be ReflectSequenceContainerCompatible");
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	size_t ke::ReflectObjectSequenceProperty<ObjectType, ContainerType, PropertyType>::size(const IReflectObject * object) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.size();
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	IReflectObject* ke::ReflectObjectSequenceProperty<ObjectType, ContainerType, PropertyType>::getReflectObject(const size_t index, IReflectObject* object)
	{
		ContainerType<PropertyType>& container = this->get(object);
		PropertyType& property = container[index];
		return static_cast<IReflectObject*>(&property);
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	const IReflectObject* ke::ReflectObjectSequenceProperty<ObjectType, ContainerType, PropertyType>::getReflectObject(const size_t index, const IReflectObject* object) const
	{
		ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		return static_cast<const IReflectObject*>(&property);
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	void ReflectObjectSequenceProperty<ObjectType, ContainerType, PropertyType>::empalceDefaultReflectObject(const IReflectObject* object)
	{
		ContainerType<PropertyType>& container = this->get(object);
		container.emplace_back();
	}
}