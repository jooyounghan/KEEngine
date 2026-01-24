#pragma once
#include "File.h"
#include "DynamicBuffer.h"

namespace ke
{
	class XmlBuilder
	{
		friend class XmlWriter;

	public:
		XmlBuilder(const char* name);
		~XmlBuilder() = default;

	private:
		std::string		_name;
		DynamicBuffer	_buffer;

	private:
		std::vector<PTR(XmlBuilder)> _children;

	public:
		inline bool isSelfClosing() const { return _children.empty(); }

	public:
		void		addAttribute(const char* name, const char* value);
		XmlBuilder* addChild(const char* name);
	};

	class XmlWriter
	{
	public:
		XmlWriter(const char* rootName, const char* path );

	private:
		WriteOnlyFile	_file;
		XmlBuilder _rootBuilder;

	public:
		inline XmlBuilder& getRootBuilder() { return _rootBuilder; }

	private:
		void writeNode(XmlBuilder* node, int indentLevel);

	public:
		void writeToFile();
	};
}