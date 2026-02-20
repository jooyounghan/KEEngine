#define KE_ENUM_PREF_VAL(EnumName, Val) EnumName::Val

#define DEFINE_ENUM_DESCRIPTOR(EnumName, ...)                                                                                   \
    template <>                                                                                                                 \
    struct EnumWrapper<EnumName>                                                                                                \
    {                                                                                                                           \
        static const std::unordered_map<size_t, std::string>& getStringMap()                                                    \
        {                                                                                                                       \
            static const std::unordered_map<size_t, std::string> stringTable = [] {                                             \
                std::vector<std::string> n = { KE_FOR_EACH(STRIZE, KE_COMMA, __VA_ARGS__) };                                    \
                std::vector<EnumName> v = { KE_FOR_EACH_WITH_FIXED(KE_ENUM_PREF_VAL, KE_COMMA, EnumName, __VA_ARGS__) };        \
                std::unordered_map<size_t, std::string> result;                                                                 \
                for(size_t i = 0; i < v.size(); ++i) result[static_cast<size_t>(v[i])] = n[i];                                  \
                return result;                                                                                                  \
            }();                                                                                                                \
            return stringTable;                                                                                                 \
        }                                                                                                                       \
    }

namespace ke
{
	template<typename T>
	const std::string& EnumWrapper<T>::toString(T val)
	{
		static const std::string unknownString = "Unknown";
		const std::unordered_map<size_t, std::string>& stringTable = EnumWrapper<T>::getStringTable();
		return stringTable.find(static_cast<size_t>(val)) != stringTable.end() ? stringTable.at(static_cast<size_t>(val)) : unknownString;
	}

	template<typename T>
	const std::optional<T> EnumWrapper<T>::fromString(const std::string_view& str)
	{
		const std::unordered_map<size_t, std::string>& stringTable = EnumWrapper<T>::getStringTable();
		for (const auto& [key, value] : stringTable)
		{
			if (value == str)
			{
				return static_cast<T>(key);
			}
		}
		return std::nullopt;
	}
}