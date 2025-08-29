// Eryck Torres Project


#include "Components/Combat/PawnCombatComponent.h"
#include "HivaDebugHelper.h"
#include "Itens/Weapons/HivaWeaponBase.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AHivaWeaponBase* InWeaponToRegister,  bool bRegisterAsEquippedWeaponOnSpawn)
{
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);

	if (bRegisterAsEquippedWeaponOnSpawn)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

}

AHivaWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AHivaWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}

	return nullptr;
}

AHivaWeaponBase* UPawnCombatComponent::GetCurrentEquippedWeapon() const
{
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}
