#pragma once
#include "IReflectPODSequenceContainerProperty.h"
#include "ReflectPropertyAccessor.h"
#include "ReflectPODPropertyInfo.h"
#include "ReflectParser.h"

namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	class ReflectPODSequenceContainerProperty : public IReflectPODSequenceContainerProperty, public RefelctPODPropertyInfo<PropertyType>, public ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>
	{
	public:
		ReflectPODSequenceContainerProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<PropertyType>> getter
			, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter
			, Setter<ObjectType, ContainerType<PropertyType>> setter
		);

	public:
		virtual size_t	getSize(const IReflectObject* parentReflectObject) const override;

	public:
		virtual void	fromBianry(const size_t index, IReflectObject* object, const void* src) override;
		virtual void	toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const override;
		virtual void	fromString(const size_t index, IReflectObject* object, const char* src, size_t strlen) override;
		virtual void	toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const override;
	};
}
#include "ReflectPODSequenceContainerProperty.hpp"