#include "pch.h"
#include "FileUtil.h"

namespace ke
{
    const char* FileUtil::findNext(const char* p, const char* end, char c) noexcept
    {
#if SIMD_ENABLED
        if (end - p >= SIMD_TARGET_BYTE)
        {
            const SIMD_VEC target = SIMD_SET1_EPI8(c);

            while (p + SIMD_TARGET_BYTE <= end)
            {
                SIMD_VEC chunk = SIMD_LOAD(p);
                SIMD_MASK_TYPE mask = SIMD_CMP_EPI8(chunk, target);

                if (mask)
                {
                    unsigned long index = 0;
                    SIMD_MASK_BSF(index, mask);
                    return p + index;
                }

                p += SIMD_TARGET_BYTE;
            }
        }
#endif
        while (p < end && *p != c)
            ++p;
        return p;
    }

    const char* FileUtil::findNameEnd(const char* p, const char* end) noexcept
    {
        while (p < end && FileUtil::isNameChar(*p)) ++p;
        return p;
    }

    CONSTEXPR_INLINE constexpr bool FileUtil::isWhitespace(char c) noexcept
    {
        return c == ' ' || c == '\t' || c == '\r' || c == '\n';
    }

    CONSTEXPR_INLINE constexpr bool FileUtil::isNameChar(char c) noexcept
    {
        return (c >= 'A' && c <= 'Z')
            || (c >= 'a' && c <= 'z')
            || (c >= '0' && c <= '9')
            || c == ':' || c == '_' || c == '-';
    }

    void FileUtil::skipWhitespace(const char*& p, const char* end) noexcept
    {
#if SIMD_ENABLED
        while (end - p >= SIMD_TARGET_BYTE)
        {

            SIMD_VEC chunk = SIMD_LOAD(p);
            SIMD_MASK_TYPE mask = SIMD_WHITESPACE_MASK(chunk);

            if (mask == SIMD_ALL_ONES_MASK)
            {
                p += SIMD_TARGET_BYTE;
                continue;
            }
            break;
        }
#endif

        while (p < end && FileUtil::isWhitespace(*p))
            ++p;
    }
}
