#include "BlackBoardPch.h"
#include "test.h"
#include "ReflectSerializer.h"
#include "XmlStruct.h"

int main()
{
	{
		ke::MoveStatus moveStatus;
		moveStatus._speed = 50;
		moveStatus._slowRatio = 0.5f;

		ke::ReflectSerializer<ke::MoveStatus>::serializeToXML(nullptr, &moveStatus);
		bool t = true;

		const char* test = "\"Test1 = \\\"10\\\" Test2 = \\\"20\\\" Test3 = \\\"30\\\" Test4 = \\\"40\\\"\"";
		ke::XMLAttribute xmlAttr(test);
		while (xmlAttr.isValid())
		{

			std::string_view name = xmlAttr.getName();
			std::string_view value = xmlAttr.getValue();

			xmlAttr = xmlAttr.getNextAttribute();
		}
	}

	return 0;
}