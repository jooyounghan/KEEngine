#include "CommonLibPch.h"
#include "XmlAttribute.h"
#include "StrUtil.h"

#include <cstring>
#include <string_view>

namespace ke
{
	XmlAttribute::XmlAttribute(const char* pos, const char* end) { parse(pos, end); }
	
    std::string_view XmlAttribute::getName() const 
    { 
        return isValid() ? std::string_view(_nameStartPos, _nameLen) : std::string_view(); 
    }
	
    std::string_view XmlAttribute::getValue() const 
    { 
        return isValid() ? std::string_view(_valueStart, _valueLen) : std::string_view(); 
    }

    XmlAttribute XmlAttribute::getNextAttribute() const
    {
        if (!isValid() || _nextPos == nullptr) return XmlAttribute();
        return XmlAttribute(_nextPos, _end);
    }

    void XmlAttribute::parse(const char* pos, const char* end)
    {
        CT_FUNCTION_CAT("XmlAttribute");
        _pos = nullptr;
        _end = end;
        _nextPos = nullptr;
        _nameStartPos = _valueStart = nullptr;
        _nameLen = _valueLen = 0;

        if (!pos || !end || pos >= end) return;

        const char* p = pos;

        StrUtil::skipWhitespace(p, end);
        if (p >= end || !StrUtil::isNameChar(*p)) return;

        _nameStartPos = p;
        const char* nameEnd = StrUtil::findNameEnd(p, end);
        if (nameEnd <= _nameStartPos) return;
        _nameLen = static_cast<uint8>(nameEnd - _nameStartPos);
        p = nameEnd;

        StrUtil::skipWhitespace(p, end);
        if (p >= end || *p != '=') return;
        ++p;

        StrUtil::skipWhitespace(p, end);
        if (p >= end) return;

        const char quote = *p;
        if (quote != '"' && quote != '\'') return;
        ++p;

        _valueStart = p;
        const char* valueEnd = StrUtil::findNext(p, end, quote);
        if (valueEnd >= end) return;
        _valueLen = static_cast<uint8>(valueEnd - _valueStart);

        const char* next = valueEnd + 1;
        StrUtil::skipWhitespace(next, end);

        _pos = pos;

        if (next >= end || *next == '>' || *next == '/')
            _nextPos = nullptr;
        else
            _nextPos = next;
    }
}