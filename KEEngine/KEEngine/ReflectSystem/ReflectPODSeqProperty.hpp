#include "ReflectPODSeqProperty.h"
namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::ReflectPODSeqProperty(
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
	const void* ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::getTypeId() const
	{
		return IReflectPODPropertyInfoAccessor::getPODTypeId<PropertyType>();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	size_t ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::size(const IReflectObject* object) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.size();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::resize(const IReflectObject* object, size_t newSize)
	{
		const ContainerType<PropertyType>& container = this->get(object);
		return container.resize(newSize);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	IReflectPODProperty* ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::getElementProperty(const size_t index, IReflectObject* object)
	{
		ContainerType<PropertyType>& container = this->get(object);
		_elementProxy.set(&container[index]);
		return &_elementProxy;
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	const IReflectPODProperty* ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::getElementProperty(const size_t index, const IReflectObject* object) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		_elementProxy.setConst(&container[index]);
		return &_elementProxy;
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::ElementProxy()
		: IReflectPODProperty(FlyweightStringA(""))
	{
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	const void* ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::getTypeId() const
	{
		return IReflectPODPropertyInfoAccessor::getPODTypeId<PropertyType>();
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::fromBianry(IReflectObject* /*object*/, const void* src)
	{
		if constexpr (std::is_enum_v<PropertyType>)
		{
			*_ptr = static_cast<PropertyType>(*static_cast<const size_t*>(src));
		}
		else
		{
			ReflectParser::parseFromBinary(src, _ptr);
		}
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::toBinary(const IReflectObject* /*object*/, IBuffer* outDst) const
	{
		if constexpr (std::is_enum_v<PropertyType>)
		{
			const size_t val = static_cast<size_t>(*_constPtr);
			outDst->write(&val, sizeof(size_t));
		}
		else
		{
			ReflectParser::parseToBinary(outDst, _constPtr);
		}
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::fromString(IReflectObject* /*object*/, const char* src, size_t strlen)
	{
		if constexpr (std::is_enum_v<PropertyType>)
		{
			std::optional<PropertyType> optVal = EnumWrapper<PropertyType>::fromString(std::string_view(src, strlen));
			if (optVal.has_value())
			{
				*_ptr = optVal.value();
			}
		}
		else
		{
			ReflectParser::parseFromString(src, strlen, _ptr);
		}
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::ElementProxy::toString(const IReflectObject* /*object*/, IBuffer* outStringBuffer) const
	{
		if constexpr (std::is_enum_v<PropertyType>)
		{
			const std::string& enumString = EnumWrapper<PropertyType>::toString(*_constPtr);
			outStringBuffer->write(enumString.c_str(), enumString.length());
		}
		else
		{
			ReflectParser::parseToString(outStringBuffer, _constPtr);
		}
	}
}