#pragma once
#include "StringConvertor.h"

#define DECLARE_Z_CONVERTOR(Type)                                                                                                           \
    template<> OwnedStringA StringConvertor::convertToString(const Type& v);                                                                \
    template<> void StringConvertor::convertToString(StaticBuffer<KEConstant::kStringConvertorBufferSize>& outStringBuffer, const Type& v);    

#define DECLARE_F_CONVERTOR(Type)                                                                                                                           \
    template<> OwnedStringA StringConvertor::convertToString(const Type& v, int precision);                                                                 \
    template<> void StringConvertor::convertToString(StaticBuffer<KEConstant::kStringConvertorBufferSize>& outStringBuffer, const Type& v, int precision);

namespace ke
{
    template<typename T, typename ...Args>
    void StringConvertor::convertToString(IStaticBuffer* staticBuffer, const T& v, Args ...args)
    {
        static_assert(false, "This type is not supported as StringConvertor::convertToString.");
    }

	DECLARE_Z_CONVERTOR(bool);

    DECLARE_Z_CONVERTOR(uint64);
    DECLARE_Z_CONVERTOR(uint32);
    DECLARE_Z_CONVERTOR(uint16);
    DECLARE_Z_CONVERTOR(uint8);
    DECLARE_Z_CONVERTOR(int64);
    DECLARE_Z_CONVERTOR(int32);
    DECLARE_Z_CONVERTOR(int16);
    DECLARE_Z_CONVERTOR(int8);

    DECLARE_F_CONVERTOR(double);
    DECLARE_F_CONVERTOR(float);
}