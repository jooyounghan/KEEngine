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
	void ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::fromBianry(const size_t index, IReflectObject* object, const void* src)
	{
		ContainerType<PropertyType>& container = this->get(object);
		PropertyType& property = container[index];
		ReflectParser::parseFromBinary(src, &property);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		ReflectParser::parseToBinary(outDst, &property);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::fromString(const size_t index, IReflectObject* object, const char* src, size_t strlen)
	{
		const ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		ReflectParser::parseFromString(src, strlen, &property);
	}

	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	void ReflectPODSeqProperty<ObjectType, ContainerType, PropertyType>::toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		const ContainerType<PropertyType>& container = this->get(object);
		const PropertyType& property = container[index];
		ReflectParser::parseToString(outStringBuffer, &property);
	}
}