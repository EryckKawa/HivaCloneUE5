// Eryck Torres Project

#pragma once

#include "NativeGameplayTags.h"

namespace HivaGameplayTags
{
	/** Input Tags **/
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Capoeira)
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ChangeCharacter)
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Gloves)
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Gloves)
	
	/** Player tags **/
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Gloves);
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Gloves);
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Gloves);

	
	/** Test Event tags **/
	HIVA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Test);

}
