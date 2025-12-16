#pragma once
#include "File.h"
#include "DynamicBuffer.h"

namespace ke
{
    struct XmlAttribute
    {
        std::string_view _name;
        std::string_view _value;
    };

    class XMLReader
    {
    public:
        struct OnReadElementStartedArgs
        {
            std::string_view    _name;
            const XmlAttribute* _attributes;
            std::size_t         _attributeCount;
        };

        struct OnReadElementEndArgs
        {
            std::string_view _name;
        };

        struct OnReadTextArgs
        {
            std::string_view _text;
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
        XMLReadHandler& _handler;
        ReadOnlyFile    _file;
        DynamicBuffer   _readBuffer;
    };

    //class XMLWriter
    //{
    //public:
    //    struct OnWriteElementArgs
    //    {
    //        std::string_view    _name;
    //        const XmlAttribute* _attributes;
    //        std::size_t         _attributeCount;
    //    };

    //    class XMLWriteHandler
    //    {
    //    public:
    //        virtual ~XMLWriteHandler() = default;

    //    public:
    //        virtual void onWriteElement(const OnWriteElementArgs& e) = 0;
    //    }
    //};
}

