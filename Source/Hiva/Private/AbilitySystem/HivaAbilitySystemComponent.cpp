// Eryck Torres Project


#include "AbilitySystem/HivaAbilitySystemComponent.h"

void UHivaAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UHivaAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	
}

void UHivaAbilitySystemComponent::GrantPlayerWeaponAbilities(const TArray<FHivaPlayerAbilitySet>& InWeaponAbilities, int32 ApplyLevel)
{
	if (InWeaponAbilities.IsEmpty()) return;

	for (const FHivaPlayerAbilitySet& AbilitySet : InWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToAdd);
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		GiveAbility(AbilitySpec);
	}
}
