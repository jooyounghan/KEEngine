#include "CommonLibPch.h"
#include "XmlStruct.h"
#include "StrUtil.h"

#include <cstring>
#include <string_view>

namespace ke
{
	XMLAttribute::XMLAttribute(const char* pos)
	{
		if (pos == nullptr)
		{
			_currentPos = nullptr;
			return;
		}

		const char* p = pos;
		const char* end = pos + std::strlen(pos);

		// skip leading whitespace
		StrUtil::skipWhitespace(p, end);
		if (p >= end || !StrUtil::isNameChar(*p))
		{
			_currentPos = nullptr;
			return;
		}

		// name
		_nameStart = p;
		const char* nameEnd = StrUtil::findNameEnd(p, end);
		_nameLength = static_cast<size_t>(nameEnd - _nameStart);
		p = nameEnd;

		// skip whitespace and expect '='
		StrUtil::skipWhitespace(p, end);
		if (p >= end || *p != '=')
		{
			_currentPos = nullptr;
			return;
		}
		++p;

		// skip whitespace and expect quote
		StrUtil::skipWhitespace(p, end);
		if (p >= end)
		{
			_currentPos = nullptr;
			return;
		}

		char quote = *p;
		if (quote != '"' && quote != '\'')
		{
			_currentPos = nullptr;
			return;
		}
		++p; // move into value

		// value
		_valueStart = p;
		const char* valueEnd = StrUtil::findNext(p, end, quote);
		if (valueEnd == end)
		{
			_currentPos = nullptr;
			return;
		}
		_valueLength = static_cast<size_t>(valueEnd - _valueStart);

		// set pointer to just after closing quote and skip trailing whitespace
		const char* next = valueEnd + 1;
		StrUtil::skipWhitespace(next, end);

		// if we reached tag end or string end, mark no next attribute
		if (next >= end || *next == '>' || *next == '/')
		{
			_currentPos = nullptr;
		}
		else
		{
			_currentPos = next;
		}
	}

	std::string_view XMLAttribute::getName() const
	{
		if (!isValid() || _nameStart == nullptr || _nameLength == INVALID_INDEX(size_t))
			return std::string_view();
		return std::string_view(_nameStart, _nameLength);
	}

	std::string_view XMLAttribute::getValue() const
	{
		if (!isValid() || _valueStart == nullptr || _valueLength == INVALID_INDEX(size_t))
			return std::string_view();
		return std::string_view(_valueStart, _valueLength);
	}

	XMLAttribute XMLAttribute::getNextAttribute() const
	{
		if (!isValid() || _currentPos == nullptr)
			return XMLAttribute(nullptr);
		return XMLAttribute(_currentPos);
	}
}