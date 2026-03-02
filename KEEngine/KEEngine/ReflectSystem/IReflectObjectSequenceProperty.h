#pragma once
#include "IReflectContainerProperty.h"

namespace ke
{
	class IBuffer;
	class IReflectObject;

	class IReflectObjectSequenceProperty : public IReflectSequenceContainerProperty
	{
	public:
		IReflectObjectSequenceProperty(const FlyweightStringA& name);
		~IReflectObjectSequenceProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::ReflectObjectSeqeunceContainer; }

	protected:
		inline virtual void*		getInterface() override final { return static_cast<IReflectObjectSequenceProperty*>(this); }
		inline virtual const void*	getInterface() const override final { return static_cast<const IReflectObjectSequenceProperty*>(this); }

	public:
		virtual IReflectObject*			getReflectObject(const size_t index, IReflectObject* parentReflectObject) = 0;
		virtual const IReflectObject*	getReflectObject(const size_t index, const IReflectObject* parentReflectObject) const = 0;
	};

	template<>
	struct ReflectCastHelper<IReflectObjectSequenceProperty>
	{
		static IReflectObjectSequenceProperty*			cast(IReflectProperty* prop);
		static const IReflectObjectSequenceProperty*	cast(const IReflectProperty* prop);
	};
}