#define REFLECT_SEQUENCE_TEMPLATE \
    template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>

#define REFLECT_SEQUENCE_CLASS \
    ReflectSequenceProperty<ObjectType, ContainerType, PropertyType>

namespace ke
{
	REFLECT_SEQUENCE_TEMPLATE
	REFLECT_SEQUENCE_CLASS::ReflectSequenceProperty(
		const FlyweightStringA& name,
		Getter<ObjectType, ContainerType<PropertyType>> getter,
		ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter,
		Setter<ObjectType, ContainerType<PropertyType>> setter
	)	: IReflectProperty(name),
		ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>(getter, constGetter, setter)
	{
		STATIC_ASSERT((ReflectSequenceContainerCompatible<ContainerType<PropertyType>, PropertyType>), "ContainerType must be ReflectSequenceContainerCompatible");
	}

	REFLECT_SEQUENCE_TEMPLATE
	void REFLECT_SEQUENCE_CLASS::serailizeToXml(XmlWriter* xmlWriter, XmlBuilder* xmlBuilder, const IReflectObject* obj) const
	{
		if (xmlBuilder == nullptr)
		{
			KE_ASSERT_DEV(false, "ReflectSeqeunceProperty need XmlBuilder For Serializing");
			return;
		}

		const ContainerType<PropertyType>& containerProperty = this->get(obj);
		const size_t count = containerProperty.size();

		StaticBuffer<BUFFER_BYTES_1KB> propertyValueBuffer;
		if (count > 0) ReflectParser::toString(&propertyValueBuffer, &containerProperty[0]);
		for (size_t idx = 1; idx < count; ++idx)
		{
			propertyValueBuffer.write(", ", 2);
			ReflectParser::toString(&propertyValueBuffer, &containerProperty[idx])
		}
		xmlBuilder->addAttribute(_name.c_str(), _name.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
	}

	REFLECT_SEQUENCE_TEMPLATE
	void REFLECT_SEQUENCE_CLASS::deserializeFromXML(const XmlNode * xmlNode, const XmlAttribute * xmlAttribute, IReflectObject * obj)
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

		ContainerType<PropertyType>& containerProperty = this->get(obj);

		const size_t count = values.size();
		for (size_t idx = 0; idx < count; ++idx)
		{
			const std::string_view& value = values[idx];
			PropertyType& property = containerProperty.emplace_back();
			ReflectParser::fromString(value.data(), value.length(), &property);
		}
	}

	REFLECT_SEQUENCE_TEMPLATE
	void REFLECT_SEQUENCE_CLASS::serializeToBinary(IBuffer * dstBuffer, const IReflectObject * obj) const
	{}

	REFLECT_SEQUENCE_TEMPLATE
	void REFLECT_SEQUENCE_CLASS::deserializeFromBinary(const IBuffer * srcBuffer, const IReflectObject * obj)
	{}
}

#undef REFLECT_SEQUENCE_TEMPLATE
#undef REFLECT_SEQUENCE_CLASS