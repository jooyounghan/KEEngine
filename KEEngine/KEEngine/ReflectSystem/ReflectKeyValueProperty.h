#pragma once
#include "IReflectKeyValueProperty.h"
#include "ReflectPropertyAccessor.h"
#include "StrUtil.h"

namespace ke
{
	template<typename ObjectType, template<typename...> typename ContainerType, typename KeyType, typename ValueType>
	class ReflectKeyValueProperty : public IReflectKeyValueProperty, public ReflectPODPropertyInfo<ValueType>, public ReflectPropertyAccessor<ObjectType, ContainerType<KeyType, ValueType>>
	{
	public:
		ReflectKeyValueProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, ContainerType<KeyType, ValueType>> getter
			, ConstGetter<ObjectType, ContainerType<KeyType, ValueType>> constGetter
			, Setter<ObjectType, ContainerType<KeyType, ValueType>> setter
		);

	protected:
		virtual void* getPODPropertyInfoPtr() override { return static_cast<ReflectPODPropertyInfo<ValueType>*>(this); }
		virtual const void* getPODPropertyInfoPtr() const override { return static_cast<const ReflectPODPropertyInfo<ValueType>*>(this); }

	public:
		virtual size_t	size(const IReflectObject* parentReflectObject) const override;

	public:
		virtual void toBinary(const void* key, const IReflectObject* object, IBuffer* outDst) const override;
		virtual void toString(const void* key, const IReflectObject* object, IBuffer* outStringBuffer) const override;

	public:
		virtual void addFromBinary(IReflectObject* object, const void* src) override;
		virtual void addFromString(IReflectObject* object, const char* src, size_t strLen) override;
	};
}
#include "ReflectKeyValueProperty.hpp"