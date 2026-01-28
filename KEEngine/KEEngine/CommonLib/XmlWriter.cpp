#include "CommonLibPch.h"
#include "XmlWriter.h"

namespace ke
{
	constexpr size_t kXmlIndentSize = 2;
	constexpr size_t kSpaceBlockSize = 1024;
	constexpr size_t kWriteBufferSize = 4096;


	const char* getSpaceBlock()
	{
		static const std::array<char, kSpaceBlockSize> block = [] {
			std::array<char, kSpaceBlockSize> b{};
			b.fill(' ');
			return b;
		}();
		return block.data();
	}

    XmlBuilder::XmlBuilder(const char* name, size_t len, XmlWriter* writer, int depth)
        : _name(name), _nameLen(len), _writer(writer), _depth(depth)
    {
        _writer->writeIndent(_depth);
        _writer->writeBuffer("<", 1);
        _writer->writeBuffer(_name, _nameLen);
    }

    XmlBuilder::~XmlBuilder()
    {
        closeTag();
    }

    void XmlBuilder::addAttribute(const char* name, size_t nLen, const char* value, size_t vLen)
    {
        _writer->writeBuffer(" ", 1);
        _writer->writeBuffer(name, nLen);
        _writer->writeBuffer("=\"", 2);
        _writer->writeBuffer(value, vLen);
        _writer->writeBuffer("\"", 1);
    }

    void XmlBuilder::openHeaderEnd()
    {
        if (!_headerClosed)
        {
            _writer->writeBuffer(">\n", 2);
            _headerClosed = true;
        }
    }

    void XmlBuilder::closeTag()
    {
        if (_tagClosed) return;

        if (!_headerClosed)
        {
            _writer->writeBuffer(" />\n", 4);
        }
        else
        {
            _writer->writeIndent(_depth);
            _writer->writeBuffer("</", 2);
            _writer->writeBuffer(_name, _nameLen);
            _writer->writeBuffer(">\n", 2);
        }
        _tagClosed = true;
    }

    XmlWriter::XmlWriter(const char* rootName, const char* path)
        : _file(path)
    {
        _buffer.set(kWriteBufferSize);
        _rootBuilder = new XmlBuilder(rootName, std::strlen(rootName), this, 0);
    }

    XmlWriter::~XmlWriter()
    {
        if (_rootBuilder)
        {
            delete _rootBuilder;
            _rootBuilder = nullptr;
        }
    }

    void XmlWriter::writeBuffer(const char* data, size_t count)
    {
        if (_buffer.getCursorPos() + count > kWriteBufferSize)
        {
            flushBuffer();
            if (count > kWriteBufferSize)
            {
                _file.writer().write(data, count);
                return;
            }
        }
        _buffer.write(data, count);
    }

    void XmlWriter::flushBuffer()
    {
        size_t pos = _buffer.getCursorPos();
        if (pos > 0)
        {
            _file.writer().write(_buffer.getConstBuffer(), pos);
            _buffer.reset();
        }
    }

    void XmlWriter::writeIndent(int level)
    {
        writeBuffer(getSpaceBlock(), level * kXmlIndentSize);
    }

    void XmlWriter::writeToFile()
    {
        if (_rootBuilder)
        {
            _rootBuilder->closeTag();
        }
        flushBuffer();
    }
}
