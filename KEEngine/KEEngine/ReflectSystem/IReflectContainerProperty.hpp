#pragma once
namespace ke
{
	namespace ReflectContainerParser
	{
		template<typename T>
		static void parseToBinary(IBuffer* outBuffer, const T& value)
		{
			if constexpr (std::is_enum_v<T>)
			{
				const size_t enumValue = static_cast<size_t>(value);
				outBuffer->write(&enumValue, sizeof(size_t));
			}
			else
			{
				ReflectParser::parseToBinary(outBuffer, &value);
			}
		}

		template<typename T>
		static void parseToString(IBuffer* outBuffer, const T& value)
		{
			if constexpr (std::is_enum_v<T>)
			{
				const std::string& enumString = EnumWrapper<T>::toString(value);
				outBuffer->write(enumString.c_str(), enumString.length());
			}
			else
			{
				ReflectParser::parseToString(outBuffer, &value);
			}
		}

		template<typename T>
		static Offset parseFromBinary(const void* src, T& value)
		{
			if constexpr (std::is_enum_v<T>)
			{
				value = static_cast<T>(*static_cast<const size_t*>(src));
				return sizeof(size_t);
			}
			else
			{
				return ReflectParser::parseFromBinary(src, &value);
			}

		}

		template<typename T>
		static void parseFromString(const char* src, size_t strLen, T& value)
		{
			if constexpr (std::is_enum_v<T>)
			{
				std::optional<T> optVal = EnumWrapper<T>::fromString(std::string_view(src, strLen));
				if (optVal.has_value())
				{
					value = optVal.value();
				}
			}
			else
			{
				ReflectParser::parseFromString(src, strLen, &value);
			}
		}
	}
}