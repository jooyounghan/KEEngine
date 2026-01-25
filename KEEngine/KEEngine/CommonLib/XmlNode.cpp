#include "CommonLibPch.h"
#include "XmlNode.h"
#include "StrUtil.h"

namespace ke
{
    XmlNode::XmlNode(const char* pos, const char* end, const char* siblingEnd) { parse(pos, end, siblingEnd); }

    std::string_view XmlNode::getName() const
    {
        return isValid() ? std::string_view(_nameStartPos, _nameLen) : std::string_view();
    }

    XmlAttribute XmlNode::getFirstAttribute() const
    {
        return (isValid() && _attrStartPos != nullptr) ? XmlAttribute(_attrStartPos, _attrEndPos) : XmlAttribute();
    }

    XmlNode XmlNode::getFirstChild() const
    {
        if (!isValid() || _selfClosing) return XmlNode();

        const char* childLt = findNextElementStart(_contentStart, _contentEnd);
        if (!childLt) return XmlNode();

        return XmlNode(childLt, _xmlEndPos, _contentEnd);
    }

    XmlNode XmlNode::getNextSibling() const
    {
        if (!isValid() || !_nodeEnd) return XmlNode();
        if (!_siblingEnd || _nodeEnd >= _siblingEnd) return XmlNode();

        const char* sibLt = findNextElementStart(_nodeEnd, _siblingEnd);
        if (!sibLt) return XmlNode();

        return XmlNode(sibLt, _xmlEndPos, _siblingEnd);
    }

    const char* XmlNode::findNextElementStart(const char* p, const char* end)
    {
        while (p && p < end)
        {
            const char* lt = StrUtil::findNext(p, end, '<');
            if (!lt || lt >= end) return nullptr;
            if (lt + 1 >= end) return nullptr;

            // <!-- ... -->
            if ((end - lt) >= 4 && lt[1] == '!' && lt[2] == '-' && lt[3] == '-')
            {
                static const char seq[] = "-->";
                const char* close = StrUtil::findSequence(lt + 4, end, seq, 3);
                if (close >= end) return nullptr;
                p = close + 3;
                continue;
            }

            // <? ... ?>
            if (lt[1] == '?')
            {
                static const char seq[] = "?>";
                const char* close = StrUtil::findSequence(lt + 2, end, seq, 2);
                if (close >= end) return nullptr;
                p = close + 2;
                continue;
            }

            // <!DOCTYPE ...>
            if (lt[1] == '!')
            {
                const char* gt = StrUtil::findNext(lt + 2, end, '>');
                if (gt >= end) return nullptr;
                p = gt + 1;
                continue;
            }

            if (lt[1] == '/')
            {
                p = lt + 2;
                continue;
            }

            // <name ...>
            if (StrUtil::isNameCharStart(lt[1]))
                return lt;

            p = lt + 1;
        }
        return nullptr;
    }

    const char* XmlNode::findTagHeaderEnd(const char* p, const char* end)
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

    bool XmlNode::isSelfClosingTag(const char* afterName, const char* gt)
    {
        const char* p = gt;
        while (p > afterName && StrUtil::isWhitespace(*(p - 1))) --p;
        return (p > afterName && *(p - 1) == '/');
    }

    const char* XmlNode::findMatchingCloseTagLt(const char* p, const char* end, std::string_view name)
    {
        int depth = 1;

        while (p && p < end)
        {
            const char* lt = StrUtil::findNext(p, end, '<');
            if (!lt || lt >= end) return nullptr;
            if (lt + 1 >= end) return nullptr;

            if ((end - lt) >= 4 && lt[1] == '!' && lt[2] == '-' && lt[3] == '-')
            {
                static const char seq[] = "-->";
                const char* close = StrUtil::findSequence(lt + 4, end, seq, 3);
                if (close >= end) return nullptr;
                p = close + 3;
                continue;
            }
            if (lt[1] == '?')
            {
                static const char seq[] = "?>";
                const char* close = StrUtil::findSequence(lt + 2, end, seq, 2);
                if (close >= end) return nullptr;
                p = close + 2;
                continue;
            }
            if (lt[1] == '!')
            {
                const char* gt = StrUtil::findNext(lt + 2, end, '>');
                if (gt >= end) return nullptr;
                p = gt + 1;
                continue;
            }

            if (lt[1] == '/')
            {
                const char* n0 = lt + 2;
                if (n0 < end && StrUtil::isNameCharStart(*n0))
                {
                    const char* nEnd = StrUtil::findNameEnd(n0, end);
                    std::string_view closeName(n0, static_cast<size_t>(nEnd - n0));
                    if (closeName == name)
                    {
                        --depth;
                        if (depth == 0) return lt;
                    }
                }
                p = lt + 2;
                continue;
            }

            if (StrUtil::isNameCharStart(lt[1]))
            {
                const char* n0 = lt + 1;
                const char* nEnd = StrUtil::findNameEnd(n0, end);
                std::string_view openName(n0, static_cast<size_t>(nEnd - n0));

                const char* gt = findTagHeaderEnd(nEnd, end);
                if (gt >= end) return nullptr;

                bool selfClosing = isSelfClosingTag(nEnd, gt);
                if (!selfClosing && openName == name)
                    ++depth;

                p = gt + 1;
                continue;
            }

            p = lt + 1;
        }

        return nullptr;
    }

    void XmlNode::parse(const char* pos, const char* end, const char* siblingEnd)
    {
        CT_FUNCTION_CAT("XmlNode");
        reset();
        _xmlEndPos = end;
        _siblingEnd = siblingEnd ? siblingEnd : end;

        if (!pos || !end || pos >= _siblingEnd) return;

        const char* lt = nullptr;

        if (*pos == '<' && (pos + 1) < _siblingEnd && StrUtil::isNameCharStart(pos[1]))
            lt = pos;
        else
            lt = findNextElementStart(pos, _siblingEnd);

        if (!lt) return;
        if (lt + 1 >= _siblingEnd || !StrUtil::isNameCharStart(lt[1])) return;

        _nodeStartPos = lt;
        _nodeStartPos = lt;

        _nameStartPos = lt + 1;
        const char* nameEnd = StrUtil::findNameEnd(_nameStartPos, _siblingEnd);
        if (nameEnd <= _nameStartPos) { reset(); return; }
        _nameLen = static_cast<size_t>(nameEnd - _nameStartPos);

        _attrStartPos = nameEnd;

        const char* gt = findTagHeaderEnd(nameEnd, _siblingEnd);
        if (gt >= _siblingEnd) { reset(); return; }
        _attrEndPos = gt;

        _selfClosing = isSelfClosingTag(nameEnd, gt);
        if (_selfClosing)
        {
            _contentStart = gt + 1;
            _contentEnd = _contentStart;
            _nodeEnd = gt + 1;
            return;
        }

        _contentStart = gt + 1;

        std::string_view myName(_nameStartPos, _nameLen);
        const char* closeLt = findMatchingCloseTagLt(_contentStart, _siblingEnd, myName);
        if (!closeLt) { reset(); return; }

        _contentEnd = closeLt;

        const char* closeGt = StrUtil::findNext(closeLt, _siblingEnd, '>');
        if (closeGt >= _siblingEnd) { reset(); return; }

        _nodeEnd = closeGt + 1;
    }
    
    void XmlNode::reset()
    {
        _nodeStartPos = nullptr;
        _xmlEndPos = nullptr;

        _nameStartPos = nullptr;
        _nameLen = 0;

        _attrStartPos = nullptr;
        _attrEndPos = nullptr;

        _contentStart = nullptr;
        _contentEnd = nullptr;

        _siblingEnd = nullptr;
        _nodeEnd = nullptr;
        _selfClosing = false;
    }
}

