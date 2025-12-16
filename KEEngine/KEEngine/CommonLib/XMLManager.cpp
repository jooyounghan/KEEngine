#include "CommonLibPch.h"
#include "XMLManager.h"
#include "FileUtil.h"

namespace ke
{
    XMLReader::XMLReader(const char* path, XMLReadHandler& h)
        : _handler(h)
        , _file(path)
    {
        // read entire file
        uint64 fileSize = _file.core().getSize();
        _readBuffer.set(static_cast<std::size_t>(fileSize) + 1);
        _file.reader().read(&_readBuffer, static_cast<std::size_t>(fileSize));
    }

    void XMLReader::parse(const char* data, std::size_t size)
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
                parseText(p, end);
            }
        }
    }

    inline static void handleEndTag(const char*& p, const char* end, XMLReader::XMLReadHandler& handler)
    {
        ++p;  // skip '/'

        const char* nameStart = p;
        p = FileUtil::findNext(p, end, '>');
        const char* nameEnd = p;
        std::string_view name = std::string_view(nameStart, nameEnd);
        KE_ASSERT(nameStart != nameEnd, "XML Parsing Error: Expected element name in end tag.");
        KE_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing end tag.");
        KE_ASSERT(*nameEnd == '>', "XML Parsing Error: Expected '>' at the end of end tag.");
        ++p; // skip '>'

        handler.onReadElementFinished(XMLReader::OnReadElementEndArgs{ name });
        return;
    }

    inline static void handleStartTag(const char*& p, const char* end, XMLReader::XMLReadHandler& handler)
    {
        // start tag
        const char* elementNameStart = p;
        p = FileUtil::findNameEnd(p, end);
        const char* elementNameEnd = p;
        std::string_view elementName = std::string_view(elementNameStart, elementNameEnd);
        KE_ASSERT(elementNameStart != elementNameEnd, "XML Parsing Error: Expected element name in start tag.");
        KE_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing start tag.");

        std::vector<XmlAttribute> attributes;
        attributes.clear();

        FileUtil::skipWhitespace(p, end);
        while (p < end && *p != '>' && *p != '/')
        {
            const char* attrNameStart = p;
            p = FileUtil::findNameEnd(p, end);
            const char* attrNameEnd = p;
            KE_DEBUG_ASSERT(attrNameStart != attrNameEnd, "XML Parsing Error: Expected attribute name.");
            KE_DEBUG_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute value.");

            FileUtil::skipWhitespace(p, end);

            KE_DEBUG_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute.");
            KE_DEBUG_ASSERT(*p == '=', "XML Parsing Error : Expected '=' after attribute name.");
            ++p;

            FileUtil::skipWhitespace(p, end);
            KE_DEBUG_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute value.");

            char quote = *p;
            KE_DEBUG_ASSERT(quote == '\"' || quote == '\'', "XML Parsing Error: Expected '\"' or '\\'' at the beginning of attribute value.");
            ++p; // skip opening " or '

            const char* valueStart = p;
            p = FileUtil::findNext(p, end, quote);
            const char* valueEnd = p;
            KE_DEBUG_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing attribute value.");
            KE_DEBUG_ASSERT(valueStart != valueEnd, "XML Parsing Error: Expected attribute value.");
            KE_DEBUG_ASSERT(*p == quote, "XML Parsing Error: Expected closing quote for attribute value.");

            ++p; // skip closing " or '

            XmlAttribute atrribute;
            atrribute._name = std::string_view(attrNameStart, attrNameEnd);
            atrribute._value = std::string_view(valueStart, valueEnd);

            attributes.push_back(atrribute);
            FileUtil::skipWhitespace(p, end);
        }

        bool selfClosing = false;
        // check self closing
        if (p < end && *p == '/')
        {
            // expect "/>"
            selfClosing = true;
            ++p; // skip '/'

            KE_ASSERT(p < end, "XML Parsing Error: Unexpected end of input after '/' in start tag.");
            KE_ASSERT(*p == '>', "XML Parsing Error: Expected '>' at the end of self-closing tag.");
            ++p; // skip '>'
        }
        else
        {
            // expect '>'

            KE_ASSERT(p < end, "XML Parsing Error: Unexpected end of input while parsing start tag.");
            KE_ASSERT(*p == '>', "XML Parsing Error: Expected '>' at the end of start tag.");
            ++p; // skip '>'
        }

        // issue start tag event
        handler.onReadElementStarted(XMLReader::OnReadElementStartedArgs{
            elementName,
            attributes.data(),
            attributes.size()
            });

        // issue end tag event when self-closing
        if (selfClosing)
        {
            handler.onReadElementFinished(XMLReader::OnReadElementEndArgs{ elementName });
        }
    }

    void XMLReader::parseElement(const char*& p, const char* end)
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

        handleStartTag(p, end, _handler);
    }

    void XMLReader::parseText(const char*& p, const char* end)
    {
        const char* textStart = p;
        p = FileUtil::findNext(p, end, '<');
        const char* textEnd = p;

        if (textEnd > textStart)
        {
            _handler.onReadText(OnReadTextArgs{ std::string_view(textStart, textEnd) });
        }
    }
}