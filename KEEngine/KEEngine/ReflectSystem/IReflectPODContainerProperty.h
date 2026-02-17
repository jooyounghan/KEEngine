#pragma once
#include "IReflectProperty.h"

namespace ke
{
	class IBuffer;
	class IReflectObject;

	class IReflectPODContainerProperty : public IReflectProperty
	{
	public:
		IReflectPODContainerProperty(const FlyweightStringA& name);
		~IReflectPODContainerProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::PODContainer; }

	protected:
		inline virtual void*		getInterface() override final { return static_cast<IReflectPODContainerProperty*>(this); }
		inline virtual const void*	getInterface() const override final { return static_cast<const IReflectPODContainerProperty*>(this); }

	public:
		virtual size_t getSize(const IReflectObject* parentReflectObject) const = 0;

	public:
		virtual void fromBianry(const size_t index, IReflectObject* object, const void* src) = 0;
		virtual void toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const = 0;
		virtual void fromString(const size_t index, IReflectObject* object, const char* src, size_t strlen) = 0;
		virtual void toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const = 0;
	};

	template<>
	struct ReflectCastHelper<IReflectPODContainerProperty>
	{
		static IReflectPODContainerProperty*		cast(IReflectProperty* prop);
		static const IReflectPODContainerProperty*	cast(const IReflectProperty* prop);
	};
}