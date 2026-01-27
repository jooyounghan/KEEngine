#pragma once
#include "XmlAttribute.h"

namespace ke
{
    class XmlNode
    {
    public:
        XmlNode() = default;

    public:
		inline bool isRoot() const { return _parent == nullptr; }
        inline bool isValid() const { return (_nameStartPos != nullptr) || !_children.empty(); }
        std::string_view getName() const;
        XmlAttribute getFirstAttribute() const;


    public:
        inline const XmlNode* getParent() const { return _parent; }
        inline const std::vector<XmlNode>& getChildNodes() const { return _children; }
        const std::vector<XmlNode>& getSiblingNodes() const;


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

    public:
        XmlNode& getRoot() { return _root; }
        const XmlNode& getRoot() const { return _root; }

    private:
        struct FlatNode
        {
            const char* nameStart = nullptr;
            uint32      nameLen = 0;
            const char* attrStart = nullptr;
            const char* attrEnd = nullptr;
        };

    private:
        static const char* findTagHeaderEnd(const char* p, const char* end);
        static bool isSelfClosingTag(const char* afterName, const char* gt);

    private:
        void resetRoot();
        int32 addNode(
            const char* nameStart, 
            uint32 nameLen,
            const char* attrStart, 
            const char* attrEnd,
            int32 parentIdx
        );
        void scanOnce(const char* begin, const char* end);
        void buildInto(XmlNode& parent, int32 idx);

    private:
        const char* _begin = nullptr;
        const char* _end = nullptr;

        std::vector<FlatNode> _nodes;
        std::vector<std::vector<int32>> _children;
        std::vector<int32> _topLevel;

        XmlNode _root;
    };
}