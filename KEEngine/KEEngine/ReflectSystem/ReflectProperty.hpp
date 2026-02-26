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
    void ReflectProperty<ObjectType, PropertyType>::fromBianry(IReflectObject* object, const void* src)
    {
        ReflectParser::parseFromBinary(src, &this->get(object));
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectProperty<ObjectType, PropertyType>::toBinary(const IReflectObject* object, IBuffer* outDst) const
    {
        ReflectParser::parseToBinary(outDst, &this->get(object));
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectProperty<ObjectType, PropertyType>::fromString(IReflectObject* object, const char* src, size_t strLen)
    {
        ReflectParser::parseFromString(src, strLen, &this->get(object));
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectProperty<ObjectType, PropertyType>::toString(const IReflectObject* object, IBuffer* outStringBuffer) const
    {
        ReflectParser::parseToString(outStringBuffer, &this->get(object));
    }
}