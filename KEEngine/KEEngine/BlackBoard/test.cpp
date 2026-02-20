#include "BlackBoardPch.h"
#include "test.h"
#include "ReflectSerializer.h"
namespace ke
{
	DEFINE_ENUM_DESCRIPTOR(ECharacterType, Citizen, Warrior, Mage, Archer, Count);

	BEGIN_DEFINE_REFLECT_PROPERTY(MoveStatus)
		DEFINE_REFLECT_POD_PROPERTY(MoveStatus, _speed)
		DEFINE_REFLECT_POD_PROPERTY(MoveStatus, _slowRatio)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(MoveStatus)
		BIND_REFLECET_POD_RANGED_PROPERTY(MoveStatus, int8, _speed, EReflectUIOption::Editable, 10, 0, 100, 1);
		BIND_REFLECET_POD_RANGED_PROPERTY(MoveStatus, float, _slowRatio, EReflectUIOption::Editable, 0.1f, 0.0f, 1.0f, 0.01f);
	END_BIND_REFLECT_PROPERTY()


	BEGIN_DEFINE_REFLECT_PROPERTY(AttackStatus)
		DEFINE_REFLECT_POD_PROPERTY(AttackStatus, _power)
		DEFINE_REFLECT_POD_PROPERTY(AttackStatus, _lethality)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(AttackStatus)
		BIND_REFLECET_POD_RANGED_PROPERTY(AttackStatus, int16, _power, EReflectUIOption::Editable, 30, 0, 100, 1);
		BIND_REFLECET_POD_RANGED_PROPERTY(AttackStatus, double, _lethality, EReflectUIOption::Editable, 20.f, 0.0f, 1.0f, 0.01f);
	END_BIND_REFLECT_PROPERTY()

	BEGIN_DEFINE_REFLECT_PROPERTY(CharacterStatus)
		DEFINE_REFLECT_POD_PROPERTY(CharacterStatus, _killPoint);
		DEFINE_REFLECT_POD_PROPERTY(CharacterStatus, _bountyPointRatio);
		DEFINE_REFLECT_OBJECT_PROPERTY(CharacterStatus, _moveStatus);
		DEFINE_REFLECT_OBJECT_PROPERTY(CharacterStatus, _attackStatus);
		DEFINE_REFLECT_ENUM_PROPERTY(CharacterStatus, _characterType);
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(CharacterStatus)
		BIND_REFLECET_POD_RANGED_PROPERTY(CharacterStatus, uint32, _killPoint, EReflectUIOption::Editable, 0, 0, 100, 1);
		BIND_REFLECET_POD_RANGED_PROPERTY(CharacterStatus, float, _bountyPointRatio, EReflectUIOption::Editable, -1.f, 0.0f, 1.0f, 0.01f);
		BIND_REFLECET_PROPERTY(CharacterStatus, MoveStatus, _moveStatus, EReflectUIOption::Editable);
		BIND_REFLECET_PROPERTY(CharacterStatus, AttackStatus, _attackStatus, EReflectUIOption::Editable);
		//BIND_REFLECET_POD_PROPERTY(CharacterStatus, ECharacterType, _characterType, EReflectUIOption::Editable, ECharacterType::Citizen);
	END_BIND_REFLECT_PROPERTY()

	void testIsAttributeProperty()
	{
		const ReflectMetaData* metaData = CharacterStatus::getObjectMetaData();

		// POD properties must be serialized as XML attributes
		const IReflectProperty* killPointProp = metaData->getPropertyByName(CharacterStatus::getName_killPoint());
		KE_ASSERT(killPointProp != nullptr, "Property _killPoint not found");
		KE_ASSERT(killPointProp->isAttributeProperty() == true, "_killPoint (POD) must be an attribute property");

		const IReflectProperty* bountyPointRatioProp = metaData->getPropertyByName(CharacterStatus::getName_bountyPointRatio());
		KE_ASSERT(bountyPointRatioProp != nullptr, "Property _bountyPointRatio not found");
		KE_ASSERT(bountyPointRatioProp->isAttributeProperty() == true, "_bountyPointRatio (POD) must be an attribute property");

		// ReflectObject properties must be serialized as XML child nodes
		const IReflectProperty* moveStatusProp = metaData->getPropertyByName(CharacterStatus::getName_moveStatus());
		KE_ASSERT(moveStatusProp != nullptr, "Property _moveStatus not found");
		KE_ASSERT(moveStatusProp->isAttributeProperty() == false, "_moveStatus (ReflectObject) must not be an attribute property");

		const IReflectProperty* attackStatusProp = metaData->getPropertyByName(CharacterStatus::getName_attackStatus());
		KE_ASSERT(attackStatusProp != nullptr, "Property _attackStatus not found");
		KE_ASSERT(attackStatusProp->isAttributeProperty() == false, "_attackStatus (ReflectObject) must not be an attribute property");

		// Enum properties (stored as POD) must be serialized as XML attributes
		const IReflectProperty* characterTypeProp = metaData->getPropertyByName(CharacterStatus::getName_characterType());
		KE_ASSERT(characterTypeProp != nullptr, "Property _characterType not found");
		KE_ASSERT(characterTypeProp->isAttributeProperty() == true, "_characterType (Enum/POD) must be an attribute property");
	}

	void testReflectSerializerRoundTrip()
	{
		CharacterStatus original;
		original._killPoint = 42;
		original._bountyPointRatio = 0.75f;
		original._moveStatus._speed = 20;
		original._moveStatus._slowRatio = 0.2f;
		original._attackStatus._power = 15;
		original._attackStatus._lethality = 0.35;
		original._characterType = ECharacterType::Warrior;

		const char* testPath = "test_roundtrip.xml";
		ReflectSerializer::serializeToXML(testPath, &original);

		CharacterStatus loaded;
		ReflectSerializer::deserializeFromXML(testPath, &loaded);

		KE_ASSERT(loaded._killPoint == original._killPoint, "Round-trip failed: _killPoint mismatch");
		KE_ASSERT(loaded._bountyPointRatio == original._bountyPointRatio, "Round-trip failed: _bountyPointRatio mismatch");
		KE_ASSERT(loaded._moveStatus._speed == original._moveStatus._speed, "Round-trip failed: _moveStatus._speed mismatch");
		KE_ASSERT(loaded._moveStatus._slowRatio == original._moveStatus._slowRatio, "Round-trip failed: _moveStatus._slowRatio mismatch");
		KE_ASSERT(loaded._attackStatus._power == original._attackStatus._power, "Round-trip failed: _attackStatus._power mismatch");
		KE_ASSERT(loaded._attackStatus._lethality == original._attackStatus._lethality, "Round-trip failed: _attackStatus._lethality mismatch");
		KE_ASSERT(loaded._characterType == original._characterType, "Round-trip failed: _characterType mismatch");
	}

}