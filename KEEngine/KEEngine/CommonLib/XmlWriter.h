#pragma once
#include "File.h"
#include "DynamicBuffer.h"

namespace ke
{
    class XmlWriter;

    class XmlBuilder
    {
    public:
        XmlBuilder(const char* name, size_t len, XmlWriter* writer, int depth);
        ~XmlBuilder();

    public:
        void addAttribute(const char* name, size_t nLen, const char* value, size_t vLen);
        void openHeaderEnd();
        void closeTag();

    private:
        const char* _name;
        size_t      _nameLen;
        XmlWriter* _writer;
        int         _depth;
        bool        _headerClosed = false;
        bool        _tagClosed = false;
    };

    class XmlWriter
    {
    public:
        XmlWriter(const char* rootName, const char* path);
        ~XmlWriter();

    public:
        void writeBuffer(const char* data, size_t count);
        void flushBuffer();
        void writeIndent(int level);
        void writeToFile();

        inline XmlBuilder* getRootBuilder() { return _rootBuilder; }

    private:
        WriteOnlyFile  _file;
        DynamicBuffer  _buffer;
        XmlBuilder* _rootBuilder = nullptr;
    };
}