#pragma once
#include "IReflectContainerProperty.h"

namespace ke
{
	class IBuffer;
	class IReflectObject;

	class IReflectObjectKeyValueProperty : public IReflectContainerProperty
	{
	public:
		IReflectObjectKeyValueProperty(const FlyweightStringA& name);
		~IReflectObjectKeyValueProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::ReflectObjectKeyValueContainer; }

	protected:
		inline virtual void* getInterface() override final { return static_cast<IReflectObjectKeyValueProperty*>(this); }
		inline virtual const void* getInterface() const override final { return static_cast<const IReflectObjectKeyValueProperty*>(this); }

	public:
		virtual void toBinaryKey(const size_t index, const IReflectObject* object, IBuffer* outDst) const = 0;
		virtual void toStringKey(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const = 0;
		virtual IReflectObject* getReflectObject(const size_t index, IReflectObject* parentReflectObject) = 0;
		virtual const IReflectObject* getReflectObject(const size_t index, const IReflectObject* parentReflectObject) const = 0;

	public:
		virtual void empalceDefaultReflectObject(const IReflectObject* parentReflectObject) = 0;
	};

	template<>
	struct ReflectCastHelper<IReflectObjectKeyValueProperty>
	{
		static IReflectObjectKeyValueProperty* cast(IReflectProperty* prop);
		static const IReflectObjectKeyValueProperty* cast(const IReflectProperty* prop);
	};
}