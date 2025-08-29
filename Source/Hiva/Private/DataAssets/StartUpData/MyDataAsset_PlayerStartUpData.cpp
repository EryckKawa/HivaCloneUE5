// Eryck Torres Project


#include "DataAssets/StartUpData/MyDataAsset_PlayerStartUpData.h"

#include "AbilitySystem/HivaAbilitySystemComponent.h"

void UMyDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InAbilitySystemComponentToGive, ApplyLevel);

	for (const FHivaPlayerAbilitySet& AbilitySet : PlayerStartupAbilitiesSets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToAdd);
		AbilitySpec.SourceObject = InAbilitySystemComponentToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		InAbilitySystemComponentToGive->GiveAbility(AbilitySpec);
	}
}
