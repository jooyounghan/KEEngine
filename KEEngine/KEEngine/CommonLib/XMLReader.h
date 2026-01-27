#pragma once
#include "File.h"
#include "DynamicBuffer.h"
#include "XmlNode.h"

namespace ke
{
	class XmlReader
	{
	public:
		XmlReader(const char* path);

	private:
		ReadOnlyFile	_file;
		DynamicBuffer	_buffer;
		XmlIndexer		_xmlIndexer;
		XmlNode			_rootNode;

	public:
		const XmlNode& getRootNode() const { return _rootNode; }
	};
}

