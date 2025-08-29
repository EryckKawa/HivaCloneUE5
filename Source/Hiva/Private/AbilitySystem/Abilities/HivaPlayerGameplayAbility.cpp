// Eryck Torres Project


#include "AbilitySystem/Abilities/HivaPlayerGameplayAbility.h"
#include "Characters/HivaPlayerCharacter.h"
#include "Controllers/HivaPlayerController.h"

AHivaPlayerCharacter* UHivaPlayerGameplayAbility::GetPlayerCharacterFromActorInfo()
{
	if (!CachedHivaPlayerCharacter.IsValid())
	{
		CachedHivaPlayerCharacter = Cast<AHivaPlayerCharacter>(GetAvatarActorFromActorInfo());
	}

	return CachedHivaPlayerCharacter.IsValid()? CachedHivaPlayerCharacter.Get() : nullptr;
}

AHivaPlayerController* UHivaPlayerGameplayAbility::GetPlayerControllerFromActorInfo()
{
	if (!CachedHivaPlayerController.IsValid())
	{
		CachedHivaPlayerController = Cast<AHivaPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedHivaPlayerController.IsValid()? CachedHivaPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* UHivaPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}
