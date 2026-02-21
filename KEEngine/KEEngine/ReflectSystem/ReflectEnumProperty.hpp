namespace ke
{
	template<typename ObjectType, typename PropertyType>
	ReflectEnumProperty<ObjectType, PropertyType>::ReflectEnumProperty(
		const FlyweightStringA& name,
		Getter<ObjectType, PropertyType> getter, 
		ConstGetter<ObjectType, PropertyType> constGetter, 
		Setter<ObjectType, PropertyType> setter
	) : IReflectPODProperty(name), ReflectPropertyAccessor<ObjectType, PropertyType>(getter, constGetter, setter)
	{
	}

	template<typename ObjectType, typename PropertyType>
	const void* ke::ReflectEnumProperty<ObjectType, PropertyType>::getTypeId() const
	{
		return IReflectPODPropertyInfoAccessor::getPODTypeId<PropertyType>();
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectEnumProperty<ObjectType, PropertyType>::fromBianry(IReflectObject* object, const void* src)
	{
		this->get(object) = static_cast<const PropertyType>(*static_cast<const size_t*>(src));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectEnumProperty<ObjectType, PropertyType>::toBinary(const IReflectObject * object, IBuffer * outDst) const
	{
		const size_t enumValue = static_cast<const size_t>(this->get(object));
		outDst->write(&enumValue, sizeof(size_t));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectEnumProperty<ObjectType, PropertyType>::fromString(IReflectObject * object, const char* src, size_t strLen)
	{
		std::optional<PropertyType> optVal = EnumWrapper<PropertyType>::fromString(std::string_view(src, strLen));
		if (optVal.has_value())
		{
			this->get(object) = optVal.value();
		}
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectEnumProperty<ObjectType, PropertyType>::toString(const IReflectObject * object, IBuffer * outStringBuffer) const
	{
		const std::string& enumString = EnumWrapper<PropertyType>::toString(this->get(object));
		outStringBuffer->write(enumString.c_str(), enumString.length());
	}
}