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
        if (xmlBuilder == nullptr)
        {
            KE_ASSERT_DEV(false, "ReflectProperty need XmlBuilder For Serializing");
            return;
        }

        StaticBuffer<BUFFER_BYTES_256> propertyValueBuffer;
        const PropertyType& property = this->get(obj);
        ReflectParser::toString(&propertyValueBuffer, property);
        xmlBuilder->addAttribute(_name.c_str(), _name.length(), propertyValueBuffer.getConstBuffer(), propertyValueBuffer.getCursorPos());
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectProperty<ObjectType, PropertyType>::deserializeFromXML(const XmlNode* xmlNode, const XmlAttribute* xmlAttribute, IReflectObject* obj)
    {
        if (xmlAttribute == nullptr)
        {
            KE_ASSERT_DEV(false, "ReflectProperty need XmlAttribute For Deserializing");
            return;
        }

        const std::string_view name = xmlAttribute->getName();
        
        if (_name != name)
        {
            KE_ASSERT_DEV(false, "ReflectProperty name mismatched with attribute");
            return;
        }

        const std::string_view value = xmlAttribute->getValue();
        PropertyType& property = this->get(obj);
        ReflectParser::fromString(value.data(), value.length(), &property);
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectProperty<ObjectType, PropertyType>::serializeToBinary(IBuffer * dstBuffer, const IReflectObject * obj) const
    {}

    template<typename ObjectType, typename PropertyType>
    void ReflectProperty<ObjectType, PropertyType>::deserializeFromBinary(const IBuffer * srcBuffer, const IReflectObject * obj)
    {}
}