#pragma once
#include "IReflectSequenceProperty.h"
#include "ReflectPropertyAccessor.h"

namespace ke
{
	template<typename ObjectType, template<typename...> typename ContainerType, typename PropertyType>
	class ReflectSequenceProperty : public IReflectSequenceProperty, public ReflectPODPropertyInfo<PropertyType>, public ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>
	{
	public:
		ReflectSequenceProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<PropertyType>> getter
			, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter
			, Setter<ObjectType, ContainerType<PropertyType>> setter
		);

	protected:
		virtual void* getPODPropertyInfoPtr() override { return static_cast<ReflectPODPropertyInfo<PropertyType>*>(this); }
		virtual const void* getPODPropertyInfoPtr() const override { return static_cast<const ReflectPODPropertyInfo<PropertyType>*>(this); }

	public:
		virtual size_t	size(const IReflectObject* parentReflectObject) const override;

	public:
		virtual void	toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const override;
		virtual void	toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const override;

	public:
		virtual void	addFromBinary(IReflectObject* object, const void* src) override;
		virtual void	addFromString(IReflectObject* object, const char* src, size_t strLen) override;
	};
}
#include "ReflectSequenceProperty.hpp"
