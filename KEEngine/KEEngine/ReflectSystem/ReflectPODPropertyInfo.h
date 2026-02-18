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
    class ReflectPODPropertyInfo;

    class IReflectPODPropertyInfoAccessor
    {
    protected:
        virtual const void* getTypeId() const = 0;

    protected:
        template<typename T>
        static const void* getPODTypeId();

    public:
        template<typename PropertyType>
        ReflectPODPropertyInfo<PropertyType>* getPODPropertyInfo();
    };

	template<typename PropertyType>
    class ReflectPODPropertyInfo
    {
    public:
        ReflectPODPropertyInfo() = default;
        virtual ~ReflectPODPropertyInfo() = default;

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
#include "ReflectPODPropertyInfo.hpp"