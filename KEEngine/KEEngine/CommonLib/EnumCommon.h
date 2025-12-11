#pragma once
#include "CommonLibPch.h"
#include "MacroCommon.h"

#define DECLARE_ENUM_CLASS(EnumName, EnumType, ...) enum class EnumName : EnumType { __VA_ARGS__ }

#define DEFINE_ENUM_DESCRIPTOR(EnumName, ...)                       \
    const std::vector<std::string> _stringTable##EnumName = {       \
        KE_FOR_EACH(STRIZE, KE_COMMA, __VA_ARGS__)                  \
    }

#define DECLARE_ENUM_CLASS_IN_CLASS(ClassName, EnumName, EnumType, ...)  \
    DECLARE_ENUM_CLASS(EnumName, EnumType, __VA_ARGS__);                 \
    static const std::vector<std::string> _stringTable##EnumName

#define DEFINE_ENUM_DESCRIPTOR_IN_CLASS(ClassName, EnumName, ...)           \
    const std::vector<std::string> ClassName::_stringTable##EnumName = {    \
        KE_FOR_EACH(STRIZE, KE_COMMA, __VA_ARGS__)                          \
    }

#define GET_ENUM_STRING_TABLE(EnumName) _stringTable##EnumName

#define GET_ENUM_STRING(EnumName, enumValue) \
    (static_cast<size_t>(enumValue) < GET_ENUM_STRING_TABLE(EnumName).size() ? GET_ENUM_STRING_TABLE(EnumName)[static_cast<size_t>(enumValue)].c_str() : "Unknown")