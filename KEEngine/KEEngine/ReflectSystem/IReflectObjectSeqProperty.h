#pragma once
#include "IReflectContainerProperty.h"

namespace ke
{
	class IBuffer;
	class IReflectObject;

	class IReflectObjectSeqProperty : public IReflectContainerProperty
	{
	public:
		IReflectObjectSeqProperty(const FlyweightStringA& name);
		~IReflectObjectSeqProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::ReflectObjectContainer; }

	protected:
		inline virtual void*		getInterface() override final { return static_cast<IReflectObjectSeqProperty*>(this); }
		inline virtual const void*	getInterface() const override final { return static_cast<const IReflectObjectSeqProperty*>(this); }

	public:
		virtual IReflectObject*			getReflectObject(const size_t index, IReflectObject* parentReflectObject) = 0;
		virtual const IReflectObject*	getReflectObject(const size_t index, const IReflectObject* parentReflectObject) const = 0;
	};

	template<>
	struct ReflectCastHelper<IReflectObjectSeqProperty>
	{
		static IReflectObjectSeqProperty*			cast(IReflectProperty* prop);
		static const IReflectObjectSeqProperty*	cast(const IReflectProperty* prop);
	};
}