namespace ke
{
    template<typename T>
    const void* IReflectPODPropertyInfoAccessor::getPODTypeId()
    {
        static char staticTypeId;
        return &staticTypeId;
    }

    template<typename PropertyType>
    ReflectPODPropertyInfo<PropertyType>* IReflectPODPropertyInfoAccessor::getPODPropertyInfo()
    {
		return this->getTypeId() == getPODTypeId<PropertyType>() ? dynamic_cast<ReflectPODPropertyInfo<PropertyType>*>(this) : nullptr;
    }

    template<typename PropertyType>
    const ReflectPODPropertyInfo<PropertyType>* IReflectPODPropertyInfoAccessor::getPODPropertyInfo() const
    {
		return this->getTypeId() == getPODTypeId<PropertyType>() ? dynamic_cast<const ReflectPODPropertyInfo<PropertyType>*>(this) : nullptr;
    }

    template<typename PropertyType>
    void ReflectPODPropertyInfo<PropertyType>::assignRangeInfo(
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
    void ReflectPODPropertyInfo<PropertyType>::validateRange(PropertyType& value)
    {
        if (_rangeInfo.get() != nullptr)
        {
            value = MathUtil::max(_rangeInfo->_minValue, value);
            value = MathUtil::min(_rangeInfo->_maxValue, value);
        }
    }
}