#pragma once
#include "IReflectContainerProperty.h"

namespace ke
{
	class IBuffer;
	class IReflectObject;

	class IReflectObjectSeqeunceContainerProperty : public IReflectContainerProperty
	{
	public:
		IReflectObjectSeqeunceContainerProperty(const FlyweightStringA& name);
		~IReflectObjectSeqeunceContainerProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::ReflectObjectContainer; }

	protected:
		inline virtual void*		getInterface() override final { return static_cast<IReflectObjectSeqeunceContainerProperty*>(this); }
		inline virtual const void*	getInterface() const override final { return static_cast<const IReflectObjectSeqeunceContainerProperty*>(this); }

	public:
		virtual IReflectObject*			getReflectObject(const size_t index, IReflectObject* parentReflectObject) = 0;
		virtual const IReflectObject*	getReflectObject(const size_t index, const IReflectObject* parentReflectObject) const = 0;
	};

	template<>
	struct ReflectCastHelper<IReflectObjectSeqeunceContainerProperty>
	{
		static IReflectObjectSeqeunceContainerProperty*			cast(IReflectProperty* prop);
		static const IReflectObjectSeqeunceContainerProperty*	cast(const IReflectProperty* prop);
	};
}