#pragma once
#include "IReflectProperty.h"
#include "IReflectVectorProperty.h"
#include <vector>

namespace ke
{
	template<typename ObjectType, typename ElementType>
	class ReflectVectorProperty : public IReflectVectorProperty, public ReflectPropertyBase<ObjectType, std::vector<ElementType>>
	{
	public:
		ReflectVectorProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, std::vector<ElementType>> getter
			, ConstGetter<ObjectType, std::vector<ElementType>> constGetter
			, Setter<ObjectType, std::vector<ElementType>> setter
		);
		~ReflectVectorProperty() override = default;

	public:
		// New type system
		inline virtual EReflectPropertyType getPropertyType() const override { return EReflectPropertyType::Vector; }

	protected:
		// Override helper methods for type-safe conversion
		inline virtual IReflectVectorProperty* asIReflectVectorProperty() override { return this; }
		inline virtual const IReflectVectorProperty* asIReflectVectorProperty() const override { return this; }

	public:
		// IReflectVectorProperty implementation
		virtual size_t getSize(const IReflectObject* object) const override;
		virtual void resize(IReflectObject* object, size_t newSize) override;
		virtual void clear(IReflectObject* object) override;
		virtual void* getElement(IReflectObject* object, size_t index) override;
		virtual const void* getElement(const IReflectObject* object, size_t index) const override;

	public:
		virtual void setFromBianry(IReflectObject* object, const void* src) override;
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const override;
		virtual void setFromString(IReflectObject* object, const char* src, size_t strlen) override;
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
	};
}
#include "ReflectVector.hpp"
