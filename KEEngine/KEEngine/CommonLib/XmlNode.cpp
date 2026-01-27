#include "CommonLibPch.h"
#include "XmlNode.h"
#include "StrUtil.h"

namespace ke
{
    std::string_view XmlNode::getName() const
    {
        return (_nameStartPos && _nameLen) ? std::string_view(_nameStartPos, _nameLen) : std::string_view();
    }
    
    XmlAttribute XmlNode::getFirstAttribute() const
    {
        return (_attrStartPos && _attrEndPos) ? XmlAttribute(_attrStartPos, _attrEndPos) : XmlAttribute();
    }
    
    const std::vector<XmlNode>& XmlNode::getSiblingNodes() const
    {
        if (_parent) return _parent->_children;
        else return this->getChildNodes();
    }
    
    XmlNode& XmlIndexer::build(const char* begin, const char* end)
    {
        _begin = begin;
        _end = end;

        _nodes.clear();
        _children.clear();
        _topLevel.clear();

        resetRoot();

        if (!begin || !end || begin >= end)
            return _root;

        scanOnce(begin, end);

        _root._children.reserve(_topLevel.size());
        for (int32 idx : _topLevel)
            buildInto(_root, idx);

        return _root;
    }

    void XmlIndexer::resetRoot()
    {
        _root = XmlNode();
        _root._nameStartPos = nullptr;
        _root._nameLen = 0;
        _root._attrStartPos = nullptr;
        _root._attrEndPos = nullptr;
        _root._parent = nullptr;
        _root._children.clear();
    }

    const char* XmlIndexer::findTagHeaderEnd(const char* p, const char* end)
    {
        bool inQuote = false;
        char qc = 0;

        while (p < end)
        {
            char c = *p;
            if (!inQuote)
            {
                if (c == '"' || c == '\'') { inQuote = true; qc = c; }
                else if (c == '>') return p;
            }
            else
            {
                if (c == qc) { inQuote = false; qc = 0; }
            }
            ++p;
        }
        return end;
    }

    bool XmlIndexer::isSelfClosingTag(const char* afterName, const char* gt)
    {
        const char* p = gt;
        while (p > afterName && StrUtil::isWhitespace(*(p - 1))) --p;
        return (p > afterName && *(p - 1) == '/');
    }

    int32 XmlIndexer::addNode(const char* nameStart, uint32 nameLen, const char* attrStart, const char* attrEnd, int32 parentIdx)
    {
        FlatNode n;
        n.nameStart = nameStart;
        n.nameLen = nameLen;
        n.attrStart = attrStart;
        n.attrEnd = attrEnd;

        int32 idx = (int32)_nodes.size();
        _nodes.push_back(n);
        _children.emplace_back();

        if (parentIdx >= 0)
            _children[(size_t)parentIdx].push_back(idx);
        else
            _topLevel.push_back(idx);

        return idx;
    }

    void XmlIndexer::scanOnce(const char* begin, const char* end)
    {
        std::vector<int32> stack;
        stack.reserve(256);

        const char* p = begin;

        while (p && p < end)
        {
            const char* lt = StrUtil::findNext(p, end, '<');
            if (!lt || lt + 1 >= end) break;

            // <!-- ... -->
            if ((end - lt) >= 4 && lt[1] == '!' && lt[2] == '-' && lt[3] == '-')
            {
                static const char seq[] = "-->";
                const char* close = StrUtil::findSequence(lt + 4, end, seq, 3);
                if (close >= end) break;
                p = close + 3;
                continue;
            }

            // <? ... ?>
            if (lt[1] == '?')
            {
                static const char seq[] = "?>";
                const char* close = StrUtil::findSequence(lt + 2, end, seq, 2);
                if (close >= end) break;
                p = close + 2;
                continue;
            }

            // <!DOCTYPE ...>
            if (lt[1] == '!')
            {
                const char* gt = StrUtil::findNext(lt + 2, end, '>');
                if (gt >= end) break;
                p = gt + 1;
                continue;
            }

            // close tag </name>
            if (lt[1] == '/')
            {
                const char* n0 = lt + 2;
                if (n0 < end && StrUtil::isNameCharStart(*n0))
                {
                    const char* nEnd = StrUtil::findNameEnd(n0, end);
                    uint32 len = (uint32)(nEnd - n0);

                    const char* closeGt = StrUtil::findNext(lt, end, '>');
                    if (closeGt >= end) break;

                    for (int i = (int)stack.size() - 1; i >= 0; --i)
                    {
                        int32 openIdx = stack[(size_t)i];
                        const FlatNode& openN = _nodes[(size_t)openIdx];

                        if (openN.nameLen == len &&
                            std::memcmp(openN.nameStart, n0, len) == 0)
                        {
                            stack.resize((size_t)i);
                            break;
                        }
                    }

                    p = closeGt + 1;
                    continue;
                }

                p = lt + 2;
                continue;
            }

            // open tag <name ...>
            if (StrUtil::isNameCharStart(lt[1]))
            {
                const char* nameStart = lt + 1;
                const char* nameEnd = StrUtil::findNameEnd(nameStart, end);
                if (nameEnd <= nameStart) { p = lt + 1; continue; }

                uint32 nameLen = (uint32)(nameEnd - nameStart);

                const char* gt = findTagHeaderEnd(nameEnd, end);
                if (gt >= end) break;

                const char* attrStart = nameEnd;
                const char* attrEnd = gt;

                bool selfClosing = isSelfClosingTag(nameEnd, gt);

                int32 parentIdx = stack.empty() ? -1 : stack.back();
                int32 idx = addNode(nameStart, nameLen, attrStart, attrEnd, parentIdx);

                if (!selfClosing)
                    stack.push_back(idx);

                p = gt + 1;
                continue;
            }

            p = lt + 1;
        }
    }

    void XmlIndexer::buildInto(XmlNode& parent, int32 idx)
    {
        const FlatNode& fn = _nodes[(size_t)idx];

        parent._children.emplace_back();
        XmlNode& me = parent._children.back();

        me._nameStartPos = fn.nameStart;
        me._nameLen = (size_t)fn.nameLen;
        me._attrStartPos = fn.attrStart;
        me._attrEndPos = fn.attrEnd;
        me._parent = &parent;

        const auto& kids = _children[(size_t)idx];
        me._children.clear();
        me._children.reserve(kids.size());

        for (int32 c : kids)
            buildInto(me, c);
    }

}

