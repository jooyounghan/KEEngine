#pragma once
#include "XmlAttribute.h"

namespace ke
{
    class XmlNode
    {
    public:
        XmlNode() = default;
        XmlNode(const char* pos, const char* end, const char* siblingEnd);

    public:
        inline bool isValid() const { return _nodeStartPos != nullptr; }
		inline bool isSelfClosing() const { return _selfClosing; }

    public:
        std::string_view getName() const;
        XmlAttribute getFirstAttribute() const;
        XmlNode getFirstChild() const;
        XmlNode getNextSibling() const;

    private:
        static const char* findNextElementStart(const char* p, const char* end);
        static const char* findTagHeaderEnd(const char* p, const char* end);
        static bool isSelfClosingTag(const char* afterName, const char* gt);
        static const char* findMatchingCloseTagLt(const char* p, const char* end, std::string_view name);

    private:
        void parse(const char* pos, const char* end, const char* siblingEnd);
        void reset();

    private:
        const char* _nodeStartPos = nullptr;
        const char* _xmlEndPos = nullptr;

        const char* _nameStartPos = nullptr;
        size_t      _nameLen = 0;

        const char* _attrStartPos = nullptr;
        const char* _attrEndPos = nullptr;

        const char* _contentStart = nullptr;
        const char* _contentEnd = nullptr;

        const char* _siblingEnd = nullptr;
        const char* _nodeEnd = nullptr;
        bool        _selfClosing = false;
    };
}