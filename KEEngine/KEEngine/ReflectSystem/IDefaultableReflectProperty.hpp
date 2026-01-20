#pragma once
namespace ke
{
	template<typename PropertyType>
	void IDefaultableReflectProperty<PropertyType>::assignRangeInfo(const PropertyType& minValue, const PropertyType& maxValue, const PropertyType& step)
	{
		_rangeInfo = MAKE_PTR(RangedPropertyInfo<PropertyType>);
		_rangeInfo->minValue = minValue;
		_rangeInfo->maxValue = maxValue;
		_rangeInfo->step = step;
	}

	template<typename PropertyType>
	void IDefaultableReflectProperty<PropertyType>::setDefaultFromBuffer(const void* data, size_t size)
	{
		STATIC_ASSERT(size == sizeof(PropertyType), "IDefaultableReflectProperty::setDefaultFromBuffer size mismatch");
		_defaultValue = *static_cast<const PropertyType*>(data);
	}

	template<typename PropertyType>
	void IDefaultableReflectProperty<PropertyType>::assignRangeInfoFromBuffer(const void* min, const void* max, const void* step, size_t elemSize)
	{
		STATIC_ASSERT(elemSize == sizeof(PropertyType), "IDefaultableReflectProperty::assignRangeInfoFromBuffer size mismatch");
		assignRangeInfo(
			*static_cast<const PropertyType*>(min),
			*static_cast<const PropertyType*>(max),
			*static_cast<const PropertyType*>(step)
		);
	}
}