#define KE_ENUM_PREF_VAL(EnumName, Val) EnumName::Val

#define DEFINE_ENUM_FLAG_OPERATORS(EnumName)                                        \
    inline EnumName operator|(EnumName lhs, EnumName rhs)                           \
    {                                                                               \
        using T = std::underlying_type_t<EnumName>;                                 \
        return static_cast<EnumName>(static_cast<T>(lhs) | static_cast<T>(rhs));    \
    }                                                                               \
                                                                                    \
    inline EnumName operator&(EnumName lhs, EnumName rhs)                           \
    {                                                                               \
        using T = std::underlying_type_t<EnumName>;                                 \
        return static_cast<EnumName>(static_cast<T>(lhs) & static_cast<T>(rhs));    \
    }                                                                               \
                                                                                    \
    inline EnumName& operator|=(EnumName& lhs, EnumName rhs)                        \
    {                                                                               \
        return lhs = lhs | rhs;                                                     \
    }                                                                               \
                                                                                    \
    inline EnumName& operator&=(EnumName& lhs, EnumName rhs)                        \
    {                                                                               \
        return lhs = lhs & rhs;                                                     \
    }

#define DECLARE_REFLECT_ENUM(EnumName)                                                                  \
template<> const std::unordered_map<size_t, std::string>& EnumWrapper<EnumName>::getStringTable();      \
template<> std::string EnumWrapper<EnumName>::toString(EnumName val);                                   \
template<> std::optional<EnumName> EnumWrapper<EnumName>::fromString(const std::string_view& str);

#define DECLARE_REFLECT_ENUM_FLAG(EnumName)     \
DEFINE_ENUM_FLAG_OPERATORS(EBlendColorMask);    \
DECLARE_REFLECT_ENUM(EnumName);

#define DEFINE_REFLECT_ENUM(EnumName, ...)                                                                                                  \
    template<> const std::unordered_map<size_t, std::string>& EnumWrapper<EnumName>::getStringTable()                                       \
    {                                                                                                                                       \
        static const std::unordered_map<size_t, std::string> stringTable = [] {                                                             \
            std::vector<std::string> n = { KE_FOR_EACH(STRIZE, KE_COMMA, __VA_ARGS__) };                                                    \
            std::vector<EnumName> v = { KE_FOR_EACH_WITH_FIXED(KE_ENUM_PREF_VAL, KE_COMMA, EnumName, __VA_ARGS__) };                        \
            std::unordered_map<size_t, std::string> result;                                                                                 \
            for(size_t i = 0; i < v.size(); ++i) result[static_cast<size_t>(v[i])] = n[i];                                                  \
            return result;                                                                                                                  \
        }();                                                                                                                                \
        return stringTable;                                                                                                                 \
    }                                                                                                                                       \
                                                                                                                                            \
    template<> std::string EnumWrapper<EnumName>::toString(EnumName val)                                                                    \
    {                                                                                                                                       \
        static const std::string unknownString = "Unknown";                                                                                 \
        const std::unordered_map<size_t, std::string>& stringTable = getStringTable();                                                      \
        return stringTable.find(static_cast<size_t>(val)) != stringTable.end() ? stringTable.at(static_cast<size_t>(val)) : unknownString;  \
    }                                                                                                                                       \
                                                                                                                                            \
    template<> std::optional<EnumName> EnumWrapper<EnumName>::fromString(const std::string_view& str)                                 \
    {                                                                                                                                       \
        const std::unordered_map<size_t, std::string>& stringTable = getStringTable();                                                      \
        for (const auto& [key, value] : stringTable)                                                                                        \
        {                                                                                                                                   \
            if (value == str)                                                                                                               \
            {                                                                                                                               \
                return std::make_optional(static_cast<EnumName>(key));                                                                      \
            }                                                                                                                               \
        }                                                                                                                                   \
        return std::nullopt;                                                                                                                \
    };

#define DEFINE_REFLECT_ENUM_FLAG(EnumName, ...)                                                                             \
    template<> const std::unordered_map<size_t, std::string>& EnumWrapper<EnumName>::getStringTable()                       \
    {                                                                                                                       \
        static const std::unordered_map<size_t, std::string> stringTable = [] {                                             \
            std::vector<std::string> n = { KE_FOR_EACH(STRIZE, KE_COMMA, __VA_ARGS__) };                                    \
            std::vector<EnumName> v = { KE_FOR_EACH_WITH_FIXED(KE_ENUM_PREF_VAL, KE_COMMA, EnumName, __VA_ARGS__) };        \
            std::unordered_map<size_t, std::string> res;                                                                    \
            for(size_t i = 0; i < v.size(); ++i) res[static_cast<size_t>(v[i])] = n[i];                                     \
            return res;                                                                                                     \
        }();                                                                                                                \
        return stringTable;                                                                                                 \
    }                                                                                                                       \
                                                                                                                            \
    template<> std::string EnumWrapper<EnumName>::toString(EnumName val)                                                    \
    {                                                                                                                       \
        size_t raw = static_cast<size_t>(val);                                                                              \
        if (raw == 0) return "None";                                                                                        \
        std::string res;                                                                                                    \
        for (const auto& [bit, name] : getStringTable()) {                                                                  \
            if (bit != 0 && (raw & bit) == bit) {                                                                           \
                if (!res.empty()) res += "|";                                                                               \
                res += name;                                                                                                \
            }                                                                                                               \
        }                                                                                                                   \
        return res.empty() ? "Unknown" : res;                                                                               \
    }                                                                                                                       \
                                                                                                                            \
    template<> std::optional<EnumName> EnumWrapper<EnumName>::fromString(const std::string_view& str)                       \
    {                                                                                                                       \
        size_t combined = 0;                                                                                                \
        for (const auto& [bit, name] : getStringTable()) if (str.find(name) != std::string_view::npos) combined |= bit;     \
        return (combined != 0) ? std::make_optional(static_cast<EnumName>(combined)) : std::nullopt;                        \
    }