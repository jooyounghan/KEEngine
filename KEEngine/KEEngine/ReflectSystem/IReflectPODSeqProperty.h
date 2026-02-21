#pragma once
#include "IReflectContainerProperty.h"
#include "ReflectPODPropertyInfo.h"

namespace ke
{
	class IBuffer;
	class IReflectPODProperty;

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
		void fromBianry(const size_t index, IReflectObject* object, const void* src);
		void toBinary(const size_t index, const IReflectObject* object, IBuffer* outDst) const;
		void fromString(const size_t index, IReflectObject* object, const char* src, size_t strlen);
		void toString(const size_t index, const IReflectObject* object, IBuffer* outStringBuffer) const;

	protected:
		virtual IReflectPODProperty* getElementProperty(const size_t index, IReflectObject* object) = 0;
		virtual const IReflectPODProperty* getElementProperty(const size_t index, const IReflectObject* object) const = 0;
	};

	template<>
	struct ReflectCastHelper<IReflectPODSeqProperty>
	{
		static IReflectPODSeqProperty*		cast(IReflectProperty* prop);
		static const IReflectPODSeqProperty*	cast(const IReflectProperty* prop);
	};
}