#include "BlackBoardPch.h"
#include "test.h"
#include "ReflectSerializer.h"
#include "XmlReader.h"
#include "XmlWriter.h"

#include <iostream>
#include <chrono>

using namespace ke;

int main()
{
	CharacterStatus characterStatus;
	characterStatus._killPoint = 5;
	characterStatus._bountyPointRatio = 0.75f;
	characterStatus._moveStatus._speed = 20;
	characterStatus._moveStatus._slowRatio = 0.2f;
	characterStatus._attackStatus._power = 15;
	characterStatus._attackStatus._lethality = 0.35;


	ReflectSerializer::serializeToXML("./characterStatus.xml", &characterStatus);

	return 0;
}