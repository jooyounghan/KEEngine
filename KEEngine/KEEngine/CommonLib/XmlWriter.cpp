#include "CommonLibPch.h"
#include "XmlWriter.h"

namespace ke
{
	constexpr size_t kXmlIndentSize = 2;
	constexpr uint32 kXmlNodeBufferSize = 1024;
	constexpr size_t kSpaceBlockSize = 4096;

	XmlBuilder::XmlBuilder(const char* name)
		: _name(name)
	{
		_buffer.release();
		_buffer.set(kXmlNodeBufferSize);

		_buffer.writeOne('<');
		_buffer.write(_name.c_str(), _name.length());
	}


	void XmlBuilder::addAttribute(const char* name, const char* value)
	{
		_buffer.writeOne(' ');
		_buffer.write(name, std::strlen(name));
		_buffer.writeOne('=');
		_buffer.writeOne('"');
		_buffer.write(value, std::strlen(value));
		_buffer.writeOne('"');
	}

	XmlBuilder* XmlBuilder::addChild(const char* name)
	{
		_children.push_back(MAKE_PTR(XmlBuilder, name));
		return _children.back().get();
	}

	XmlWriter::XmlWriter(const char* rootName, const char* path)
		: _file(path), _rootBuilder(rootName)
	{
		const FileCore& fileCore = _file.core();
		if (fileCore.getOpenStatus() != 0) return;
	}

	const char* getSpaceBlock()
	{
		static const std::array<char, kSpaceBlockSize> block = [] {
			std::array<char, kSpaceBlockSize> b{};
			b.fill(' ');
			return b;
		}();
		return block.data();
	}

#define WRITE_INDENT(level) _file.writer().write(getSpaceBlock(), level * kXmlIndentSize);
	void XmlWriter::writeNode(XmlBuilder* node, int indentLevel)
	{
		WRITE_INDENT(indentLevel);
		_file.writer().write(&node->_buffer, node->_buffer.getCursorPos());
		const bool isSelfClosing = node->isSelfClosing();
		const char* endTag = isSelfClosing ? "/>\n" : ">\n";
		const size_t endTagLen = isSelfClosing ? 3 : 2;
		_file.writer().write(endTag, endTagLen);

		for (const PTR(XmlBuilder)& child : node->_children)
		{
			writeNode(child.get(), indentLevel + 1);
		}

		if (isSelfClosing == false)
		{
			WRITE_INDENT(indentLevel);
			_file.writer().write("</", 2);
			_file.writer().write(node->_name.c_str(), node->_name.length());
			_file.writer().write(">\n", 2);
		}
	}
#undef WRITE_INDENT

	void XmlWriter::writeToFile()
	{
		writeNode(&_rootBuilder, 0);
	}
}
