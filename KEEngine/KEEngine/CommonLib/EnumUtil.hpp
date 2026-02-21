#define KE_ENUM_PREF_VAL(EnumName, Val) EnumName::Val

#define DEFINE_ENUM_DESCRIPTOR(EnumName, ...)                                                                                                   \
    template <>                                                                                                                                 \
    struct EnumWrapper<EnumName>                                                                                                                \
    {                                                                                                                                           \
        static const std::unordered_map<size_t, std::string>& getStringTable()                                                                  \
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
        static const std::string& toString(EnumName val)                                                                                        \
        {                                                                                                                                       \
            static const std::string unknownString = "Unknown";                                                                                 \
            const std::unordered_map<size_t, std::string>& stringTable = getStringTable();                                                      \
            return stringTable.find(static_cast<size_t>(val)) != stringTable.end() ? stringTable.at(static_cast<size_t>(val)) : unknownString;  \
        }                                                                                                                                       \
                                                                                                                                                \
        static const std::optional<EnumName> fromString(const std::string_view& str)                                                            \
        {                                                                                                                                       \
            const std::unordered_map<size_t, std::string>& stringTable = getStringTable();                                                      \
            for (const auto& [key, value] : stringTable)                                                                                        \
            {                                                                                                                                   \
                if (value == str)                                                                                                               \
                {                                                                                                                               \
                    return static_cast<EnumName>(key);                                                                                          \
                }                                                                                                                               \
            }                                                                                                                                   \
            return std::nullopt;                                                                                                                \
        }                                                                                                                                       \
    };