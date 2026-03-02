#pragma once
#include "IReflectContainerProperty.h"
#include "ReflectPODPropertyInfo.h"

namespace ke
{
	class IBuffer;

	class IReflectKeyValueProperty : public IReflectContainerProperty, public IReflectPODPropertyInfoAccessor
	{
	public:
		IReflectKeyValueProperty(const FlyweightStringA& name);
		~IReflectKeyValueProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::PODKeyValueContainer; }

	protected:
		inline virtual void* getInterface() override final { return static_cast<IReflectKeyValueProperty*>(this); }
		inline virtual const void* getInterface() const override final { return static_cast<const IReflectKeyValueProperty*>(this); }

	public:
		virtual void toBinary(const void* key, const IReflectObject* object, IBuffer* outDst) const = 0;
		virtual void toString(const void* key, const IReflectObject* object, IBuffer* outStringBuffer) const = 0;

	public:
		virtual void addFromBinary(IReflectObject* object, const void* src) = 0;
		virtual void addFromString(IReflectObject* object, const char* src, size_t strLen) = 0;
	};

	template<>
	struct ReflectCastHelper<IReflectKeyValueProperty>
	{
		static IReflectKeyValueProperty* cast(IReflectProperty* prop);
		static const IReflectKeyValueProperty* cast(const IReflectProperty* prop);
	};
}