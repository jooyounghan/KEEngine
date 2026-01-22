#pragma once
namespace ke
{
	class XMLWriter
	{
	public:
		void AddAttribute(const char* name, const char* value);
		void BeginElement(const char* name);
		void EndElement();

	private:
		struct XMLNode;
		XMLNode* _currentNode = nullptr;
	};
}