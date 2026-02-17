#pragma once
#include "IReflectProperty.h"

namespace ke
{
	template<typename PropertyType>
	class IReflectVectorProperty : public IReflectStaticTypeId
	{
	protected:
		virtual const void* getTypeId() const override;

	public:
		virtual std::vector<PropertyType>& getVector(IReflectObject* object) = 0;
		virtual const std::vector<PropertyType>& getVector(const IReflectObject* object) const = 0;
	};

	template<typename ObjectType, typename PropertyType>
	class ReflectVectorProperty : public IReflectVectorProperty<PropertyType>, public ReflectPropertyBase<ObjectType, std::vector<PropertyType>>
	{
	public:
		ReflectVectorProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, std::vector<PropertyType>> getter
			, ConstGetter<ObjectType, std::vector<PropertyType>> constGetter
			, Setter<ObjectType, std::vector<PropertyType>> setter
		);
		~ReflectVectorProperty() override = default;

	protected:
		virtual void* getInterface() override { return static_cast<IReflectVectorProperty<PropertyType>*>(this); }
		virtual const void* getInterface() const override { return static_cast<const IReflectVectorProperty<PropertyType>*>(this); }

	public:
		virtual inline std::vector<PropertyType>& getVector(IReflectObject* object) override { return this->get(object); }
		virtual inline const std::vector<PropertyType>& getVector(IReflectObject* object) const override { return this->get(object); }

	public:
		inline virtual EReflectPropertyType getPropertyType() const override { return EReflectPropertyType::Vector; }
		virtual void setFromBianry(IReflectObject* object, const void* src) override;
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const override;
		virtual void setFromString(IReflectObject* object, const char* src, size_t strlen) override;
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
	};
}
#include "ReflectVector.hpp"
