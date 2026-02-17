#pragma once
#include "IReflectProperty.h"

namespace ke
{
	class IBuffer;
	class IReflectObject;

	class IReflectPODProperty : public IReflectProperty
	{
	public:
		IReflectPODProperty(const FlyweightStringA& name);
		~IReflectPODProperty() override = default;

	public:
		inline virtual EReflectPropertyType getType() const override final { return EReflectPropertyType::POD; }

	protected:
		inline virtual void*		getInterface() override final { return static_cast<IReflectPODProperty*>(this); }
		inline virtual const void*	getInterface() const override final { return static_cast<const IReflectPODProperty*>(this); }

	public:
		virtual void fromBianry(IReflectObject* object, const void* src) = 0;
		virtual void toBinary(const IReflectObject* object, IBuffer* outDst) const = 0;
		virtual void fromString(IReflectObject* object, const char* src, size_t strlen) = 0;
		virtual void toString(const IReflectObject* object, IBuffer* outStringBuffer) const = 0;
	};

    template<>
    struct ReflectCastHelper<IReflectPODProperty>
    {
        static IReflectPODProperty*			cast(IReflectProperty* prop);
        static const IReflectPODProperty*	cast(const IReflectProperty* prop);
    };
}
#include "IReflectPODProperty.hpp"