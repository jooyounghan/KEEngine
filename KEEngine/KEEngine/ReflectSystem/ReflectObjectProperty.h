#pragma once
#include "IReflectProperty.h"

namespace ke
{
	template<typename ObjectType, typename PropertyType>
	class ReflectObjectProperty : public ReflectPropertyBase<ObjectType, PropertyType>
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

	public:
		// Legacy compatibility
		inline virtual bool isReflectObject() const override { return true; };
		inline virtual IReflectObject* getReflectObject(IReflectObject* parentReflectObject) override { return static_cast<IReflectObject*>(&this->get(parentReflectObject)); }
		inline virtual const IReflectObject* getReflectObject(const IReflectObject* parentReflectObject) const override { return static_cast<const IReflectObject*>(&this->get(parentReflectObject)); }

	public:
		// Legacy compatibility
		inline virtual bool isPODProperty() const override { return false; }
		inline virtual IReflectPODProperty* getPODProperty() override { return nullptr; }
		inline virtual const IReflectPODProperty* getPODProperty() const override { return nullptr; };

	public:
		virtual void setFromBianry(IReflectObject* object, const void* src) override;
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const override;
		virtual void setFromString(IReflectObject* object, const char* src, size_t strlen) override;
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
	};
}
#include "ReflectObjectProperty.hpp"