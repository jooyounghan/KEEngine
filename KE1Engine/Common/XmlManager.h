#pragma once
#include "FlyweightString.h"
#include "StringView.h"
#include "StringCommon.h"
#include "DynamicBuffer.h"
#include "File.h"

namespace ke
{
    struct XmlAttribute 
    {
        StringViewA _name;
        StringViewA _value;
    };

    class XMLReader
    {
    public:
        struct OnReadElementStartedArgs
        {
            StringViewA         _name;
            const XmlAttribute* _attributes;
            std::size_t         _attributeCount;
        };

        struct OnReadElementEndArgs
        {
            StringViewA _name;
        };

        struct OnReadTextArgs
        {
            StringViewA _text;
        };

        class XMLReadHandler
        {
        public:
            virtual ~XMLReadHandler() = default;

        public:
            virtual void onReadElementStarted(const OnReadElementStartedArgs& args) = 0;
            virtual void onReadElementFinished(const OnReadElementEndArgs& args) = 0;
            virtual void onReadText(const OnReadTextArgs& args) = 0;
        };

    public:
        explicit XMLReader(const char* path, XMLReadHandler& h);
        NONCOPYABLE(XMLReader);

    public:
        void parse(const char* data, std::size_t size);

    private:
        void parseElement(const char*& p, const char* end);
        void parseText(const char*& p, const char* end);

    private:
        XMLReadHandler&                                     _handler;
		File<AllowRead, BlockWrite, EOpenMode::ReadOnly>    _file;
		DynamicBuffer									    _readBuffer;
    };

    class XMLWriter
	{
    public:
        struct OnWriteElementArgs
        {
            StringViewA         _name;
            const XmlAttribute* _attributes;
            std::size_t         _attributeCount;
        };

        class XMLWriteHandler
        {
        public:
            virtual ~XMLWriteHandler() = default;

        public:
            virtual void onWriteElement(const OnWriteElementArgs& e) = 0;
        }
    };
}