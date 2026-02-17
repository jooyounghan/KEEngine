#pragma once
#include "IReflectProperty.h"
#include "IReflectObjectProperty.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectObjectProperty : public ReflectPropertyBase<ObjectType, PropertyType>, public IReflectObjectProperty
	{
	public:
		ReflectObjectProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);
		~ReflectObjectProperty() override = default;

	public:
		// New type system
		inline virtual EReflectPropertyType getPropertyType() const override { return EReflectPropertyType::Object; }

	protected:
		// Override helper methods for type-safe conversion
		inline virtual IReflectObjectProperty* asIReflectObjectProperty() override { return this; }
		inline virtual const IReflectObjectProperty* asIReflectObjectProperty() const override { return this; }

	public:
		// IReflectObjectProperty implementation
		inline virtual IReflectObject* getReflectObject(IReflectObject* parentReflectObject) override 
		{ 
			return static_cast<IReflectObject*>(&this->get(parentReflectObject)); 
		}
		inline virtual const IReflectObject* getReflectObject(const IReflectObject* parentReflectObject) const override 
		{ 
			return static_cast<const IReflectObject*>(&this->get(parentReflectObject)); 
		}

	public:
		virtual void setFromBianry(IReflectObject* object, const void* src) override;
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const override;
		virtual void setFromString(IReflectObject* object, const char* src, size_t strlen) override;
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
	};
}
#include "ReflectObjectProperty.hpp"