#pragma once
#include "Vector.h"
#include "FlyweightString.h"
#include "StringView.h"
#include "StringCommon.h"

namespace ke
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
        StringViewA text;
    };

    class Handler 
    {
    public:
        virtual ~Handler() = default;

    public:
        virtual void onStartElement(const StartElementEvent& e) = 0;
        virtual void onEndElement(const EndElementEvent& e) = 0;
    };

    class XMLParser {
    public:
        explicit XMLParser(Handler& h);

    public:
        void parse(const char* data, std::size_t size);
        
    private:
        void parseElement(const char*& p, const char* end);

    private:
        Handler& _handler;
		Vector<Attribute> _attributes;
    };
}