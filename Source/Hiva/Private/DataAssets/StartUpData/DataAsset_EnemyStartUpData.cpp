// Eryck Torres Project


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "AbilitySystem/HivaAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/HivaEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InAbilitySystemComponentToGive, ApplyLevel);

	if (!EnemyStartupAbilities.IsEmpty())
	{
		for (const TSubclassOf<UHivaEnemyGameplayAbility>& AbilityClass : EnemyStartupAbilities)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InAbilitySystemComponentToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InAbilitySystemComponentToGive->GiveAbility(AbilitySpec);
		}
	}
}
