#include "BlackBoardPch.h"
#include "test.h"
#include "ReflectSerializer.h"
#include "XmlReader.h"
#include "XmlWriter.h"

#include <iostream>
#include <chrono>

using namespace ke;

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <cstdlib>
#else
#include <cstdlib>
#endif

static void TraverseSiblings(const XmlNode& node, XmlWriter* writer, int depth)
{
    std::string_view name = node.getName();
    XmlBuilder builder(name.data(), name.length(), writer, depth);

    for (XmlAttribute a = node.getFirstAttribute(); a.isValid(); a = a.getNextAttribute())
    {
        std::string_view n = a.getName();
        std::string_view v = a.getValue();
        builder.addAttribute(n.data(), n.length(), v.data(), v.length());
    }

    const auto& children = node.getChildNodes();
    if (!children.empty())
    {
        builder.openHeaderEnd();
        for (const XmlNode& childNode : children)
        {
            TraverseSiblings(childNode, writer, depth + 1);
        }
    }
}

static void TraverseDocument(const XmlNode& rootNode, XmlWriter& writer)
{
    if (!rootNode.isValid()) return;

    const auto& children = rootNode.getChildNodes();
    XmlBuilder* rootBuilder = writer.getRootBuilder();
    if (!children.empty())
    {
        rootBuilder->openHeaderEnd();
        for (const XmlNode& childNode : children)
        {
            TraverseSiblings(childNode, &writer, 1);
        }
    }
}


int main()
{
	std::chrono::high_resolution_clock clock;

    int iteration = 0;

    while(true)
    {
        auto startTime = clock.now();
		iteration++;
		XmlReader xmlReader("./xml_stress_1mb.xml");
        auto endTime = clock.now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "XMLReader : " << duration << " ms\n";
		XmlWriter xmlWriter("Root", "./output.xml");
        endTime = clock.now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "XMLWriter : " << duration << " ms\n";

        TraverseDocument(xmlReader.getRootNode(), xmlWriter);
        endTime = clock.now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "Traverse: " << duration << " ms\n";

        xmlWriter.writeToFile();
        endTime = clock.now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        std::cout << "WriteToFile : " << duration << " ms\n";

		iteration++;
		if (iteration >= 10)
            break;
	}

	return 0;
}