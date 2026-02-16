#pragma once
#include "IReflectProperty.h"

namespace ke
{
	template<typename PropertyType>
	struct RangedPropertyInfo
	{
		PropertyType	_maxValue;
		PropertyType	_minValue;
		PropertyType	_step;
	};

	class IReflectPODProperty
	{
	public:
		virtual ~IReflectPODProperty() = default;

	protected:
		virtual const void* getTypeId() const = 0;
		template<typename T>
		static const void* getStaticTypeId();

	public:
		template<typename PropertyType>
		ReflectPODPropertyBase<PropertyType>* getBase();
		template<typename PropertyType>
		const ReflectPODPropertyBase<PropertyType>* getBase() const;
	};


	template<typename PropertyType>
	class ReflectPODPropertyBase : public IReflectPODProperty
	{
	protected:
		virtual const void* getTypeId() const override;

	public:
		inline void setDefaultValue(const PropertyType& defaultValue) { _defaultValue = defaultValue; }
		inline const PropertyType& getDefaultValue() const { return _defaultValue; }

	public:
		inline bool hasRange() const { return _rangeInfo != nullptr; }
		void assignRangeInfo(const PropertyType& minValue, const PropertyType& maxValue, const PropertyType& step);
		inline const RangedPropertyInfo<PropertyType>* getRangeInfo() const { return _rangeInfo.get(); }

	protected:
		PTR(RangedPropertyInfo<PropertyType>) _rangeInfo = nullptr;

	protected:
		PropertyType	_defaultValue;
	};

	template<typename ObjectType, typename PropertyType>
	class ReflectPODProperty : public ReflectPODPropertyBase<PropertyType>, public ReflectPropertyBase<ObjectType, PropertyType>
	{
	public:
		ReflectPODProperty(
			const FlyweightStringA& name
			, Getter<ObjectType, PropertyType> getter
			, ConstGetter<ObjectType, PropertyType> constGetter
			, Setter<ObjectType, PropertyType> setter
		);
		~ReflectPODProperty() override = default;

	public:
		// New type system
		inline virtual EReflectPropertyType getPropertyType() const override { return EReflectPropertyType::POD; }

	public:
		virtual void setFromBianry(IReflectObject* object, const void* src) override;
		virtual void getToBinary(const IReflectObject* object, IBuffer* outDst) const override;
		virtual void setFromString(IReflectObject* object, const char* src, size_t strlen) override;
		virtual void getToString(const IReflectObject* object, IBuffer* outStringBuffer) const override;
	};
}
#include "ReflectPODProperty.hpp"