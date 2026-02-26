namespace ke
{
    template<typename PropertyType>
    ReflectPropertyInfo<PropertyType>* IReflectPropertyInfoAccessor::getPropertyInfo()
    {
		return static_cast<ReflectPropertyInfo<PropertyType>*>(getPropertyInfoPtr());
    }

    template<typename PropertyType>
    const ReflectPropertyInfo<PropertyType>* IReflectPropertyInfoAccessor::getPropertyInfo() const
    {
		return static_cast<const ReflectPropertyInfo<PropertyType>*>(getPropertyInfoPtr());
    }

    template<typename PropertyType>
    void ReflectPropertyInfo<PropertyType>::assignRangeInfo(
        const PropertyType& minValue,
        const PropertyType& maxValue,
        const PropertyType& step
    )
    {
        _rangeInfo = MAKE_PTR(RangedPropertyInfo<PropertyType>);
        _rangeInfo->_minValue = minValue;
        _rangeInfo->_maxValue = maxValue;
        _rangeInfo->_step = step;
    }

    template<typename PropertyType>
    void ReflectPropertyInfo<PropertyType>::validateRange(PropertyType& value)
    {
        if (_rangeInfo.get() != nullptr)
        {
            value = MathUtil::max(_rangeInfo->_minValue, value);
            value = MathUtil::min(_rangeInfo->_maxValue, value);
        }
    }
}
