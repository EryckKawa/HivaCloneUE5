// Eryck Torres Project


#include "AbilitySystem/Abilities/HivaEnemyGameplayAbility.h"
#include "Characters/HivaEnemyCharacter.h"

AHivaEnemyCharacter* UHivaEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedHivaEnemyCharacter.IsValid())
	{
		CachedHivaEnemyCharacter = Cast<AHivaEnemyCharacter>(GetAvatarActorFromActorInfo());
	}

	return CachedHivaEnemyCharacter.IsValid()? CachedHivaEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UHivaEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
