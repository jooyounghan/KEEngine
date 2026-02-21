namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::ReflectEnumSeqProperty(
		const FlyweightStringA& name,
		Getter<ObjectType, ContainerType<PropertyType>> getter,
		ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter,
		Setter<ObjectType, ContainerType<PropertyType>> setter
	)
		: IReflectPODSeqProperty(name),
		ReflectPODPropertyInfo<PropertyType>(),
		ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>(getter, constGetter, setter)
	{
		STATIC_ASSERT((ReflectContainerCompatible<ContainerType, PropertyType>), "ContainerType must be ReflectContainerCompatible");
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	const void* ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::getTypeId() const
	{
		return IReflectPODPropertyInfoAccessor::getPODTypeId<PropertyType>();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	size_t ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::size(const IReflectObject* object) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.size();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::resize(const IReflectObject* object, size_t newSize)
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.resize(newSize);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	IReflectPODProperty* ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::getElementProperty(const size_t index, IReflectObject* object)
	{
		ContainerType<PropertyType>& container = this->get(object);
		_elementProxy.set(&container[index]);
		return &_elementProxy;
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	const IReflectPODProperty* ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::getElementProperty(const size_t index, const IReflectObject* object) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		_elementProxy.setConst(&container[index]);
		return &_elementProxy;
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::ElementProxy()
		: IReflectPODProperty(FlyweightStringA(""))
	{
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	const void* ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::getTypeId() const
	{
		return IReflectPODPropertyInfoAccessor::getPODTypeId<PropertyType>();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::fromBianry(IReflectObject* /*object*/, const void* src)
	{
		*_ptr = static_cast<PropertyType>(*static_cast<const size_t*>(src));
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::toBinary(const IReflectObject* /*object*/, IBuffer* outDst) const
	{
		const size_t val = static_cast<size_t>(*_constPtr);
		outDst->write(&val, sizeof(size_t));
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::fromString(IReflectObject* /*object*/, const char* src, size_t strlen)
	{
		std::optional<PropertyType> optVal = EnumWrapper<PropertyType>::fromString(std::string_view(src, strlen));
		if (optVal.has_value())
		{
			*_ptr = optVal.value();
		}
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectEnumSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::toString(const IReflectObject* /*object*/, IBuffer* outStringBuffer) const
	{
		const std::string& enumString = EnumWrapper<PropertyType>::toString(*_constPtr);
		outStringBuffer->write(enumString.c_str(), enumString.length());
	}
}
