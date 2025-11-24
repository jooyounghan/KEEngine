#include "XmlManager.h"
#include "AssertManager.h"

namespace ke
{
	XMLParser::XMLParser(Handler& h) : _handler(h) {}

    void XMLParser::parse(const char* data, std::size_t size)
    {
        const char* p = data;
        const char* end = data + size;

        while (p < end)
        {
            if (*p == '<')
            {
                parseElement(p, end);
            }
            else
            {
                p = KEString::findNext(p, end, '<');
            }
        }
    }

    inline static StringViewA getStringView(const char* start, const char* end)
    {
        return StringViewA(start, static_cast<std::size_t>(end - start));
	}

    inline static void handleEndTag(const char*& p, const char* end, Handler& handler)
    {
        ++p;  // skip '/'

        const char* nameStart = p;
        p = KEString::findNext(p, end, '>');
        const char* nameEnd = p;
        StringView name = getStringView(nameStart, nameEnd);

        if (p < end) ++p; // skip '>'

        handler.onEndElement(EndElementEvent{ name });
        return;
	}

    inline static void handleStartTag(const char*& p, const char* end, Vector<Attribute>& attributes, Handler& handler)
    {
        // start tag
        const char* nameStart = p;
        p = KEString::findNameEnd(p, end);
        const char* nameEnd = p;
        StringView name = getStringView(nameStart, nameEnd);

		KEString::skipWhitespace(p, end);
        attributes.clear();        

        bool selfClosing = false;

        while (p < end && *p != '>' && *p != '/') 
        {
            // 속성 이름
            const char* attrNameStart = p;
            p = KEString::findNameEnd(p, end);
            const char* attrNameEnd = p;
            KE_DEBUG_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute value.");
            KE_DEBUG_ASSERT(attrNameStart != attrNameEnd, "XML Parsing Error: Expected attribute name.");
            
            KEString::skipWhitespace(p, end);

			KE_DEBUG_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute.");
			KE_DEBUG_ASSERT(*p == '=', "XML Parsing Error : Expected '=' after attribute name.");
            ++p;
            
            KEString::skipWhitespace(p, end);
			KE_DEBUG_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute value.");

            char quote = *p;
			KE_DEBUG_ASSERT(quote == '\"' || quote == '\'', "XML Parsing Error: Expected '\"' or '\\'' at the beginning of attribute value.");
            ++p; // skip opening " or '

            const char* valueStart = p;
            p = KEString::findNext(p, end, quote);
            const char* valueEnd = p;
            KE_DEBUG_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute value.");
			KE_DEBUG_ASSERT(valueStart != valueEnd, "XML Parsing Error: Expected attribute value.");
			KE_DEBUG_ASSERT(*p == quote, "XML Parsing Error: Expected closing quote for attribute value.");

			++p; // skip closing " or '

            Attribute a;
            a._name = getStringView(attrNameStart, attrNameEnd);
			a._value = getStringView(valueStart, valueEnd);

            // ===========================================================
            attrBuffer_.push_back(a);

            skipWhitespace(p, end);
        }

        // self-closing 체크: "/>"
        if (p < end && *p == '/') {
            selfClosing = true;
            ++p; // skip '/'
            if (p < end && *p == '>') {
                ++p; // skip '>'
            }
        }
        else {
            // '>' 기대
            if (p < end && *p == '>') {
                ++p;
            }
        }

        // 시작 태그 이벤트
        handler_.onStartElement(StartElementEvent{
            elementName,
            attrBuffer_.data(),
            attrBuffer_.size()
            });

        // self-closing 이면 바로 종료 태그 이벤트도 발행
        if (selfClosing) {
            handler_.onEndElement(EndElementEvent{ elementName });
        }
    }

    void XMLParser::parseElement(const char*& p, const char* end)
    {
        // skip '<'
        ++p; 
        if (p >= end) return;

        // end tag
        if (*p == '/') 
        {
			handleEndTag(p, end, _handler);
			return;
        }

		handleStartTag(p, end, _attributes, _handler);
    }

}
