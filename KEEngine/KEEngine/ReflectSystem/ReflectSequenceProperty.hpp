namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
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
		STATIC_ASSERT((ReflectContainerCompatible<ContainerType, PropertyType>), "ContainerType must be ReflectContainerCompatible");
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	size_t ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::size(const IReflectObject* object) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.size();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::resize(const IReflectObject* object, size_t newSize)
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.resize(newSize);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::fromBianry(const size_t index, IReflectObject* object, const void* src)
	{
		ContainerType<PropertyType>& container = this->get(object);
		PropertyType& property = container[index];
		if constexpr (std::is_enum_v<PropertyType>)
		{
			property = static_cast<PropertyType>(*static_cast<const size_t*>(src));
		}
		else
		{
			ReflectParser::parseFromBinary(src, &property);
		}
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		if constexpr (std::is_enum_v<PropertyType>)
		{
			const size_t enumValue = static_cast<size_t>(property);
			outDst->write(&enumValue, sizeof(size_t));
		}
		else
		{
			ReflectParser::parseToBinary(outDst, &property);
		}
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::fromString(const size_t index, IReflectObject* object, const char* src, size_t strLen)
	{
		ContainerType<PropertyType>& container = this->get(object);
		PropertyType& property = container[index];
		if constexpr (std::is_enum_v<PropertyType>)
		{
			std::optional<PropertyType> optVal = EnumWrapper<PropertyType>::fromString(std::string_view(src, strLen));
			if (optVal.has_value())
			{
				property = optVal.value();
			}
		}
		else
		{
			ReflectParser::parseFromString(src, strLen, &property);
		}
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>::toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		if constexpr (std::is_enum_v<PropertyType>)
		{
			const std::string& enumString = EnumWrapper<PropertyType>::toString(property);
			outStringBuffer->write(enumString.c_str(), enumString.length());
		}
		else
		{
			ReflectParser::parseToString(outStringBuffer, &property);
		}
	}
}
