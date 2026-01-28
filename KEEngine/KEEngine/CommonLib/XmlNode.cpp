#include "CommonLibPch.h"
#include "XmlNode.h"
#include "StrUtil.h"

namespace ke
{
    XmlNode::XmlNode(const char* nameStart, size_t nameLen, const char* attrStart, const char* attrEnd, XmlNode* parent)
        : _nameStartPos(nameStart), _nameLen(nameLen), _attrStartPos(attrStart), _attrEndPos(attrEnd), _parent(parent)
    {
    }

    std::string_view XmlNode::getName() const
    {
        return (_nameStartPos && _nameLen) ? std::string_view(_nameStartPos, _nameLen) : std::string_view();
    }

    XmlAttribute XmlNode::getFirstAttribute() const
    {
        return (_attrStartPos && _attrEndPos) ? XmlAttribute(_attrStartPos, _attrEndPos) : XmlAttribute();
    }

    XmlNode& XmlIndexer::build(const char* begin, const char* end)
    {
        resetRoot();
        if (!begin || !end || begin >= end) return _root;

        parseOnePass(begin, end);
        return _root;
    }

    void XmlIndexer::resetRoot()
    {
        _root = XmlNode();
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
            else if (c == qc) inQuote = false;
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

    void XmlIndexer::parseOnePass(const char* begin, const char* end)
    {
        std::vector<XmlNode*> stack;
        stack.reserve(128);
        stack.push_back(&_root);

        const char* p = begin;
        while (p < end)
        {
            const char* lt = StrUtil::findNext(p, end, '<');
            if (!lt || lt >= end) break;

            if (lt + 1 < end && (lt[1] == '!' || lt[1] == '?'))
            {
                if (lt + 3 < end && lt[1] == '!' && lt[2] == '-' && lt[3] == '-')
                {
                    const char* close = StrUtil::findSequence(lt + 4, end, "-->", 3);
                    p = close ? close + 3 : end;
                }
                else
                {
                    const char* close = (lt[1] == '?') ? StrUtil::findSequence(lt + 2, end, "?>", 2) : StrUtil::findNext(lt + 2, end, '>');
                    p = close ? close + (lt[1] == '?' ? 2 : 1) : end;
                }
                continue;
            }

            if (lt + 1 < end && lt[1] == '/')
            {
                if (stack.size() > 1) stack.pop_back();
                const char* closeGt = StrUtil::findNext(lt + 2, end, '>');
                p = closeGt ? closeGt + 1 : end;
                continue;
            }

            if (lt + 1 < end && StrUtil::isNameCharStart(lt[1]))
            {
                const char* nStart = lt + 1;
                const char* nEnd = StrUtil::findNameEnd(nStart, end);
                const char* gt = findTagHeaderEnd(nEnd, end);
                if (!gt || gt >= end) { p = end; break; }

                XmlNode* parent = stack.back();
                parent->_children.emplace_back(nStart, (size_t)(nEnd - nStart), nEnd, gt, parent);

                if (!isSelfClosingTag(nEnd, gt))
                {
                    stack.push_back(&parent->_children.back());
                }
                p = gt + 1;
                continue;
            }
            p = lt + 1;
        }
    }
}

