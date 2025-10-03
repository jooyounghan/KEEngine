#pragma once
#include "StringConvertor.h"

#include "TemplateCommon.h"
#define DECLARE_Z_CONVERTOR(Type) template<> void StringConvertor::convertToStringBuffer(IStaticBuffer* outStaticBuffer, const Type& v);    
#define DECLARE_F_CONVERTOR(Type) template<> void StringConvertor::convertToStringBuffer(IStaticBuffer* outStaticBuffer, const Type& v, int precision);

namespace ke
{
    template<typename T, typename ...Args>
    void StringConvertor::convertToStringBuffer(IStaticBuffer* outStaticBuffer, const T& v, Args ...args)
    {
        STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(StringConvertor);
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