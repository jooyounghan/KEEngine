#include "ReflectPODProperty.h"
#pragma once
namespace ke
{
	template<typename T>
	const void* IReflectPODProperty::getStaticTypeId()
	{
		static char staticTypeId;
		return &staticTypeId;
	}

	template<typename PropertyType>
	ReflectPODPropertyBase<PropertyType>* IReflectPODProperty::getBase()
	{
		if (getTypeId() == getStaticTypeId<PropertyType>())
		{
			return static_cast<ReflectPODPropertyBase<PropertyType>*>(this);
		}
		return nullptr;
	}

	template<typename PropertyType>
	const ReflectPODPropertyBase<PropertyType>* IReflectPODProperty::getBase() const
	{
		if (getTypeId() == getStaticTypeId<PropertyType>())
		{
			return static_cast<const ReflectPODPropertyBase<PropertyType>*>(this);
		}
		return nullptr;
	}

	template<typename PropertyType>
	 const void* ReflectPODPropertyBase<PropertyType>::getTypeId() const
	{
		return IReflectPODProperty::getStaticTypeId<PropertyType>();
	}

	template<typename PropertyType>
	void ReflectPODPropertyBase<PropertyType>::assignRangeInfo(const PropertyType& minValue, const PropertyType& maxValue, const PropertyType& step)
	{
		_rangeInfo = MAKE_PTR(RangedPropertyInfo<PropertyType>);
		_rangeInfo->_minValue = minValue;
		_rangeInfo->_maxValue = maxValue;
		_rangeInfo->_step = step;
	}

	template<typename ObjectType, typename PropertyType>
	ReflectPODProperty<ObjectType, PropertyType>::ReflectPODProperty(
		const FlyweightStringA& name
		, Getter<ObjectType, PropertyType> getter
		, ConstGetter<ObjectType, PropertyType> constGetter
		, Setter<ObjectType, PropertyType> setter
	)
		: ReflectPropertyBase<ObjectType, PropertyType>(name, getter, constGetter, setter)
	{
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::setFromBianry(IReflectObject* object, const void* src)
	{
		ReflectParser::parseFromBinary(src, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::getToBinary(const IReflectObject* object, IBuffer* outDst) const
	{
		ReflectParser::parseToBinary(outDst, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::setFromString(IReflectObject* object, const char* src, size_t strlen)
	{
		ReflectParser::parseFromString(src, strlen , &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		ReflectParser::parseToString(outStringBuffer, &this->get(object));
	}
}