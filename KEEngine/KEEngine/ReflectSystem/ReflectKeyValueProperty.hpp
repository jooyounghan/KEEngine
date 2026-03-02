namespace ke
{
	template<typename ObjectType, template<typename...> typename ContainerType, typename KeyType, typename ValueType>
	ReflectKeyValueProperty<ObjectType, ContainerType, KeyType, ValueType>::ReflectKeyValueProperty(
		const FlyweightStringA& name,
		Getter<ObjectType, ContainerType<KeyType, ValueType>> getter,
		ConstGetter<ObjectType, ContainerType<KeyType, ValueType>> constGetter,
		Setter<ObjectType, ContainerType<KeyType, ValueType>> setter
	)
	{
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename KeyType, typename ValueType>
	size_t ReflectKeyValueProperty<ObjectType, ContainerType, KeyType, ValueType>::size(const IReflectObject* parentReflectObject) const
	{
		const ContainerType<KeyType, ValueType>& container = this->get(object);
		return container.size();
	}



	template<typename ObjectType, template<typename...> typename ContainerType, typename KeyType, typename ValueType>
	void ReflectKeyValueProperty<ObjectType, ContainerType, KeyType, ValueType>::toBinary(const void* key, const IReflectObject* object, IBuffer* outDst) const
	{
		const KeyType& keyRef = *static_cast<const KeyType*>(key);
		const ContainerType<KeyType, ValueType>& container = this->get(object);
		ContainerType<KeyType, ValueType>::const_iterator iter = container.find(keyRef);

		if (iter != container.end())
		{
			ReflectContainerParser::parseToBinary(outDst, keyRef);
			ReflectContainerParser::parseToBinary(outDst, iter->second);
		}
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename KeyType, typename ValueType>
	void ReflectKeyValueProperty<ObjectType, ContainerType, KeyType, ValueType>::toString(const void* key, const IReflectObject * object, IBuffer * outStringBuffer) const
	{
		const KeyType& keyRef = *static_cast<const KeyType*>(key);
		const ContainerType<KeyType, ValueType>& container = this->get(object);
		ContainerType<KeyType, ValueType>::const_iterator iter = container.find(keyRef);

		if (iter != container.end())
		{
			ReflectContainerParser::parseToString(outStringBuffer, &keyRef);
			outStringBuffer->write(':', 1);
			ReflectContainerParser::parseToString(outStringBuffer, &iter->second);
		}
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename KeyType, typename ValueType>
	void ReflectKeyValueProperty<ObjectType, ContainerType, KeyType, ValueType>::addFromBinary(IReflectObject * object, const void* src)
	{
		KeyType key;
		ValueType value;

		Offset offset = ReflectContainerParser::parseFromBinary(src, key);
		ReflectContainerParser::parseFromBinary(src + offset, value);

		ContainerType<KeyType, ValueType>& container = this->get(object);
		container.emplace(key, value);
	}

	template<typename ObjectType, template<typename...> typename ContainerType, typename KeyType, typename ValueType>
	void ReflectKeyValueProperty<ObjectType, ContainerType, KeyType, ValueType>::addFromString(IReflectObject * object, const char* src, size_t strLen)
	{
		KeyType key;
		ValueType value;
		const std::vector<std::string_view> keyValue = StrUtil::split(src, strLen, ":", 1);

		KE_ASSERT(keyValue.size() == 2, "Invalid key-value string format");		
		const std::string_view& keyStr = keyValue[0];
		const std::string_view& valueStr = keyValue[1];

		ReflectContainerParser::parseFromString(keyStr.data(), keyStr.size(), key);
		ReflectContainerParser::parseFromString(valueStr.data(), valueStr.size(), value);

		ContainerType<KeyType, ValueType>& container = this->get(object);
		container.emplace(key, value);
	}
}