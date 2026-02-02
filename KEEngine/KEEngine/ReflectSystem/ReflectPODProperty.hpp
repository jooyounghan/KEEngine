#pragma once
namespace ke
{
	template<typename PropertyType>
	void ReflectPODPropertyBase<PropertyType>::assignRangeInfo(const PropertyType& minValue, const PropertyType& maxValue, const PropertyType& step)
	{
		_rangeInfo = MAKE_PTR(RangedPropertyInfo<PropertyType>);
		_rangeInfo->_minValue = minValue;
		_rangeInfo->_maxValue = maxValue;
		_rangeInfo->_step = step;
	}

	template<typename PropertyType>
	void ReflectPODPropertyBase<PropertyType>::setDefaultFromBuffer(const void* data, size_t size)
	{
		KE_ASSERT_DEV(size == sizeof(PropertyType), "IDefaultableReflectProperty::setDefaultFromBuffer size mismatch");
		_defaultValue = *static_cast<const PropertyType*>(data);
	}

	template<typename PropertyType>
	void ReflectPODPropertyBase<PropertyType>::assignRangeInfoFromBuffer(const void* min, const void* max, const void* step, size_t elemSize)
	{
		KE_ASSERT_DEV(elemSize == sizeof(PropertyType), "IDefaultableReflectProperty::assignRangeInfoFromBuffer size mismatch");
		assignRangeInfo(
			*static_cast<const PropertyType*>(min),
			*static_cast<const PropertyType*>(max),
			*static_cast<const PropertyType*>(step)
		);
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
	void ReflectPODProperty<ObjectType, PropertyType>::setFromString(IReflectObject* object, const char* src)
	{
		ReflectParser::parseFromString(src, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		ReflectParser::parseToString(outStringBuffer, &this->get(object));
	}
}