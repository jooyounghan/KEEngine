#include "StrUtil.h"

#define DECLARE_Z_CONVERTOR_SPECIALIZATION(Type) template<> void StrUtil::convertToStringBuffer(IBuffer* outStaticBuffer, const Type& v);    
#define DECLARE_F_CONVERTOR_SPECIALIZATION(Type) template<> void StrUtil::convertToStringBuffer(IBuffer* outStaticBuffer, const Type& v, int precision);

namespace ke
{
    template<typename T, typename ...Args>
    void StrUtil::convertToStringBuffer(IBuffer* outStaticBuffer, const T& v, Args ...args)
    {
        STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(StringConvertor);
    }

    DECLARE_Z_CONVERTOR_SPECIALIZATION(bool);

    DECLARE_Z_CONVERTOR_SPECIALIZATION(uint64);
    DECLARE_Z_CONVERTOR_SPECIALIZATION(uint32);
    DECLARE_Z_CONVERTOR_SPECIALIZATION(uint16);
    DECLARE_Z_CONVERTOR_SPECIALIZATION(uint8);
    DECLARE_Z_CONVERTOR_SPECIALIZATION(int64);
    DECLARE_Z_CONVERTOR_SPECIALIZATION(int32);
    DECLARE_Z_CONVERTOR_SPECIALIZATION(int16);
    DECLARE_Z_CONVERTOR_SPECIALIZATION(int8);

    DECLARE_F_CONVERTOR_SPECIALIZATION(double);
    DECLARE_F_CONVERTOR_SPECIALIZATION(float);



    template<typename T>
    bool StrUtil::parseStringViewToInteger(std::string_view sv, T& out)
    {
        const char* first = sv.data();
        const char* last = sv.data() + sv.size();

        auto [ptr, ec] = std::from_chars(first, last, out, 10);
        if (ec != std::errc{}) return false;
        if (ptr == first) return false;
        return true;
    }

    template<typename T>
    bool ke::StrUtil::parseStringViewToFloating(std::string_view sv, T& out)
    {
        const char* first = sv.data();
        const char* last = sv.data() + sv.size();

        auto [ptr, ec] = std::from_chars(first, last, out, std::chars_format::general);
        if (ec != std::errc{}) return false;
        if (ptr == first) return false;
        return true;
    }
}