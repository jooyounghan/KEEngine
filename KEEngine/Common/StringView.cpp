#include "StringView.h"

namespace ke
{
    template<>
    size_t HashGenerator<StringView<char>>::convertToHash(const StringView<char>& value)
    {
        return computeHash(value.data(), value.length());
    }
}