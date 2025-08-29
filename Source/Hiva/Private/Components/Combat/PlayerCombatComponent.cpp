// Eryck Torres Project


#include "Components/Combat/PlayerCombatComponent.h"
#include "Itens/Weapons/HivaPlayerWeapon.h"

AHivaPlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	return Cast<AHivaPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTagToGet));
}
