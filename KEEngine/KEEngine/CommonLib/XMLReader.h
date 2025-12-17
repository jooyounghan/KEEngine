#pragma once
#include "IBuffer.h"

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
        XMLReader(
            IBuffer* xmlBuffer, 
            size_t bufferSize, 
            XMLReadHandler& h
        );
        NONCOPYABLE(XMLReader);

    public:
        void parse();

    private:
        void parseElement(const char*& p, const char* end);
        void parseText(const char*& p, const char* end);

    private:
		void handleStartTag(const char*& p, const char* end);
		void handleEndTag(const char*& p, const char* end);

    private:
        XMLReadHandler& _handler;
		IBuffer*        _targetBuffer;
		size_t          _bufferSize;
		bool            _isParsing = false;
    };
}

