#pragma once
#include "IReflectContainerProperty.h"
#include "ReflectPODPropertyInfo.h"

namespace ke
{
	class IBuffer;

	class IReflectPODSeqProperty : public IReflectContainerProperty, public IReflectPODPropertyInfoAccessor
	{
	public:
		IReflectPODSeqProperty(const FlyweightStringA& name);
		~IReflectPODSeqProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::PODContainer; }

	protected:
		inline virtual void*		getInterface() override final { return static_cast<IReflectPODSeqProperty*>(this); }
		inline virtual const void*	getInterface() const override final { return static_cast<const IReflectPODSeqProperty*>(this); }

	public:
		virtual void fromBianry(const size_t index, IReflectObject* object, const void* src) = 0;
		virtual void toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const = 0;
		virtual void fromString(const size_t index, IReflectObject* object, const char* src, size_t strlen) = 0;
		virtual void toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const = 0;
	};

	template<>
	struct ReflectCastHelper<IReflectPODSeqProperty>
	{
		static IReflectPODSeqProperty*		cast(IReflectProperty* prop);
		static const IReflectPODSeqProperty*	cast(const IReflectProperty* prop);
	};
}