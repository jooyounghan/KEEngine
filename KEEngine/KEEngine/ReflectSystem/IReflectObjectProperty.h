#pragma once
#include "IReflectProperty.h"
#include "IReflectObject.h"

namespace ke
{
	class IReflectObjectProperty : public IReflectProperty
	{
	public:
		IReflectObjectProperty(const FlyweightStringA& name);
		~IReflectObjectProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::ReflectObject; }

	protected:
		inline virtual void*		getInterface() override final { return static_cast<IReflectObjectProperty*>(this); }
		inline virtual const void*	getInterface() const override final { return static_cast<const IReflectObjectProperty*>(this); }

	public:
		virtual IReflectObject*			getReflectObject(IReflectObject* parentReflectObject) = 0;
		virtual const IReflectObject*	getReflectObject(const IReflectObject* parentReflectObject) const = 0;
	};

    template<>
    struct ReflectCastHelper<IReflectObjectProperty>
    {
        static IReflectObjectProperty*			cast(IReflectProperty* prop);
        static const IReflectObjectProperty*	cast(const IReflectProperty* prop);
    };
}