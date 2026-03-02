namespace ke
{
	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::ReflectSequenceProperty(
		const FlyweightStringA& name,
		Getter<ObjectType, ContainerType<PropertyType>> getter,
		ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter,
		Setter<ObjectType, ContainerType<PropertyType>> setter
	)
		: IReflectSequenceProperty(name),
		ReflectPODPropertyInfo<PropertyType>(),
		ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>(getter, constGetter, setter)
	{
		STATIC_ASSERT((ReflectSequenceContainerCompatible<ContainerType<PropertyType>, PropertyType>), "ContainerType must be ReflectSequenceContainerCompatible");
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	size_t ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::size(const IReflectObject* object) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.size();
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	void ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		ReflectContainerParser::parseToBinary(outDst, property);
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	void ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		ReflectContainerParser::parseToString(outStringBuffer, property);
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	void ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::addFromBinary(IReflectObject* object, const void* src)
	{
		PropertyType property;
		ReflectContainerParser::parseFromBinary(src, property);

		ContainerType<PropertyType>& container = this->get(object);
		container.push_back(property);
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	void ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::addFromString(IReflectObject* object, const char* src, size_t strLen)
	{
		PropertyType property;
		ReflectContainerParser::parseFromString(src, strLen, property);

		ContainerType<PropertyType>& container = this->get(object);
		container.push_back(property);
	}
}
