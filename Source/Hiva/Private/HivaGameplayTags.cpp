// Eryck Torres Project


#include "HivaGameplayTags.h"

namespace HivaGameplayTags
{
	/** Input Tags **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move,"InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look,"InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Capoeira,"InputTag.Capoeira")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ChangeCharacter,"InputTag.ChangeCharacter")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Gloves,"InputTag.LightAttack.Gloves")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Gloves,"InputTag.HeavyAttack.Gloves")

	/** Player tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Gloves,"Player.Weapon.Gloves");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Gloves,"Player.Ability.Attack.Light.Gloves");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Gloves,"Player.Ability.Attack.Heavy.Gloves");

	/** Test Event tags **/
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Test,"Player.Event.Test");

}
