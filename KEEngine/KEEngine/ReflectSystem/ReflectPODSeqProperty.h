#pragma once
#include "IReflectPODSeqProperty.h"
#include "ReflectPropertyAccessor.h"
#include "ReflectParser.h"

namespace ke
{
	template<typename ObjectType, template<typename> typename ContainerType, typename PropertyType>
	class ReflectPODSeqProperty : public IReflectPODSeqProperty, public ReflectPODPropertyInfo<PropertyType>, public ReflectPropertyAccessor<ObjectType, ContainerType<PropertyType>>
	{
	public:
		ReflectPODSeqProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<PropertyType>> getter
			, ConstGetter<ObjectType, ContainerType<PropertyType>> constGetter
			, Setter<ObjectType, ContainerType<PropertyType>> setter
		);

	protected:
		virtual const void* getTypeId() const;
		virtual void* getPODPropertyInfoPtr() override { return static_cast<ReflectPODPropertyInfo<PropertyType>*>(this); }
		virtual const void* getPODPropertyInfoPtr() const override { return static_cast<const ReflectPODPropertyInfo<PropertyType>*>(this); }

	public:
		virtual size_t	size(const IReflectObject* parentReflectObject) const override;
		virtual void	resize(const IReflectObject* object, size_t newSize) override;

	public:
		virtual void	fromBianry(const size_t index, IReflectObject* object, const void* src) override;
		virtual void	toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const override;
		virtual void	fromString(const size_t index, IReflectObject* object, const char* src, size_t strLen) override;
		virtual void	toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const override;
	};
}
#include "ReflectPODSeqProperty.hpp"