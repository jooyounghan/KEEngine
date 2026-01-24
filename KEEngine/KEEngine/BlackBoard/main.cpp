#include "BlackBoardPch.h"
#include "test.h"
#include "ReflectSerializer.h"
#include "XmlReader.h"
#include "XmlWriter.h"

#include <iostream>
#include <chrono>

using namespace ke;

static void PrintNodeHeader(const XmlNode& node, XmlBuilder* builder, int depth)
{
    for (XmlAttribute a = node.getFirstAttribute(); a.isValid(); a = a.getNextAttribute())
    {
		builder->addAttribute(std::string(a.getName()).c_str(), std::string(a.getValue()).c_str());
    }
}

static void TraverseSiblings(XmlNode node, XmlBuilder* builder, int depth)
{
    for (XmlNode n = node; n.isValid(); n = n.getNextSibling())
    {
		XmlBuilder* childBuilder = builder->addChild(std::string(n.getName()).c_str());
        PrintNodeHeader(n, childBuilder, depth);

        XmlNode child = n.getFirstChild();
        if (child.isValid())
        {
            TraverseSiblings(child, childBuilder, depth + 1);
        }
    }
}

static void TraverseDocument(const XmlNode& rootNode, XmlBuilder& rootBuilder)
{
    if (!rootNode.isValid())
    {
        std::cout << "No valid root element found.\n";
        return;
    }

    TraverseSiblings(rootNode, &rootBuilder, 0);
}


int main()
{
	MoveStatus moveStatus;
	moveStatus._speed = 50;
	moveStatus._slowRatio = 0.5f;

	ReflectSerializer<MoveStatus>::serializeToXML(nullptr, &moveStatus);
	bool t = true;

	std::chrono::high_resolution_clock clock;
	auto startTime = clock.now();
    int iteration = 0;

    while(true)
    {
		iteration++;
		XmlReader xmlReader("./xml_stress_1mb.xml");
		XmlWriter xmlWriter("Root", "./output.xml");

        TraverseDocument(xmlReader.getRootNode(), xmlWriter.getRootBuilder());

        xmlWriter.writeToFile();

        if (iteration % 100 == 0)
        {
			auto endTime = clock.now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
			std::cout << "Elapsed time for " << iteration << " iterations: " << duration << " ms\n";
			startTime = endTime;
        }

	}

	return 0;
}