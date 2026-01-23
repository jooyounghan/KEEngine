#include "BlackBoardPch.h"
#include "test.h"
#include "ReflectSerializer.h"
#include "XmlReader.h"

#include <iostream>
using namespace ke;

static void PrintIndent(int depth)
{
    for (int i = 0; i < depth; ++i) std::cout << "  ";
}

// 노드 하나 출력 (이름 + 속성)
static void PrintNodeHeader(const XmlNode& node, int depth)
{
    PrintIndent(depth);
    std::cout << "<" << node.getName();

    for (XmlAttribute a = node.getFirstAttribute(); a.isValid(); a = a.getNextAttribute())
    {
        std::cout << " " << a.getName() << "=\"" << a.getValue() << "\"";
    }

    if (node.isSelfClosing())
        std::cout << " />\n";
    else
        std::cout << ">\n";
}

static void PrintNodeFooter(const XmlNode& node, int depth)
{
    if (node.isSelfClosing()) return;

    PrintIndent(depth);
    std::cout << "</" << node.getName() << ">\n";
}

static void TraverseSiblings(XmlNode node, int depth)
{
    for (XmlNode n = node; n.isValid(); n = n.getNextSibling())
    {
        PrintNodeHeader(n, depth);

        XmlNode child = n.getFirstChild();
        if (child.isValid())
        {
            TraverseSiblings(child, depth + 1);
        }

        PrintNodeFooter(n, depth);
    }
}

static void TraverseDocument(const XmlNode& root)
{
    if (!root.isValid())
    {
        std::cout << "No valid root element found.\n";
        return;
    }

    TraverseSiblings(root, 0);
}

int main()
{
	{
		MoveStatus moveStatus;
		moveStatus._speed = 50;
		moveStatus._slowRatio = 0.5f;

		ReflectSerializer<MoveStatus>::serializeToXML(nullptr, &moveStatus);
		bool t = true;

		XmlReader xmlReader("./test.xml");
        TraverseDocument(xmlReader.getRootNode());
	}

	return 0;
}