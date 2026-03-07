namespace ke
{
    template<typename ObjectType, typename PropertyType>
    ReflectProperty<ObjectType, PropertyType>::ReflectProperty(
        const FlyweightStringA& name,
        Getter<ObjectType, PropertyType> getter,
        ConstGetter<ObjectType, PropertyType> constGetter,
        Setter<ObjectType, PropertyType> setter
	) : IReflectProperty(name), ReflectPropertyAccessor<ObjectType, PropertyType>(getter, constGetter, setter)
    {
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectProperty<ObjectType, PropertyType>::serailizeToXml(XmlWriter* xmlWriter, XmlBuilder* xmlBuilder, const IReflectObject* obj) const
    {
        StaticBuffer<BUFFER_BYTES_256> propertyValueBuffer;
        const PropertyType& property = this->get(obj);
        if constexpr (std::is_enum_v<PropertyType>)
        {
            const std::string& enumString = EnumWrapper<T>::toString(property);
            propertyValueBuffer->write(enumString.c_str(), enumString.length());
        }
        else
        {
            ReflectParser::parseToString(propertyValueBuffer, &value);
        }
        
        const bool isSerializable = xmlBuilder != nullptr;
        KE_ASSERT_DEV(isSerializable, "ReflectProperty need XmlBuilder For Serializing");
        if (isSerializable)
        {
            xmlBuilder->addAttribute(_name.c_str(), _name.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
        }
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectProperty<ObjectType, PropertyType>::deserializeFromXML(const XmlNode* xmlNode, const XmlAttribute* xmlAttribute, IReflectObject* obj)
    {
        const bool isSerializable = xmlAttribute != nullptr;
        KE_ASSERT_DEV(isSerializable, "ReflectProperty need XmlAttribute For Deserializing");
        if (isSerializable)
        {
            const std::string_view name = xmlAttribute.getName();

            const bool isNameMatched = _name == name;
            KE_ASSERT_DEV(isNameMatched, "ReflectProperty name mismatched with attribute");
            if (isNameMatched)
            {
                const std::string_view value = xmlAttribute.getValue();
                if constexpr (std::is_enum_v<PropertyType>)
                {
                    std::optional<T> optVal = EnumWrapper<PropertyType>::fromString(std::string_view(value.data(), value.length()));
                    if (optVal.has_value())
                    {
                        this->set(optVal.value());
                    }
                }
                else
                {
                    PropertyType& property = this->get(obj);
                    ReflectParser::parseFromString(value.data(), value.length(), &property);
                }
            }
        }
    }

    template<typename ObjectType, typename PropertyType>
    inline void ReflectProperty<ObjectType, PropertyType>::serializeToBinary(IBuffer * dstBuffer, const IReflectObject * obj) const
    {}

    template<typename ObjectType, typename PropertyType>
    inline void ReflectProperty<ObjectType, PropertyType>::deserializeFromBinary(const IBuffer * srcBuffer, const IReflectObject * obj)
    {}
}