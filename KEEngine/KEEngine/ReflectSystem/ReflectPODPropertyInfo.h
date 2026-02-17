#pragma once

namespace ke
{
    template<typename PropertyType>
    struct RangedPropertyInfo
    {
        PropertyType    _maxValue;
        PropertyType    _minValue;
        PropertyType    _step;
    };

	template<typename PropertyType>
    class RefelctPODPropertyInfo
    {
    public:
        RefelctPODPropertyInfo() = default;
        virtual ~RefelctPODPropertyInfo() = default;

    public:
        inline void                 setDefaultValue(const PropertyType& defaultValue) { _defaultValue = defaultValue; }
        inline const PropertyType&  getDefaultValue() const { return _defaultValue; }

    public:
        inline bool                                     hasRangeInfo() const { return _rangeInfo != nullptr; }
        void                                            assignRangeInfo(const PropertyType& minValue, const PropertyType& maxValue, const PropertyType& step);
        inline const RangedPropertyInfo<PropertyType>*  getRangeInfo() const { return _rangeInfo.get(); }

    protected:
        PropertyType                            _defaultValue;
        PTR(RangedPropertyInfo<PropertyType>)   _rangeInfo = nullptr;
    };
}
#include "ReflectPODPropertyInfo.hpp"