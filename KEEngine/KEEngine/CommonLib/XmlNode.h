#pragma once
#include "XmlAttribute.h"

namespace ke
{
    class XmlNode
    {
    public:
        XmlNode() = default;
        XmlNode(const char* nameStart, size_t nameLen, const char* attrStart, const char* attrEnd, XmlNode* parent);

    public:
        inline bool isRoot() const { return _parent == nullptr; }
        inline bool isValid() const { return isRoot() || _nameStartPos != nullptr; }
        std::string_view getName() const;
        XmlAttribute getFirstAttribute() const;

    public:
        inline const XmlNode* getParent() const { return _parent; }
        inline const std::vector<XmlNode>& getChildNodes() const { return _children; }

    private:
        friend class XmlIndexer;

        const char* _nameStartPos = nullptr;
        size_t      _nameLen = 0;

        const char* _attrStartPos = nullptr;
        const char* _attrEndPos = nullptr;

        XmlNode* _parent = nullptr;
        std::vector<XmlNode> _children;
    };

    class XmlIndexer
    {
    public:
        XmlIndexer() = default;

    public:
        XmlNode& build(const char* begin, const char* end);
        inline XmlNode& getRootNode() { return _root; }

    private:
        static const char* findTagHeaderEnd(const char* p, const char* end);
        static bool isSelfClosingTag(const char* afterName, const char* gt);

    private:
        void resetRoot();
        void parseOnePass(const char* begin, const char* end);

    private:
        XmlNode _root;
    };
}