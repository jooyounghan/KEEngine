#include "CommonLibPch.h"
#include "XMLReader.h"
#include "StrUtil.h"

namespace ke
{
    XMLReader::XMLReader(IBuffer* xmlBuffer, size_t bufferSize, XMLReadHandler& h)
		: _handler(h), _targetBuffer(xmlBuffer), _bufferSize(bufferSize)
    {
    }

    void XMLReader::parse()
    {
        const char* p = _targetBuffer->getConstBuffer();
        const char* end = p + _bufferSize;

        while (p < end)
        {
            if (*p == '<')
            {
                parseElement(p, end);
            }
            else
            {
                parseText(p, end);
            }
        }
    }

    void XMLReader::handleEndTag(const char*& p, const char* end)
    {
        ++p;  // skip '/'

        const char* nameStart = p;
        p = StrUtil::findNext(p, end, '>');
        const char* nameEnd = p;

        KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing end tag.");
        std::string_view name = std::string_view(nameStart, nameEnd);

        KE_DEBUG_RETURN(nameStart != nameEnd, "XML Parsing Error: Expected element name in end tag.");
        KE_DEBUG_RETURN(*nameEnd == '>', "XML Parsing Error: Expected '>' at the end of end tag.");
        ++p; // skip '>'

        _isParsing = false;
        _handler.onReadElementFinished(XMLReader::OnReadElementEndArgs{ name });
        return;
    }

    void XMLReader::handleStartTag(const char*& p, const char* end)
    {
        // special handling: comments <!-- ... -->, processing instructions <? ... ?>, declarations <! ... >
        if (p < end && (*p == '!' || *p == '?'))
        {
            if (*p == '!' && p + 2 < end && p[1] == '-' && p[2] == '-')
            {
                // comment: skip until "-->"
                p = StrUtil::findSequence(p, end, "-->", 3);
                KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing comment.");
				p += 3; // skip "-->"

                _isParsing = false;
                return;
            }
            else
            {
                // declaration or processing instruction: skip until matching terminator
                if (*p == '?')
                {
                    // processing instruction: skip until "?>"
                    p = StrUtil::findSequence(p, end, "?>", 2);
                    KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing processing instruction.");
					p += 2; // skip "?>"

                    _isParsing = false;
                    return;
                }
                else
                {
                    p = StrUtil::findNext(p, end, '>');
                    KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing declaration.");
                    ++p; // skip '>'
                    
                    _isParsing = false;
                    return;
                }
            }
        }

        // start tag
        const char* elementNameStart = p;
        p = StrUtil::findNameEnd(p, end);
        const char* elementNameEnd = p;
        std::string_view elementName = std::string_view(elementNameStart, elementNameEnd);

        KE_DEBUG_RETURN(elementNameStart != elementNameEnd, "XML Parsing Error: Expected element name in start tag.");
        KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing start tag.");

        std::vector<XmlAttribute> attributes;
        attributes.clear();

        StrUtil::skipWhitespace(p, end);
        while (p < end && *p != '>' && *p != '/')
        {
            const char* attrNameStart = p;
            p = StrUtil::findNameEnd(p, end);
            const char* attrNameEnd = p;
            KE_DEBUG_RETURN(attrNameStart != attrNameEnd, "XML Parsing Error: Expected attribute name.");
            KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute value.");

            StrUtil::skipWhitespace(p, end);

            KE_DEBUG_RETURN(*p == '=', "XML Parsing Error : Expected '=' after attribute name.");
            KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute.");
            ++p;

            StrUtil::skipWhitespace(p, end);
            KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute value.");

            char quote = *p;
            KE_DEBUG_RETURN(quote == '\"' || quote == '\'', "XML Parsing Error: Expected '\"' or '\\'' at the beginning of attribute value.");
            ++p; // skip opening " or '

            const char* valueStart = p;
            p = StrUtil::findNext(p, end, quote);
            const char* valueEnd = p;
            KE_DEBUG_RETURN(valueStart != valueEnd, "XML Parsing Error: Expected attribute value.");
            KE_DEBUG_RETURN(*p == quote, "XML Parsing Error: Expected closing quote for attribute value.");
            KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute value.");
            ++p; // skip closing " or '

            XmlAttribute atrribute;
            atrribute._name = std::string_view(attrNameStart, attrNameEnd);
            atrribute._value = std::string_view(valueStart, valueEnd);

            attributes.push_back(atrribute);
            StrUtil::skipWhitespace(p, end);
        }

        bool selfClosing = false;
        // check self closing
        if (p < end && *p == '/')
        {
            // expect "/>"
            selfClosing = true;
            ++p; // skip '/'
        }
        // expect '>'
        KE_DEBUG_RETURN(*p == '>', "XML Parsing Error: Expected '>' at the end of start tag.");
        KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input while parsing start tag.");
        ++p; // skip '>'

        // issue start tag event
        _handler.onReadElementStarted(XMLReader::OnReadElementStartedArgs{
            elementName,
            attributes.data(),
            attributes.size()
            });

        // issue end tag event when self-closing
        if (selfClosing)
        {
            _isParsing = false;
            _handler.onReadElementFinished(XMLReader::OnReadElementEndArgs{ elementName });
        }
    }

    void XMLReader::parseElement(const char*& p, const char* end)
    {
        // skip '<'
        ++p;
        KE_DEBUG_RETURN(p < end, "XML Parsing Error: Unexpected end of input after '<'.");

        // end tag
        if (*p == '/')
        {
            handleEndTag(p, end);
            return;
        }

        _isParsing = true;
        handleStartTag(p, end);
    }

    void XMLReader::parseText(const char*& p, const char* end)
    {
        const char* textStart = p;
        p = StrUtil::findNext(p, end, '<');
        const char* textEnd = p;

		KE_DEBUG_RETURN(_isParsing != true, "XML Parsing Error: Text found outside of start element.");
        if (textEnd <= textStart)
            return;

        _handler.onReadText(OnReadTextArgs{ std::string_view(textStart, textEnd) });
    }
}