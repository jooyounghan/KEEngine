namespace ke
{
    template<typename PropertyType>
    void ke::RefelctPODPropertyInfo<PropertyType>::assignRangeInfo(
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
}