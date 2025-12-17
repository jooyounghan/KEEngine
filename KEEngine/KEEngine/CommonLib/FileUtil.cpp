#include "CommonLibPch.h"
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

    const char* FileUtil::findSequence(const char* p, const char* end, const char* seq, size_t seqLen) noexcept
    {
        if (seqLen == 0) return p;
        if (p >= end) return end;
        if (seqLen == 1) return findNext(p, end, seq[0]);

        const char first = seq[0];
        const char* cur = p;

#if SIMD_ENABLED
        // SIMD 블록 단위로 첫 문자 위치 탐색
        if (end - cur >= SIMD_TARGET_BYTE)
        {
            SIMD_VEC target = SIMD_SET1_EPI8(first);
            while (cur + SIMD_TARGET_BYTE <= end)
            {
                SIMD_VEC chunk = SIMD_LOAD(cur);
                SIMD_MASK_TYPE mask = SIMD_CMP_EPI8(chunk, target);
                if (mask)
                {
                    // 마스크에 설정된 모든 비트(인덱스) 검사
                    while (mask)
                    {
                        unsigned long idx = 0;
                        SIMD_MASK_BSF(idx, mask);
                        const char* pos = cur + idx;
                        // 남은 길이 확인
                        if (static_cast<size_t>(end - pos) < seqLen) return end;
                        if (std::memcmp(pos, seq, seqLen) == 0) return pos;
                        // 가장 낮은 비트 제거
                        mask &= (mask - 1);
                    }
                }
                cur += SIMD_TARGET_BYTE;
            }
        }
#endif
        while (true)
        {
            // memchr requires length; cast away const for API but keep pointer arithmetic safe
            size_t remaining = static_cast<size_t>(end - cur);
            if (remaining == 0) return end;
            const void* found = std::memchr(cur, first, remaining);
            if (found == nullptr) return end;
            cur = static_cast<const char*>(found);
            // ensure enough room for full sequence
            if (static_cast<size_t>(end - cur) < seqLen) return end;
            if (std::memcmp(cur, seq, seqLen) == 0) return cur;
            ++cur; // continue searching after this position
        }
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
