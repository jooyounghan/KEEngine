#pragma once
namespace ke
{
    class XmlAttribute
    {
    public:
        XmlAttribute() = default;
        XmlAttribute(const char* pos, const char* end);

    public:
        inline bool isValid() const { return _pos != nullptr; }

        std::string_view getName()  const;
        std::string_view getValue() const;

        XmlAttribute getNextAttribute() const;

    private:
        void parse(const char* pos, const char* end);

    private:
        const char* _pos = nullptr;
        const char* _end = nullptr;

        const char* _nextPos = nullptr;

        const char* _nameStartPos = nullptr;
        uint8 _nameLen = 0;

        const char* _valueStart = nullptr;
        uint8 _valueLen = 0;
    };
}