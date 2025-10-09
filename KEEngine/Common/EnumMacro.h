#pragma once
#include "MacroUtilities.h"
#include "Vector.h"
#include "OwnedString.h"

#define DECLARE_ENUM_CLASS(EnumName, EnumType, ...) enum class EnumName : EnumType { __VA_ARGS__ }

#define DECLARE_ENUM_CLASS_STRING_TABLE(EnumName, ...) static const ke::Vector<ke::OwnedStringA> _stringTable##EnumName

#define DECLARE_ENUM_DESCRIPTOR(EnumName, EnumType, ...)    \
    DECLARE_ENUM_CLASS(EnumName, EnumType, __VA_ARGS__);    

#define DEFINE_ENUM_DESCRIPTOR(EnumName, ...)                       \
    const ke::Vector<ke::OwnedStringA> _stringTable##EnumName = {   \
        KE_FOR_EACH(STRIZE, ,, __VA_ARGS__)                         \
    }

#define GET_ENUM_STRING_TABLE(EnumName) _stringTable##EnumName

#define DECLARE_BY_INDEX(Class, Index) Class KE_CAT3(col_, _, Index)
