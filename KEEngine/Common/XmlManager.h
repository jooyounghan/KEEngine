#pragma once
#include "Vector.h"
#include "FlyweightString.h"
#include "StringView.h"
#include "StringCommon.h"
#include "File.h"

namespace ke
{
    namespace KEXMLParser
    {
        struct Attribute 
        {
            StringViewA _name;
            StringViewA _value;
        };

        struct StartElementEvent 
        {
            StringViewA         _name;
            const Attribute*    _attributes;
            std::size_t         _attributeCount;
        };

        struct EndElementEvent 
        {
            StringViewA _name;
        };

        struct TextEvent 
        {
            StringViewA _text;
        };

        class XMLReader
        {
        public:
            class XMLReadHandler
            {
            public:
                virtual ~XMLReadHandler() = default;

            public:
                virtual void onStartElement(const StartElementEvent& e) = 0;
                virtual void onEndElement(const EndElementEvent& e) = 0;
                virtual void onText(const TextEvent& e) = 0;
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
            
        };
    };
}