namespace ke
{
    template<typename ObjectType, typename PropertyType>
    ReflectPODProperty<ObjectType, PropertyType>::ReflectPODProperty(
        const FlyweightStringA& name,
        Getter<ObjectType, PropertyType> getter,
        ConstGetter<ObjectType, PropertyType> constGetter,
        Setter<ObjectType, PropertyType> setter
	) : IReflectPODProperty(name), ReflectPropertyAccessor<ObjectType, PropertyType>(getter, constGetter, setter)
    {
    }

    template<typename ObjectType, typename PropertyType>
    const void* ReflectPODProperty<ObjectType, PropertyType>::getTypeId() const
    {
        return IReflectPODPropertyInfoAccessor::getPODTypeId<PropertyType>();
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectPODProperty<ObjectType, PropertyType>::fromBianry(IReflectObject* object, const void* src)
    {
        ReflectParser::parseFromBinary(src, &this->get(object));
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectPODProperty<ObjectType, PropertyType>::toBinary(const IReflectObject* object, IBuffer* outDst) const
    {
        ReflectParser::parseToBinary(outDst, &this->get(object));
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectPODProperty<ObjectType, PropertyType>::fromString(IReflectObject* object, const char* src, size_t strlen)
    {
        ReflectParser::parseFromString(src, strlen, &this->get(object));
    }

    template<typename ObjectType, typename PropertyType>
    void ReflectPODProperty<ObjectType, PropertyType>::toString(const IReflectObject* object, IBuffer* outStringBuffer) const
    {
        ReflectParser::parseToString(outStringBuffer, &this->get(object));
    }
}