#include "BlackBoardPch.h"
#include "test.h"
#include "ReflectSerializer.h"
#include "XmlReader.h"
#include "XmlWriter.h"
#include "OwnerVector.h"

#include <iostream>
#include <chrono>

using namespace ke;

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
    TraverseSiblings(rootNode, &writer, 0);
}

void PrintOwnerVector(const OwnerVector<int>& vec)
{
    //std::cout << "OwnerVector contents: ";
    //for (size_t i = 0; i < vec.size(); ++i)
    //{
    //    std::cout << *(vec[i]) << " ";
    //}
    //std::cout << std::endl;
}

int main()
{
    //XmlReader xmlReader("./xml_stress_1mb.xml");
    //XmlWriter xmlWriter("./output.xml");
    //TraverseDocument(xmlReader.getRootNode(), xmlWriter);
    //xmlWriter.writeToFile();

    CharacterStatus characterStatus;
	characterStatus._killPoint = 5;
	characterStatus._bountyPointRatio = 0.75f;
	characterStatus._moveStatus._speed = 20;
	characterStatus._moveStatus._slowRatio = 0.2f;
	characterStatus._attackStatus._power = 15;
	characterStatus._attackStatus._lethality = 0.35;
    
	ReflectSerializer::serializeToXML("./characterStatus.xml", &characterStatus);

	
	CharacterStatus loadedStatus;
    FlyweightStringA tt = loadedStatus.getName_killPoint();
	printf("KillPoint name: %s\n", tt.c_str());
    FlyweightStringA t =  loadedStatus.getName_moveStatus();
	printf("MoveStatus name: %s\n", t.c_str());
    ReflectSerializer::deserializeFromXML("./characterStatus.xml", &loadedStatus);
	return 0;
}