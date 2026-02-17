#pragma once
#include "IReflectProperty.h"

namespace ke
{
	class IBuffer;
	class IReflectObject;

	class IReflectObjectContainerProperty : public IReflectProperty
	{
	public:
		IReflectObjectContainerProperty(const FlyweightStringA& name);
		~IReflectObjectContainerProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::ReflectObjectContainer; }

	protected:
		inline virtual void*		getInterface() override final { return static_cast<IReflectObjectContainerProperty*>(this); }
		inline virtual const void*	getInterface() const override final { return static_cast<const IReflectObjectContainerProperty*>(this); }

	public:
		virtual size_t getSize(const IReflectObject* parentReflectObject) const = 0;

	public:
		virtual IReflectObject*			getReflectObject(const size_t index, IReflectObject* parentReflectObject) = 0;
		virtual const IReflectObject*	getReflectObject(const size_t index, const IReflectObject* parentReflectObject) const = 0;
	};

	template<>
	struct ReflectCastHelper<IReflectObjectContainerProperty>
	{
		static IReflectObjectContainerProperty*			cast(IReflectProperty* prop);
		static const IReflectObjectContainerProperty*	cast(const IReflectProperty* prop);
	};
}