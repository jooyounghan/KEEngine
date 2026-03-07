#define REFLECT_KEY_VALUE_TEMPLATE \
	template<typename ObjectType, template<typename...> typename ContainerType, typename KeyType, typename ValueType>

#define REFLECT_KEY_VALUE_CLASS \
    ReflectKeyValueProperty<ObjectType, ContainerType, KeyType, ValueType>

namespace ke
{
	REFLECT_KEY_VALUE_TEMPLATE
		REFLECT_KEY_VALUE_CLASS::ReflectKeyValueProperty(
		const FlyweightStringA& name,
		Getter<ObjectType, ContainerType<KeyType, ValueType>> getter,
		ConstGetter<ObjectType, ContainerType<KeyType, ValueType>> constGetter,
		Setter<ObjectType, ContainerType<KeyType, ValueType>> setter
	) : IReflectProperty(name),
		ReflectPropertyAccessor<ObjectType, ContainerType<KeyType, ValueType>>(getter, constGetter, setter)
	{
		STATIC_ASSERT((ReflectKeyValueContainerCompatible<ContainerType<KeyType, ValueType>, KeyType, ValueType>), "ContainerType must be ReflectKeyValueContainerCompatible");
	}

	template <typename Container>
	static void serializeToXmlKeyValueElement(IBuffer* dstBuffer, typename Container::const_iterator iter)
	{
		ReflectParser::toString(dstBuffer, &(iter->first));
		dstBuffer->writeOne(":");
		ReflectParser::toString(dstBuffer, &(iter->second));
	}

	REFLECT_KEY_VALUE_TEMPLATE
	void REFLECT_KEY_VALUE_CLASS::serailizeToXml(XmlWriter* xmlWriter, XmlBuilder* xmlBuilder, const IReflectObject* obj) const
	{
		if (xmlBuilder == nullptr)
		{
			KE_ASSERT_DEV(false, "ReflectKeyValueProperty need XmlBuilder For Serializing");
			return;
		}

		const ContainerType<KeyType, ValueType>& containerProperty = this->get(obj);

		StaticBuffer<BUFFER_BYTES_1KB> propertyValueBuffer;

		ContainerType<KeyType, ValueType>::const_iterator iter = containerProperty.begin();
		serializeToXmlKeyValueElement(&propertyValueBuffer, iter);
		++iter;

		for (; iter != containerProperty.end(); ++iter)
		{
			propertyValueBuffer.write(", ", 2);
			serializeToXmlKeyValueElement(&propertyValueBuffer, iter);
		}

		xmlBuilder->addAttribute(_name.c_str(), _name.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
	}

	REFLECT_KEY_VALUE_TEMPLATE
	void ke::REFLECT_KEY_VALUE_CLASS::deserializeFromXML(const XmlNode * xmlNode, const XmlAttribute * xmlAttribute, IReflectObject * obj)
	{
		if (xmlAttribute == nullptr)
		{
			KE_ASSERT_DEV(false, "ReflectSeqeunceProperty need XmlAttribute For Deserializing");
			return;
		}

		const std::string_view name = xmlAttribute->getName();

		if (_name != name)
		{
			KE_ASSERT_DEV(false, "ReflectProperty name mismatched with attribute");
			return;
		}

		const std::string_view valueString = xmlAttribute->getValue();
		const std::vector<std::string_view> values = StrUtil::split(valueString.data(), valueString.length(), ", ", 2);

		ContainerType<KeyType, ValueType>& containerProperty = this->get(obj);

		const size_t count = values.size();
		for (size_t idx = 0; idx < count; ++idx)
		{
			const std::string_view& value = values[idx];
			const std::vector<std::string_view> keyValue = StrUtil::split(value.data(), value.length(), ":", 1);
			KE_ASSERT_DEV(keyValue.size() == 2, "Attribute에 대한 데이터가 KeyValueProperty에 대한 템플릿(Key:Value)와 호환되지 않습니다.");

			const std::string_view& keyString = keyValue[0];
			const std::string_view& valueString = keyValue[1];
			KeyType key;
			ValueType value;

			ReflectParser::fromString(keyString.data(), keyString.length(), &key);
			ReflectParser::fromString(valueString.data(), valueString.length(), &value);

			containerProperty.emplace(key, value);
		}
	}

	REFLECT_KEY_VALUE_TEMPLATE
	void REFLECT_KEY_VALUE_CLASS::serializeToBinary(IBuffer * dstBuffer, const IReflectObject * obj) const
	{
	
	}

	REFLECT_KEY_VALUE_TEMPLATE
	void REFLECT_KEY_VALUE_CLASS::deserializeFromBinary(const IBuffer * srcBuffer, const IReflectObject * obj)
	{
	
	}
}

#undef REFLECT_KEY_VALUE_TEMPLATE
#undef REFLECT_KEY_VALUE_CLASS