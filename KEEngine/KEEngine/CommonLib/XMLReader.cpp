#include "CommonLibPch.h"
#include "XMLReader.h"

namespace ke
{
	XmlReader::XmlReader(const char* path)
		: _file(path)
	{
		const FileCore& fileCore = _file.core();
		if (fileCore.getOpenStatus() != 0) return;

		const size_t fileSize = static_cast<size_t>(fileCore.getSize());
		_buffer.set(fileSize);
		_file.reader().read(&_buffer, fileSize);

		const char* begin = _buffer.getConstBuffer();
		const char* end = begin + fileSize;
		_rootNode = XmlNode(begin, end, end);
	}
}