// Eryck Torres Project


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/HivaAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/HivaGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, int32 ApplyLevel)
{
	check(InAbilitySystemComponentToGive);

	GrantAbilities(ActivateOnGivenAbilities, InAbilitySystemComponentToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InAbilitySystemComponentToGive, ApplyLevel);

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf < UGameplayEffect >& EffectClass : StartUpGameplayEffects)
		{
			if(!EffectClass) continue;

			UGameplayEffect* EffectClassDefaultObject = EffectClass->GetDefaultObject<UGameplayEffect>();

			InAbilitySystemComponentToGive->ApplyGameplayEffectToSelf(
				EffectClassDefaultObject,
				ApplyLevel,
				InAbilitySystemComponentToGive->MakeEffectContext()
			);
		}
	}
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UHivaGameplayAbility>>& InAbilitiesToGive,
	UHivaAbilitySystemComponent* InAbilitySystemComponentToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) return;

	for (const TSubclassOf<UHivaGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InAbilitySystemComponentToGive->GetAvatarActor(); // Set the source object to this data asset
		AbilitySpec.Level = ApplyLevel;

		InAbilitySystemComponentToGive->GiveAbility(AbilitySpec);
	}
}
