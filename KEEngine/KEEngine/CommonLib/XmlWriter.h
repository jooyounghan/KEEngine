#pragma once
#include "File.h"
#include "DynamicBuffer.h"

namespace ke
{
    class XmlWriter;

    class XmlBuilder
    {
    public:
        XmlBuilder(const char* name, size_t len, XmlWriter* writer, bool addDepth);
        ~XmlBuilder();

    public:
        void addAttribute(const char* name, size_t nLen, const char* value, size_t vLen);
        void openHeaderEnd();
        void closeTag();

    private:
        const char* _name;
        size_t      _nameLen;
        XmlWriter*  _writer;

    private:
        uint32      _depthCached = 0;
        bool        _headerClosed = false;
        bool        _tagClosed = false;
    };

    class XmlWriter
    {
    public:
        XmlWriter(const char* path);
        ~XmlWriter();

    public:
        void writeBuffer(const char* data, size_t count);
        void flushBuffer();

    public:
        void writeIndent(int level);
        void writeToFile();

    public:
        inline uint32 increaseDepth() { return ++_depth; }
        inline uint32 decreaseDepth() { return --_depth; }
        inline uint32 getDepth() const { return _depth; }

    private:
        WriteOnlyFile   _file;
        DynamicBuffer   _buffer;

    private:
        uint32          _depth = 0;
    };
}