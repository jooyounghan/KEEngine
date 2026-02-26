#pragma once
#include "MathUtil.h"

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
    class ReflectPropertyInfo;

    class IReflectPropertyInfoAccessor
    {
    protected:
        virtual void*       getPODPropertyInfoPtr() = 0;
        virtual const void* getPODPropertyInfoPtr() const = 0;

    public:
        template<typename PropertyType>
        ReflectPropertyInfo<PropertyType>* getPODPropertyInfo();

        template<typename PropertyType>
        const ReflectPropertyInfo<PropertyType>* getPODPropertyInfo() const;
    };

	template<typename PropertyType>
    class ReflectPropertyInfo
    {
    public:
        ReflectPropertyInfo() = default;
        virtual ~ReflectPropertyInfo() = default;

    public:
        inline void                 setDefaultValue(const PropertyType& defaultValue) { _defaultValue = defaultValue; }
        inline const PropertyType&  getDefaultValue() const { return _defaultValue; }

    public:
        inline bool                                     hasRangeInfo() const { return _rangeInfo != nullptr; }
        void                                            assignRangeInfo(const PropertyType& minValue, const PropertyType& maxValue, const PropertyType& step);
        inline const RangedPropertyInfo<PropertyType>*  getRangeInfo() const { return _rangeInfo.get(); }
        void                                            validateRange(PropertyType& value);

    protected:
        PropertyType                            _defaultValue;
        PTR(RangedPropertyInfo<PropertyType>)   _rangeInfo = nullptr;
    };
}
#include "ReflectPropertyInfo.hpp"