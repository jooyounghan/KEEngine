#pragma once
#include "MacroUtilities.h"
#include "Vector.h"
#include "OwnedString.h"

#define DEFINE_ENUM_CLASS_WITH_STRINGS(EnumName, ...)                       \
    enum class EnumName : uint8_t { __VA_ARGS__ };                          \
    static const ke::Vector<ke::OwnedStringA> EnumName##String = {          \
        KE_FOR_EACH(STRIZE, __VA_ARGS__)                                    \
    };
